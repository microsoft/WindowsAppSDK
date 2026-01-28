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

2. **Priority analysis requests** — Identify which issues should get engineering focus based on multi-factor scoring (reactions, age, severity, blockers).

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

3. Edit `.user/issue-triage-report/area-contacts.json` with your team's actual contacts:
   ```json
   {
     "areaContacts": {
       "area-FeatureName": {
         "primary": "Primary Contact Name",
         "secondary": "Secondary Contact or null",
         "notes": "Optional notes"
       }
     },
     "specialAreas": {
       "triageOnly": ["area-TriageOnlyExample"],
       "crossFunctional": {
         "area-CrossTeam": "org/related-repo"
       }
     },
     "lastUpdated": "YYYY-MM"
   }
   ```

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

3. Review highlighted issues and their scores

4. Copy output to team communication channel (Teams, email, wiki)

### Workflow 2: Analyze a Specific Feature Area

1. Get area-specific issues:
   ```powershell
   gh issue list --repo microsoft/WindowsAppSDK --label "area-Notification" --state open --json number,title,labels,reactionGroups,createdAt,comments
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
   ./scripts/Get-AreaContacts.ps1 -Area "area-Notification" -Update
   ```

## Highlight Scoring Algorithm

Issues are scored (0-100) based on multiple factors. See [scoring-algorithm.md](./references/scoring-algorithm.md) for complete details.

### Quick Reference: Score Factors

| Factor | Weight | Description |
|--------|--------|-------------|
| **Reactions** | 30 | Total reactions (👍, ❤️, 🚀, etc.) indicate community interest |
| **Age** | 25 | Older untriaged issues get higher priority |
| **Comments** | 20 | Active discussion indicates importance |
| **Severity** | 15 | Labels like `bug`, `regression`, `crash` increase score |
| **Blockers** | 10 | Issues blocking other work get prioritized |

### Highlight Labels (Output)

The report adds reason labels to highlighted issues:

| Label | Meaning |
|-------|---------|
| `🔥 Hot` | High reaction count (community demand) |
| `⏰ Aging` | Open > 90 days without triage |
| `🐛 Regression` | Marked as regression or recent breakage |
| `🚧 Blocker` | Blocking other issues or teams |
| `📈 Trending` | High comment activity recently |
| ` Popular` | Feature proposal with significant support |

## Report Output Format

### Markdown Table (Default)

```markdown
| Feature Area | Area Contact | Open | Triage | Proposals | Closed | Highlights |
|--------------|--------------|------|--------|-----------|--------|------------|
| area-Notification | Vivek Khare | 34 | 8 | 11 | 0 | 🔥 [#2894](link) Hot, ⏰ [#3001](link) Aging |
| area-Widgets | Pranav Gupta | 21 | 10 | 4 | 0 | 📈 [#3958](link) Trending |
```

### Special Status Indicators

| Indicator | Meaning |
|-----------|---------|
| `0️⃣🐛🥳` | Zero bugs — celebrate! |
| `🆕` | New area (no historical data) |
| `-` | Data not applicable or unavailable |

## Configuration

### Area Contacts

Contact mappings are stored in [area-contacts.md](./references/area-contacts.md). Update this file when team assignments change.

### Custom Scoring Weights

Modify scoring weights in `./scripts/ScoringConfig.json`:

```json
{
  "weights": {
    "reactions": 30,
    "age": 25,
    "comments": 20,
    "severity": 15,
    "blockers": 10
  },
  "thresholds": {
    "hot_reactions": 10,
    "aging_days": 90,
    "trending_comments": 5
  }
}
```

## Troubleshooting

| Symptom | Solution |
|---------|----------|
| `gh: command not found` | Install GitHub CLI: `winget install GitHub.cli` |
| `authentication required` | Run `gh auth login` and follow prompts |
| Rate limit exceeded | Wait or use `--limit` to reduce API calls |
| Missing area label | Issue may use non-standard label; check label list |
| Contact not found | Update [area-contacts.md](./references/area-contacts.md) |

## Common Commands Reference

```powershell
# List all area labels
gh label list --repo microsoft/WindowsAppSDK --search "area-" --json name

# Get issue details with reactions
gh issue view 4651 --repo microsoft/WindowsAppSDK --json number,title,labels,reactionGroups,createdAt,comments,author

# List issues needing triage
gh issue list --repo microsoft/WindowsAppSDK --label "needs-triage" --state open --json number,title,labels

# Export all open issues to JSON
gh issue list --repo microsoft/WindowsAppSDK --state open --limit 1000 --json number,title,labels,reactionGroups,createdAt,comments,author
```

## References

- [Scoring Algorithm Details](./references/scoring-algorithm.md) — Complete scoring methodology
- [Area Contacts](./references/area-contacts.md) — Feature area ownership mapping
- [Report Template](./templates/report-template.md) — Customizable output template
