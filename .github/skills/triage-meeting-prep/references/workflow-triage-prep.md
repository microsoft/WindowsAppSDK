# Triage Meeting Preparation Workflow

Complete step-by-step process for generating triage meeting summaries.

## Phase 1: Environment Verification

### Step 1.1: Verify GitHub CLI Availability

Before starting, verify the GitHub CLI (`gh`) is installed and authenticated:

```powershell
# Check gh is available
gh --version

# Check authentication
gh auth status
```

#### If gh CLI is not installed

Display this message to the user and pause:

> **GitHub CLI not detected.** This skill requires the GitHub CLI for data fetching.
>
> **Install:**
> ```powershell
> winget install GitHub.cli
> ```
>
> **Then authenticate:**
> ```powershell
> gh auth login
> ```
>
> After installation, re-run this skill.

### Step 1.2: Determine Output Directory

```
Generated-Files/triageMeeting/<YYYY-MM-DD>/
```

Create the directory structure if it doesn't exist.

> **Migration note**: If you have an existing `Generated Files/triageMeeting/...` directory from a previous run, rename `Generated Files` to `Generated-Files` before proceeding, or pass the legacy path explicitly when calling the scripts (e.g., `-PreviousStatePath "Generated Files/triageMeeting/previous-state.json"`) to preserve diff history and avoid a false first-run.

---

## Phase 2: Data Collection

### Step 2.1: Fetch Needs-Triage Issues

Use the `Get-TriageIssues.ps1` script to fetch issues:

```powershell
# Get all Needs-Triage issues (open and closed)
./.github/skills/triage-meeting-prep/scripts/Get-TriageIssues.ps1 -State all

# Get only issues without area labels (primary triage focus)
./.github/skills/triage-meeting-prep/scripts/Get-TriageIssues.ps1 -State open -NoAreaOnly

# View summary
./.github/skills/triage-meeting-prep/scripts/Get-TriageIssues.ps1 -NoAreaOnly -OutputFormat summary
```

The script internally runs:
```powershell
gh issue list --repo microsoft/WindowsAppSDK --label "Needs-Triage" --state all --json number,title,body,author,createdAt,updatedAt,closedAt,state,labels,milestone,comments,reactionGroups,url,assignees --limit 200
```

### Step 2.2: Filter Locally — Identify Issues Without Area Label

The `Get-TriageIssues.ps1 -NoAreaOnly` flag handles this automatically:

```powershell
For each issue in results:
  hasAreaLabel = issue.labels.any(label => label.name.startsWith("area-"))
  
  if NOT hasAreaLabel:
    → Include in output (needs triage)
  else:
    → Exclude (already triaged, has area label)
```

> **Why filter locally?** GitHub search doesn't support wildcard exclusions like `-label:area-*`. By fetching all and filtering, we automatically handle any new `area-*` labels without updating queries.

### Step 2.3: Get Detailed Issue Information

For individual issue details (comments, timeline):

```powershell
# Get full details for a specific issue
./.github/skills/triage-meeting-prep/scripts/Get-IssueDetails.ps1 -IssueNumber 6147

# With timeline events
./.github/skills/triage-meeting-prep/scripts/Get-IssueDetails.ps1 -IssueNumber 6147 -IncludeTimeline

# View summary
./.github/skills/triage-meeting-prep/scripts/Get-IssueDetails.ps1 -IssueNumber 6147 -OutputFormat summary
```

**Data collected per issue:**
- Issue number, title, body
- Author, created date, updated date
- State (open/closed), closed date if applicable
- Labels (all), milestone
- Reaction counts (👍, 👎, ❤️, etc.)
- Comment count and last comment date
- Linked PRs

### Step 2.4: Load Previous Triage State

