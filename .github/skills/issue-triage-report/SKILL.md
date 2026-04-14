---
name: issue-triage-report
description: Generate comprehensive GitHub Feature Area Status reports for the Windows App SDK repository. Use when asked to create triage reports, identify high-priority issues, analyze feature area health, find issues needing attention, or generate status dashboards. Triggers on requests involving issue triage, area status, priority analysis, bug tracking reports, or engineering team focus areas.
license: Complete terms in LICENSE.txt
---

# Issue Triage Report Generator

This skill generates comprehensive GitHub Feature Area Status reports that help engineering teams identify high-priority issues, track triage status, and highlight items needing immediate attention.

## When to Use This Skill

**Primary triggers** — Generate a report when:

1. **Engineering triage meetings** — Create status reports showing open issues, needs-triage counts, and highlighted issues per feature area.

2. **Priority analysis requests** — Identify which issues should get engineering focus based on deterministic scoring (reactions, age, comments) plus agent content assessment.

3. **Feature area health checks** — Assess the health of specific areas by analyzing issue distribution, triage backlog, and proposal counts.

4. **Dashboard generation** — Produce markdown tables or formatted reports for team communication channels.

**Anti-patterns** — Do NOT use this skill when:
- Looking for a specific issue by number (use GitHub search directly)
- Creating or editing issues (use GitHub MCP tools)
- Analyzing code changes or PRs (use PR management tools)

## Prerequisites

- GitHub CLI (`gh`) installed and authenticated
- PowerShell 5.1+ (Windows) or PowerShell Core (cross-platform)
- Access to the target GitHub repository (microsoft/WindowsAppSDK)
- **Area contacts configuration** (see below)

### Setting Up Area Contacts

The area contacts file maps feature areas to team members. This file is **required** for contact lookups and is stored in your local `.user/` folder (not committed to the repository).

1. Create the directory structure:
   ```powershell
   mkdir -p .user/issue-triage-report
   ```

2. Copy the template and customize:
   ```powershell
   cp .github/skills/issue-triage-report/references/area-contacts.json .user/issue-triage-report/area-contacts.json
   ```

3. Edit `.user/issue-triage-report/area-contacts.json` with your team's actual contacts

> **Note**: The `.user/` folder is gitignored, so your team contacts remain private.

## Available Scripts

### Generate-FeatureAreaReport.ps1

Generate the full feature area status report with highlight scoring.

**Location**: `./scripts/Generate-FeatureAreaReport.ps1`

```powershell
./scripts/Generate-FeatureAreaReport.ps1 [-Repo <owner/repo>] [-OutputFormat <markdown|csv|json>] [-HighlightCount <n>]
```

| Parameter | Required | Default | Description |
|-----------|----------|---------|-------------|
| `-Repo` | No | `microsoft/WindowsAppSDK` | Repository in `owner/repo` format |
| `-OutputFormat` | No | `markdown` | Output format: `markdown`, `csv`, or `json` |
| `-HighlightCount` | No | `3` | Max highlighted issues per area |
| `-IncludeClosed` | No | `$false` | Include recently closed issues count |

**Example**:
```powershell
./scripts/Generate-FeatureAreaReport.ps1 -OutputFormat markdown -HighlightCount 3
```

---

### Get-HighlightScore.ps1

Calculate the highlight score for a specific issue to determine priority.

**Location**: `./scripts/Get-HighlightScore.ps1`

```powershell
./scripts/Get-HighlightScore.ps1 -IssueNumber <number> [-Repo <owner/repo>] [-Verbose]
```

| Parameter | Required | Default | Description |
|-----------|----------|---------|-------------|
| `-IssueNumber` | Yes | - | GitHub issue number to analyze |
| `-Repo` | No | `microsoft/WindowsAppSDK` | Repository in `owner/repo` format |
| `-Verbose` | No | `$false` | Show detailed scoring breakdown |

**Example**:
```powershell
./scripts/Get-HighlightScore.ps1 -IssueNumber 4651 -Verbose
```

---

### Get-AreaContacts.ps1

Retrieve or update the area-to-contact mapping configuration.

