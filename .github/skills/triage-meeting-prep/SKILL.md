---
name: triage-meeting-prep
description: Prepare weekly triage meeting summary for WinAppSDK Needs-Triage issues. Use when preparing for triage meetings, reviewing Needs-Triage issues, generating diff reports since last triage, summarizing new or updated issues, or creating action item recommendations. Triggers on requests involving triage preparation, Needs-Triage review, meeting summary, triage diff, or weekly issue analysis.
license: Complete terms in LICENSE.txt
---

# Triage Meeting Preparation

This skill helps prepare comprehensive summaries for the twice-weekly WinAppSDK triage meetings. It focuses on issues that **actually need triage attention**:

1. **Needs-Triage WITHOUT area label** — These need area assignment (primary focus)
2. **Closed issues still labeled Needs-Triage** — These need follow-up replies

> **Note**: Open issues with both `Needs-Triage` AND an `area-*` label are **excluded** — they're already triaged and waiting for area team action.

## Research-Backed Analysis

**Every suggestion and reply is backed by research:**

| Research Type | What We Search | Why |
|---------------|----------------|-----|
| 🔍 **Similar Issues** | GitHub issue search | Find duplicates, related bugs, past fixes |
| 💻 **Codebase** | `grep_search`, `semantic_search` | Understand technical context, find workarounds |
| 📚 **Documentation** | `fetch_webpage` on MS docs | Verify known limitations, expected behavior |
| 📜 **Git History** | `git log`, `git blame` | Identify area owners, recent changes |

This ensures:
- Suggested replies are technically accurate
- Workarounds are validated against the codebase
- We reference related issues customers may have missed
- Area assignments are informed by code structure

## Key Outputs: What's Changed Since Last Triage

The skill tracks **four critical categories** for each meeting:

| Category | Description | Action Required |
|----------|-------------|-----------------|
| 🔥 **Hot Issues** | ≥5 increased activity (comments + reactions) | May need priority attention |
| 🆕 **Created This Week** | Issues created since last weekly triage | Review + assign area |
| ⏳ **Older Pending** | Older issues still without area labels | Follow up — why no action? |
| ✅ **Closed (need reply)** | Closed issues with customer follow-up | Draft reply with confidence level |

## When to Use This Skill

**Primary triggers** — Use this skill when:

1. **Preparing for triage meetings** — Generate a summary of issues needing area assignment
2. **Reviewing what's changed** — See the diff of issues since the last triage run
3. **Drafting customer replies** — Get research-backed suggested replies for closed issues
4. **Tracking pending items** — Identify issues that still haven't been actioned from previous meetings

**Anti-patterns** — Do NOT use this skill when:
- Reviewing a single specific issue (use `Get-IssueDetails.ps1` for individual issues)
- General issue searching without triage context
- Non-WinAppSDK repositories

## Prerequisites

- **GitHub CLI (gh)** installed and authenticated (`gh auth login`)
- Access to microsoft/WindowsAppSDK repository
- Previous triage state file for diff comparison: `Generated Files/triageMeeting/previous-state.json`

### Installing GitHub CLI

```powershell
# Windows
winget install GitHub.cli

# Then authenticate
gh auth login
```

## Step-by-Step Workflow

### Workflow: Generate Triage Meeting Summary

1. **Load previous triage state** from `Generated Files/triageMeeting/previous-state.json`
2. **Fetch current Needs-Triage issues** using the scripts:
   ```powershell
   # Get all issues needing triage (no area label)
   ./.github/skills/triage-meeting-prep/scripts/Get-TriageIssues.ps1 -NoAreaOnly -OutputFormat summary
   
   # Or get JSON for processing
   $issues = ./.github/skills/triage-meeting-prep/scripts/Get-TriageIssues.ps1 -NoAreaOnly | ConvertFrom-Json
   ```
3. **Categorize issues by creation date**:
   - 🆕 **Created This Week** — `createdAt` ≥ last weekly triage date
   - ⏳ **Older Pending** — `createdAt` < last weekly triage date
4. **For each no-area issue**, analyze using `Get-IssueDetails.ps1`:
   - Run: `./Get-IssueDetails.ps1 -IssueNumber <number> -OutputFormat summary`
   - Review the issue body, comments, and labels
5. **Generate summary report** with links to each issue's `overview.md`
6. **Save current state** for next diff comparison

> **Important**: Every issue without an area label gets a review. The summary links to each review file.

## Output Structure

All outputs are saved to `Generated Files/triageMeeting/<date>/`:

| File | Purpose |
|------|---------|
| `summary.md` | Main meeting document with tables linking to individual reviews |
| `previous-state.json` | State snapshot for next diff (auto-generated) |

Individual issue reviews are saved to `Generated Files/issueReview/<issue-number>/`:

| File | Purpose |
|------|---------|
| `overview.md` | Full issue analysis with scores and suggested actions (linked from summary) |
| `implementation-plan.md` | Technical implementation details (if applicable) |

> **Key Output**: The `summary.md` includes the **Suggested Actions** section extracted from each issue's `overview.md`.

## Detailed Workflow

See [workflow-triage-prep.md](./references/workflow-triage-prep.md) for the complete step-by-step process.

## Issue Categories

| Category | Definition | Action Needed |
|----------|------------|---------------|
| 🔥 **Hot Issues** | ≥5 combined new comments + reactions since last triage | May need priority attention |
| 🆕 **Created This Week** | `createdAt` is after last weekly triage date | Use `Get-IssueDetails.ps1` + assign area |
| ⏳ **Older Pending** | Created before this week, still no area label | Follow up — why not actioned? |
| ✅ **Resolved** | In previous state, NOT in current | Acknowledge (got area label or closed) |
| 🏷️ **Closed (cleanup)** | Closed + still has `Needs-Triage` label | Remove `Needs-Triage` label |

> **Key distinction**: "Created This Week" is based on when the issue was **created** (`createdAt`), not when it was first seen in triage runs. This ensures new issues are highlighted even if triage runs multiple times per week.

## Summary.md Format

See [template-summary.md](./templates/template-summary.md) for the full template structure.

## Action Item Types

| Action | When to Suggest |
|--------|-----------------|
| `Assign to milestone` | High business importance, clear scope |
| `Add area label` | Missing component/area identification |
| `Request clarification` | Requirement clarity < 50 |
| `Close as duplicate` | Similar closed issue found with fix |
| `Close as by-design` | Expected behavior, not a bug |
| `Needs investigation` | Repro unclear, needs debugging |
| `Ready for work` | Clear requirements, assignable |

## Troubleshooting

| Symptom | Solution |
|---------|----------|
| No previous state file | First run — all issues shown as "New" |
| `gh` CLI not installed | Run `winget install GitHub.cli` then `gh auth login` |
| `gh` not authenticated | Run `gh auth login` and follow the prompts |
| Rate limited | Wait and retry, or reduce `--limit` parameter |
| Missing issue details | Use `Get-IssueDetails.ps1 -IssueNumber <number>` |

## Related Resources

- [GitHub CLI documentation](https://cli.github.com/manual/) — `gh` CLI reference
- [Scripts README](./scripts/) — PowerShell scripts for data fetching