Check for previous state file:
```
Generated-Files/triageMeeting/previous-state.json
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
      "reviewPath": "Generated-Files/issueReview/12345/overview.md"
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

### Step 2.5: Fetch Images and Attachments (Optional)

For issues that likely contain visual evidence, if needed you can use:
- `gh api` to fetch issue attachments
- Download screenshots manually from issue body

Extract attachments to:
```
Generated-Files/triageMeeting/<YYYY-MM-DD>/attachments/<issue-number>/
```

---

## Phase 3: Diff Calculation — What's Changed

### Step 3.1: Compare Current vs Previous State

Compare the current issue list against `previous-state.json`:

| Category | Logic | Action |
|----------|-------|--------|
| 🔥 **Hot** | Activity increased (comments, reactions, updates) | Highlight for attention |
| 🆕 **New** | Issue in current, NOT in `previous-state.json` | Run `Get-IssueDetails.ps1` |
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
- Preserve `lastSuggestedAction` from previous analysis (no need to re-run)

---

## Phase 4: Generate Issue Reviews

### Step 4.1: Fetch Area Label Definitions

Before analyzing issues, fetch the current area labels and their descriptions from the repository:

```powershell
# Get all area-* labels with descriptions
./.github/skills/triage-meeting-prep/scripts/Get-RepositoryLabels.ps1 -Filter "area-*" -OutputFormat json
```

This provides the complete list of valid area labels the agent can assign. **Keep this label list in context** — it is the source of truth for area classification throughout Phase 4.

### Step 4.2: Analyze All No-Area Issues

**Review ALL issues without area labels.** Each issue needs analysis for the summary.

For each **no-area issue** (new or older):

1. **Check if review exists:**
   ```
   if NOT exists("Generated-Files/issueReview/<issue-number>/overview.md"):
     → Run Get-IssueDetails.ps1 and analyze
   ```

2. **Run the issue analysis:**
   ```powershell
   ./Get-IssueDetails.ps1 -IssueNumber <number> -OutputFormat summary
   ```

3. **Classify the area label using LLM reasoning** (see "Area Classification" below)
   
4. **Generate review files:**
   - `Generated-Files/issueReview/<issue-number>/overview.md`
   - `Generated-Files/issueReview/<issue-number>/implementation-plan.md`

5. **Extract the "Suggested Actions" section from overview.md**, which includes:
   - Label recommendations (Add/Remove) — with area classification from step 3
   - Clarifying questions (if Clarity < 50)
   - Similar issues found
   - Potential assignees
   - Documentation check results

**Optimization:** Run analysis in parallel for up to 5 issues at a time.

### Area Classification (LLM Reasoning)

For each issue without an `area-*` label, classify it by reasoning about the issue content against the area label definitions fetched in Step 4.1.

**Inputs for classification:**
- Issue title, body, and comments (from `Get-IssueDetails.ps1`)
- Area label names and descriptions (from `Get-RepositoryLabels.ps1 -Filter "area-*"`)
- Codebase context (use `grep_search`, `semantic_search` on `dev/` directories if needed)

**Classification output format:**
```
area-<Name> [confidence:XX]
```

**Confidence rubric for area classification:**

| Score | Level | Criteria |
|-------|-------|----------|
| **80–100** | High | Issue explicitly names the component or API surface; maps to exactly one area with no ambiguity |
| **60–79** | Medium-High | Strong technical signals (stack traces, file paths, API names) point to one area; minor overlap possible |
| **40–59** | Medium | Reasonable match based on topic, but issue could plausibly belong to 2+ areas |
| **20–39** | Low | Weak signal; classification is a best guess based on general topic |
| **0–19** | Very Low | No clear technical signal; issue is vague, off-topic, or spans multiple areas equally |

**Confidence adjusters:**
- Issue mentions specific API or class name from the area: **+20**
- Stack trace or file path points to `dev/<AreaComponent>/`: **+20**
- Issue title directly references the area topic: **+15**
- Codebase search confirms the component: **+10**
- Issue could plausibly belong to 2+ areas: **−15**
- Issue is a general question with no technical detail: **−20**
- Issue is about tooling/build/infra rather than a specific SDK feature: **−10**

**Rules:**
- Always suggest the **single best area**, even at low confidence
- If confidence < 40, note the ambiguity and list alternative candidate areas
- Format: `Suggested: area-Notifications [confidence:75]`
- If alternatives exist: `Alternatives: area-AppLifecycle [confidence:35], area-Packaging [confidence:30]`

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

Use `gh search issues` to find:
```powershell
gh search issues "<keywords from issue>" --repo microsoft/WindowsAppSDK
gh search issues "label:area-<component>" --repo microsoft/WindowsAppSDK
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