**Location**: `./scripts/Get-AreaContacts.ps1`

```powershell
./scripts/Get-AreaContacts.ps1 [-Area <area-name>] [-Update]
```

| Parameter | Required | Default | Description |
|-----------|----------|---------|-------------|
| `-Area` | No | - | Specific area to look up (returns all if omitted) |
| `-Update` | No | `$false` | Interactively update contact mapping |

## Step-by-Step Workflows

### Workflow 1: Generate Weekly Triage Report

1. Ensure GitHub CLI is authenticated:
   ```powershell
   gh auth status
   ```

2. Generate the report:
   ```powershell
   ./scripts/Generate-FeatureAreaReport.ps1 -OutputFormat markdown -HighlightCount 3
   ```

  Before running the command above, have the agent save runtime assessments to:
  - `./references/AgentAssessments.json`

  This file is loaded automatically at script start and applied as per-run overrides.

3. Run an agent content review for each highlighted issue using title, body, labels, and comments.

4. Add annotation tags in report narrative: `[severity:critical|high|medium|low|none]`, `[blocker:yes|no]`, and optional `[confidence:XX]`.

5. Copy output to team communication channel (Teams, email, wiki)

### Workflow 2: Analyze a Specific Feature Area

1. Get area-specific issues:
    ```powershell
    gh issue list --repo microsoft/WindowsAppSDK --label "area-Notifications" --state open --json number,title,body,labels,reactionGroups,createdAt,comments
    ```

2. Check individual issue scores:
   ```powershell
   ./scripts/Get-HighlightScore.ps1 -IssueNumber 2894 -Verbose
   ```

3. Review scoring factors and prioritize accordingly

### Workflow 3: Update Area Contacts

1. View current contacts:
   ```powershell
   ./scripts/Get-AreaContacts.ps1
   ```

2. Update specific area contact:
   ```powershell
   ./scripts/Get-AreaContacts.ps1 -Area "area-Notifications" -Update
   ```

## Highlight Scoring Algorithm

Issues are scored with a raw-weighted composite. See [scoring-algorithm.md](./references/scoring-algorithm.md) for complete details.

PowerShell computes deterministic score factors and highlight labels. Severity and blocker are assessment-driven inputs.

Scripts load baseline assessments from:

- `./references/IssueAssessments.json`

They also load runtime agent assessments from:

- `./references/AgentAssessments.json`

If both files include the same issue number, `IssueAssessments.json` takes precedence.

If either file is missing or malformed, scripts emit status/warning output and continue with fallback behavior.

## Agent Content Review

After generating scores, review each highlighted issue and assign these annotations based on title, body, labels, and comments:

- `[severity:critical|high|medium|low|none]`
- `[blocker:yes|no]`
- `[confidence:XX]`

Use this severity rubric:

| Tier | Meaning |
|------|---------|
| `critical` | Crash, data loss, severe regression, or broad user/system impact |
| `high` | Serious functional break affecting key workflows |
| `medium` | User-visible defect or limitation with practical workaround |
| `low` | Minor issue, edge case, docs/polish impact |
| `none` | No clear severity signal from issue content |

Mark `[blocker:yes]` only when issue content explicitly indicates dependency blocking (for example: "blocked by", "blocking release", "must be fixed before") and no workaround has been provided. Otherwise use `[blocker:no]`.

Use this confidence rubric:

| Score | Level | Meaning |
|-------|-------|---------|
| **80-100** | High | Multiple strong signals agree: issue content, labels, reactions, age, comments, and recent discussion all support highlighting it |
| **60-79** | Medium-High | Strong support from the score breakdown and issue details, with only minor ambiguity |
| **40-59** | Medium | Reasonable highlight candidate, but some evidence is weak, stale, or mixed |
| **20-39** | Low | The numeric score is carrying most of the case; supporting context is limited or ambiguous |
| **0-19** | Very Low | The issue surfaced mechanically, but the agent cannot defend highlighting it with the available evidence |

Confidence should consider:

- whether the issue body and comments clearly support the highlight label
- whether the numeric score is driven by multiple meaningful factors instead of one outlier
- whether the issue still appears relevant after reading recent discussion
- whether the highlight reason would be easy to defend in a triage meeting

