# Triage Meeting Preparation Workflow

Complete step-by-step process for generating triage meeting summaries.

## Phase 1: Environment Verification

### Step 1.1: Verify GitHub MCP Availability

Before starting, verify the GitHub MCP tools are available by checking if `activate_repository_information_tools` can be invoked.

#### If MCP is unavailable

Display this message to the user and pause:

> **GitHub MCP not detected.** This skill requires the GitHub MCP for full functionality.
>
> **Install options:**
> 1. **VS Code extension** (recommended): Install [GitHub Pull Requests](https://marketplace.visualstudio.com/items?itemName=GitHub.vscode-pull-request-github) extension, then enable MCP in settings
> 2. **Manual MCP setup**: Follow [GitHub MCP documentation](https://docs.github.com/en/copilot/customizing-copilot/extending-copilot-chat-in-vs-code/using-model-context-protocol-servers-in-vs-code)
>
> After installation, restart VS Code and re-run this skill.

#### Fallback mode (limited functionality)

If the user chooses to proceed without MCP:
- Use `gh` CLI commands as fallback (requires GitHub CLI installed and authenticated)
- Issues query: `gh issue list --repo microsoft/WindowsAppSDK --label "Needs-Triage" --state all --json number,title,body,author,createdAt,updatedAt,state,labels,comments,reactions --limit 200`
- **Note**: Some advanced analysis features may be limited in fallback mode.

### Step 1.2: Determine Output Directory

```
Generated Files/triageMeeting/<YYYY-MM-DD>/
```

Create the directory structure if it doesn't exist.

---

## Phase 2: Data Collection

### Step 2.1: Fetch Needs-Triage Issues

Use `activate_github_search_tools` to search for issues:

#### Query 1: All open Needs-Triage issues
```
repo:microsoft/WindowsAppSDK is:issue is:open label:"Needs-Triage"
```

#### Query 2: Closed issues still labeled Needs-Triage
```
repo:microsoft/WindowsAppSDK is:issue is:closed label:"Needs-Triage"
```

### Step 2.2: Filter Locally — Identify Issues Without Area Label

After fetching, filter the results locally:

```
For each issue in Query 1 results:
  hasAreaLabel = issue.labels.any(label => label.name.startsWith("area-"))
  
  if NOT hasAreaLabel:
    → Add to "noAreaIssues" list (needs triage)
  else:
    → Skip (already triaged, has area label)
```

> **Why filter locally?** GitHub search doesn't support wildcard exclusions like `-label:area-*`. By fetching all and filtering, we automatically handle any new `area-*` labels without updating queries.

**MCP tool sequence:**
1. `github-pull-request_formSearchQuery` — Convert to GitHub search syntax
2. `github-pull-request_doSearch` — Execute both queries
3. For each issue, check if any label starts with `area-`
4. Use `activate_repository_information_tools` → `Get issue` for full details of no-area issues

**Data to collect per issue:**
- Issue number, title, body
- Author, created date, updated date
- State (open/closed), closed date if applicable
- Labels (all), milestone
- Reaction counts (👍, 👎, ❤️, etc.)
- Comment count and last comment date
- Linked PRs

### Step 2.3: Load Previous Triage State

Check for previous state file:
```
Generated Files/triageMeeting/previous-state.json
```

**Previous state schema:**
```json
{
  "triageDate": "2025-01-24T10:00:00Z",
  "noAreaIssues": {
    "12345": {
      "title": "Issue title",
      "firstSeen": "2025-01-17T10:00:00Z",
      "weeksPending": 1,
      "lastSuggestedAction": "Add area-Packaging label",
      "reviewPath": "Generated Files/issueReview/12345/overview.md"
    }
  },
  "closedIssues": {
    "67890": {
      "title": "Closed issue",
      "closedAt": "2025-01-23T15:30:00Z"
    }
  }
}
```

If no previous state exists:
- This is the first run
- All issues will be categorized as "New"
- Inform the user that diff comparison will be available after next run

### Step 2.3: Fetch Images and Attachments (if github-artifacts MCP available)

For issues that likely contain visual evidence:
- Use `mcp_github-artifa_github_issue_images` for screenshots
- Use `mcp_github-artifa_github_issue_attachments` for diagnostic logs

Extract attachments to:
```
Generated Files/triageMeeting/<YYYY-MM-DD>/attachments/<issue-number>/
```

---

## Phase 3: Diff Calculation — What's Changed

### Step 3.1: Compare Current vs Previous State

Compare the current issue list against `previous-state.json`:

| Category | Logic | Action |
|----------|-------|--------|
| 🔥 **Hot** | Activity increased (comments, reactions, updates) | Highlight for attention |
| 🆕 **New** | Issue in current, NOT in `previous-state.json` | Run review-issue.prompt.md |
| ⏳ **Still Pending** | Issue in BOTH current AND `previous-state.json` | Increment `weeksPending`, carry forward |
| ✅ **Resolved** | Issue in `previous-state.json`, NOT in current | Note resolution type |

### Step 3.2: Identify Hot Issues (Trending)

**Hot issues** are those with **significant** increased community engagement since last triage. Check ALL Needs-Triage issues:

```
For each issue in currentNeedsTriageIssues:
  if issue.number in previousState.allIssues:
    prev = previousState.allIssues[issue.number]
    
    commentChange = issue.commentCount - prev.commentCount
    reactionChange = issue.reactionCount - prev.reactionCount
    totalChange = commentChange + reactionChange
    
    # Only flag if SIGNIFICANT community activity increase
    if totalChange >= 5:
      → Add to "hotIssues" list with change deltas
```

**Hot issue threshold**: Combined increase of **≥5** (comments + reactions)

Examples:
- ✅ +3 comments, +2 reactions = 5 → HOT
- ✅ +5 comments, +0 reactions = 5 → HOT
- ✅ +0 comments, +6 reactions = 6 → HOT
- ❌ +1 comment, +0 reactions = 1 → Not hot
- ❌ +2 comments, +2 reactions = 4 → Not hot

**NOT considered hot** (these are admin/triage actions, not community engagement):
- ❌ `updatedAt` changed (could be label/milestone/assignment changes)
- ❌ Labels added or removed
- ❌ Assignee changed

> **Note**: Hot issues may already have area labels — they're flagged because of significant community activity regardless.

### Step 3.3: Categorize No-Area Issues

**Pseudocode:**
```
newIssues = currentNoAreaIssues - previousNoAreaIssues
pendingIssues = currentNoAreaIssues ∩ previousNoAreaIssues
resolvedIssues = previousNoAreaIssues - currentNoAreaIssues
```

### Step 3.4: Determine Resolution Type for Resolved Issues

For each issue in `previousNoAreaIssues` but not in `currentNoAreaIssues`, check:

1. **Got area label**: Issue is still open but now has `area-*` label → `"Got area label"`
2. **Closed properly**: Issue is closed and no longer has `Needs-Triage` → `"Closed"`
3. **Closed with cleanup needed**: Issue is closed but still has `Needs-Triage` → Move to closedIssues list

### Step 3.5: Update Pending Issue Tracking

For each issue still pending:
- Increment `weeksPending` counter
- Preserve `firstSeen` date
- Preserve `lastSuggestedAction` from previous review (no need to re-run review-issue)

---

## Phase 4: Generate Issue Reviews

### Step 4.1: Run review-issue.prompt.md for All No-Area Issues

**Run reviews for ALL issues without area labels.** Each issue needs a review file for the summary links to work.

For each **no-area issue** (new or older):

1. **Check if review exists:**
   ```
   if NOT exists("Generated Files/issueReview/<issue-number>/overview.md"):
     → Run review-issue.prompt.md
   ```

2. **Run the review-issue analysis:**
   ```
   review-issue.prompt.md with issue_number = <issue-number>
   ```
   
2. **Generates these files:**
   - `Generated Files/issueReview/<issue-number>/overview.md`
   - `Generated Files/issueReview/<issue-number>/implementation-plan.md`

3. **Extract the "Suggested Actions" section from overview.md**, which includes:
   - Label recommendations (Add/Remove)
   - Clarifying questions (if Clarity < 50)
   - Similar issues found
   - Potential assignees
   - Documentation check results

**Optimization:** Run analysis in parallel for up to 5 issues at a time.

### Step 4.2: Extract Action Items for Summary

From each NEW issue's `overview.md`, extract and collect:

| Field | Source in overview.md | Use in Summary |
|-------|----------------------|----------------|
| Suggested area label | Label Recommendations → Add `area-*` | Issue table + Action items |
| All label changes | Label Recommendations section | Consolidated label changes |
| Clarifying questions | Clarifying Questions section | Questions to post |
| Similar issues | Similar Issues Found section | Reference for duplicates |
| Potential assignees | Potential Assignees section | Assignment suggestions |
| Documentation check | Documentation Check section | Known limitation responses |
| Priority score | Overall Priority in At-a-Glance table | Sorting and prioritization |

### Step 4.3: Build Consolidated Action Items

Aggregate all action items from individual reviews:

```markdown
## Consolidated Action Items

### Label Changes
#<number>: Add `area-X`, Add `bug`
#<number>: Add `area-Y`, Add `needs-author-feedback`
...

### Questions to Post
#<number>: [question1], [question2]
...
```

---

## Phase 5: Analyze Closed Issues Needing Reply

### Step 5.1: Research Before Drafting Reply

**For each closed issue with Needs-Triage, conduct thorough research:**

#### A) Search for Similar/Related Issues

Use `github-pull-request_doSearch` to find:
```
repo:microsoft/WindowsAppSDK <keywords from issue>
repo:microsoft/WindowsAppSDK label:area-<component>
```

Look for:
- **Duplicate issues** that may have better answers
- **Related closed issues** with fixes or workarounds
- **Open issues** tracking the same problem
- **PRs that addressed similar problems**

#### B) Search the Codebase

Use `grep_search` and `semantic_search` to find:
- **Relevant source code** in the affected component
- **Existing workarounds** or patterns
- **Comments/TODOs** about known limitations
- **Test files** that show expected behavior

Example searches:
```
# Find related code
grep_search: "PowerManager" OR "SystemSuspendStatus"
grep_search: "ReleaseInfo" OR "GetVersion"

# Semantic search for concepts
semantic_search: "device pairing UI WinUI"
semantic_search: "version info patch number"
```

#### C) Check Documentation and Release Notes

Use `fetch_webpage` to research:
- **Official docs**: `https://learn.microsoft.com/windows/apps/windows-app-sdk/`
- **Release notes**: `https://learn.microsoft.com/windows/apps/windows-app-sdk/stable-channel`
- **Known issues**: Check if the issue is documented as a known limitation
- **API reference**: Verify expected behavior

#### D) Review Git History

Use terminal commands to find:
```powershell
# Who worked on this area recently?
git log --oneline --since="6 months ago" -- dev/<ComponentName>/

# What PRs touched related files?
git log --all --format="%h %s" -- <file_paths> | head -20

# Any related commits?
git log --all --grep="<keyword>" --oneline | head -10
```

### Step 5.2: Document Research Findings

For each closed issue, record:

```markdown
### Research Summary for #<number>

**Similar Issues Found:**
- #<number> - <title> (<state>) - <relevance>
- #<number> - <title> (<state>) - <relevance>

**Codebase Findings:**
- File: `<path>` - <what we learned>
- Pattern: <existing approach in codebase>

**Documentation:**
- <URL> - <what docs say>
- Known limitation: Yes/No

**Git History:**
- Recent PRs: #<pr> by @<author> - <relevance>
- Area owner: @<username>

**Conclusion:**
<Summary of what we learned and how it informs the reply>
```

### Step 5.3: Draft Reply with Research Context

Now draft the reply using research findings:

1. **Fetch recent comments** using `mcp_github_issue_read` with `method: get_comments`
2. **Analyze the situation**:
   - Why was it closed originally?
   - What did the customer say after closure?
   - Is the concern valid (bug vs feature)?
   - Is there a workaround (from research)?

3. **Draft a suggested reply** incorporating:
   - References to similar issues found
   - Workarounds from codebase research
   - Documentation links
   - Technical context from code analysis

4. **Assign confidence level (0-100)**:
   - **80-100**: Clear response backed by research
   - **60-79**: Good draft, research supports it
   - **40-59**: Limited research, needs team input
   - **0-39**: Insufficient research, requires escalation

5. **Recommend action**:
   - Post reply + remove label
   - Post reply + reopen issue
   - Escalate to specific team
   - Keep closed with workaround documented

**Confidence factors:**
- Similar issue found with resolution: +20
- Workaround confirmed in codebase: +20
- Documentation supports response: +15
- Clear code owner identified: +10
- Customer frustration level high: -15
- Requires team decision to reopen: -20
- Research inconclusive: -25

---

## Phase 6: Report Generation

### Step 6.1: Generate Summary Report

Create `summary.md` using [template-summary.md](../templates/template-summary.md).

**Sections:**
1. Meeting header (date, issue counts)
2. Quick stats (no-area count, closed count)
3. Issues needing area labels (with suggested areas + links to reviews)
4. **Closed issues with suggested replies** — Including confidence level and reasoning
5. Consolidated action items (copy-paste ready)

### Step 6.2: Generate Action Items File

Create `action-items.md` with all consolidated actions for easy reference.

### Step 6.3: Save Current State for Next Diff

Create `previous-state.json` with current snapshot:
```
Generated Files/triageMeeting/previous-state.json
```

Also create a dated backup:
```
Generated Files/triageMeeting/<YYYY-MM-DD>/state-snapshot.json
```

---

## Phase 7: Presentation

### Step 7.1: Display Summary to User

Show the key sections of `summary.md`:
- Quick stats table
- High-priority items
- Action items requiring discussion

### Step 7.2: Offer Follow-up Actions

Prompt the user with available next steps:
1. "View detailed analysis for issue #X"
2. "Generate implementation plan for issue #X"
3. "Post clarifying questions to issue #X"
4. "Update labels for reviewed issues"

---

## Appendix: MCP Tool Reference

| Tool | Purpose |
|------|---------|
| `activate_github_search_tools` | Access search query tools |
| `github-pull-request_formSearchQuery` | Convert natural language to GitHub search |
| `github-pull-request_doSearch` | Execute issue/PR search |
| `activate_repository_information_tools` | Access issue detail tools |
| `Get issue` | Fetch full issue details |
| `github-pull-request_renderIssues` | Render issue table for display |
| `mcp_github-artifa_github_issue_images` | Download issue screenshots |
| `mcp_github-artifa_github_issue_attachments` | Download diagnostic attachments |

## Appendix: gh CLI Fallback Commands

If MCP is unavailable, use these commands:

```bash
# List all Needs-Triage issues (open)
gh issue list --repo microsoft/WindowsAppSDK --label "Needs-Triage" --state open --json number,title,body,author,createdAt,updatedAt,state,labels,comments,reactions --limit 200

# List all Needs-Triage issues (closed)
gh issue list --repo microsoft/WindowsAppSDK --label "Needs-Triage" --state closed --json number,title,body,author,createdAt,updatedAt,closedAt,state,labels,comments,reactions --limit 200

# Get single issue details
gh issue view <number> --repo microsoft/WindowsAppSDK --json number,title,body,author,createdAt,updatedAt,state,labels,milestone,reactions,comments,linkedPullRequests
```