1. **Fetch recent comments** using `Get-IssueDetails.ps1 -IssueNumber <number>`
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

4. **Assign confidence level (0-100)** using `[confidence:XX]` format:
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

**Confidence output format**: `[confidence:XX]` — grep-friendly for filtering.

```bash
# Find high-confidence suggestions (80+)
grep "\[confidence:[89][0-9]\]" summary.md

# Find low-confidence items needing review
grep "\[confidence:[0-3][0-9]\]" summary.md
```

```powershell
# Find high-confidence suggestions (80+)
Select-String -Path summary.md -Pattern '\[confidence:[89][0-9]\]'

# Find low-confidence items needing review
Select-String -Path summary.md -Pattern '\[confidence:[0-3][0-9]\]'

# List all items with confidence, sorted by value
Get-Content summary.md | Select-String '\[confidence:(\d+)\]' | 
    ForEach-Object { $_.Line }
```

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
Generated-Files/triageMeeting/previous-state.json
```

Also create a dated backup:
```
Generated-Files/triageMeeting/<YYYY-MM-DD>/state-snapshot.json
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

## Appendix: Script Reference

This skill uses PowerShell scripts in the `scripts/` folder for predictable, scriptable data fetching:

| Script | Purpose |
|--------|---------|
| `Get-TriageIssues.ps1` | Fetch all Needs-Triage issues with filtering options |
| `Get-IssueDetails.ps1` | Get detailed info for a single issue (comments, timeline) |
| `Compare-TriageState.ps1` | Compare current issues against previous state |
| `Save-TriageState.ps1` | Save current state for next diff comparison |

### Get-TriageIssues.ps1

```powershell
# Get all Needs-Triage issues as JSON
./Get-TriageIssues.ps1

# Get only open issues without area labels
./Get-TriageIssues.ps1 -State open -NoAreaOnly

# Display summary
./Get-TriageIssues.ps1 -NoAreaOnly -OutputFormat summary

# Display as table
./Get-TriageIssues.ps1 -NoAreaOnly -OutputFormat table
```

### Get-IssueDetails.ps1

```powershell
# Get issue details as JSON
./Get-IssueDetails.ps1 -IssueNumber 6147

# Include timeline events
./Get-IssueDetails.ps1 -IssueNumber 6147 -IncludeTimeline

# Display summary
./Get-IssueDetails.ps1 -IssueNumber 6147 -OutputFormat summary
```

### Compare-TriageState.ps1

```powershell
# Compare current issues against previous state
./Get-TriageIssues.ps1 | ./Compare-TriageState.ps1

# Display summary instead of JSON
./Get-TriageIssues.ps1 | ./Compare-TriageState.ps1 -OutputFormat summary
```

### Save-TriageState.ps1

```powershell
# Save current state for next triage
./Get-TriageIssues.ps1 | ./Save-TriageState.ps1

# Save with specific date
./Get-TriageIssues.ps1 | ./Save-TriageState.ps1 -TriageDate "2026-02-02"
```

## Appendix: Raw gh CLI Commands

The scripts wrap these `gh` CLI commands:

```powershell
# List all Needs-Triage issues (open)
gh issue list --repo microsoft/WindowsAppSDK --label "Needs-Triage" --state open --json number,title,body,author,createdAt,updatedAt,state,labels,comments,reactionGroups,url,assignees --limit 200

# List all Needs-Triage issues (closed)
gh issue list --repo microsoft/WindowsAppSDK --label "Needs-Triage" --state closed --json number,title,body,author,createdAt,updatedAt,closedAt,state,labels,comments,reactionGroups,url,assignees --limit 200

# Get single issue details
gh issue view <number> --repo microsoft/WindowsAppSDK --json number,title,body,author,createdAt,updatedAt,closedAt,state,labels,milestone,reactionGroups,comments,url,assignees

# Get issue timeline (API call)
gh api repos/microsoft/WindowsAppSDK/issues/<number>/timeline --paginate
```