### Quick Reference: Score Factors

| Factor | Weight (between 0 and 1) | Description |
|--------|--------|-------------|
| **Reactions** | `weights.reactions` | `floor(weight * totalReactions)` |
| **Age** | `weights.age` | `floor(weight * issueAgeDays)` |
| **Comments** | `weights.comments` | `floor(weight * commentCount)` |
| **Severity** | `weights.severity` | `weight * severityMultipliers[tier]` from assessments (`critical/high/medium/low/none`) |
| **Blockers** | `weights.blockers` | Adds blocker weight when assessed `isBlocker=true` |

`Total` is an integer sum. If severity or blocker points are fractional, they are truncated when total score is computed.

### Highlight Labels (Output)

The report adds reason labels to highlighted issues:

| Label | Meaning |
|-------|---------|
| `🌟 Popular` | High reaction count (≥5 reactions) |
| `⏰ Aging` | Open > 90 days without triage |
| `📈 Trending` | High comment activity (≥10 comments) |

## Report Output Format

### Markdown Table (Default)

```markdown
| Feature Area | Area Contact | Open | Triage | Proposals | Closed | Highlights |
|--------------|--------------|------|--------|-----------|--------|------------|
| area-Notification | Contact Name | 34 | 8 | 11 | 0 | 🌟 [#2894](link), ⏰ [#3001](link) |
| area-Widgets | Contact Name | 21 | 10 | 4 | 0 | 📈 [#3958](link) |
```

### Agent-Reviewed Output

When producing the final narrative report, the agent should append content-review annotations:

```markdown
| Feature Area | Area Contact | Open | Triage | Proposals | Closed | Highlights |
|--------------|--------------|------|--------|-----------|--------|------------|
| area-Notification | Contact Name | 34 | 8 | 11 | 0 | 🌟 [#2894](link) [severity:high] [blocker:no] [confidence:85], ⏰ [#3001](link) [severity:medium] [blocker:no] [confidence:72] |
| area-Widgets | Contact Name | 21 | 10 | 4 | 0 | 📈 [#3958](link) [severity:low] [blocker:no] [confidence:68] |
```

### Special Status Indicators

| Indicator | Meaning |
|-----------|---------|
| `0️⃣🐛🥳` | Zero bugs — celebrate! |
| `-` | Data not applicable or unavailable |

## Configuration

### Area Contacts

Contact mappings are stored in [area-contacts.json](./references/area-contacts.json). Update this file when team assignments change.

### Custom Scoring Weights

Modify scoring weights in `./scripts/ScoringConfig.json`.

`severityMultipliers` maps assessment tiers to the percentage of `weights.severity` that is applied.

## Troubleshooting

| Symptom | Solution |
|---------|----------|
| `gh: command not found` | Install GitHub CLI: `winget install GitHub.cli` |
| `authentication required` | Run `gh auth login` and follow prompts |
| Rate limit exceeded | Wait or use `--limit` to reduce API calls |
| Missing area label | Issue may use non-standard label; check label list |
| Contact not found | Update [area-contacts.json](./references/area-contacts.json) |

## Common Commands Reference

```powershell
# List all area labels (uses Get-RepositoryLabels.ps1 as the single source of truth)
./.github/skills/triage-meeting-prep/scripts/Get-RepositoryLabels.ps1 -Filter "area-*" -OutputFormat table

# Get issue details with reactions
gh issue view 4651 --repo microsoft/WindowsAppSDK --json number,title,labels,reactionGroups,createdAt,comments,author

# List issues needing triage
gh issue list --repo microsoft/WindowsAppSDK --label "needs-triage" --state open --json number,title,labels

# Export all open issues to JSON
gh issue list --repo microsoft/WindowsAppSDK --state open --limit 1000 --json number,title,labels,reactionGroups,createdAt,comments,author
```

## References

- [Scoring Algorithm Details](./references/scoring-algorithm.md) — Complete scoring methodology
- [Area Contacts](./references/area-contacts.json) — Feature area ownership mapping
- [Report Template](./templates/report-template.md) — Customizable output template
