# ScoringConfig.json – Field-by-Field Guide

This document explains every field in [`ScoringConfig.json`](../scripts/ScoringConfig.json) so you can tune issue highlight scoring without reading the PowerShell source. The config is loaded (and strictly validated) by `Get-ScoringConfig` in [`ReportLib.ps1`](../scripts/ReportLib.ps1).

> **All fields are required.** The loader throws if any section or field is missing — there are no hidden defaults.

---

## File Location

```
.github/skills/issue-triage-report/scripts/ScoringConfig.json
```

---

## Top-Level Structure

```jsonc
{
  "weights":          { ... },   // How much each scoring factor matters (points)
  "thresholds":       { ... },   // Numeric cutoffs for highlight labels
  "labelPriority":    [ ... ],   // Order for assigning highlight labels
  "maxLabelsPerIssue": 2,        // Cap on highlight labels per issue
  "severityLabels":   { ... }    // Maps GitHub labels → severity tiers
}
```

---

## `weights` – Scoring Factor Points

Controls how many points each factor can contribute to the 0–100 composite score. The values **must** sum to 100 (or less, if you intentionally disable a factor by setting it to 0).

| Field | Type | Description |
|-------|------|-------------|
| `reactions` | int | Max points from GitHub reaction count (👍 ❤️ 🚀 👀 🎉 😕 😄). Higher reaction counts award a larger fraction of this value. |
| `age` | int | Max points from issue age (days since creation). Older untriaged issues score higher. |
| `comments` | int | Max points from comment count. More discussion → higher score. |
| `severity` | int | Reserved for agent or human assessment integration (Phase 2). Deterministic scripts assign 0 in Phase 1. |
| `blockers` | int | Reserved for agent or human assessment integration (Phase 2). Deterministic scripts assign 0 in Phase 1. |

### How points are awarded within each factor

The scoring engine divides each factor's weight into brackets. For example, with `"reactions": 30`:

| Raw Reactions | % of Weight | Points Awarded |
|---------------|-------------|----------------|
| 0 | 0% | 0 |
| 1–4 | 20% | 6 |
| 5–9 | 40% | 12 |
| 10–19 | 60% | 18 |
| 20–49 | 80% | 24 |
| 50+ | 100% | 30 |

The same 20/25/40/50/67/75/80/100% bracket pattern applies to `age` and `comments`. Changing the weight value scales all brackets proportionally.

In Phase 1, deterministic scoring does not add points from severity or blockers.

### Tuning tips

- **Emphasize community signal**: Increase `reactions` and `comments`, decrease `age`.
- **Prioritize backlog hygiene**: Increase `age`.
- **Prepare for agent overrides**: Keep `severity` and `blockers` configured for Phase 2 even though deterministic scripts keep them at 0 in Phase 1.

---

## `thresholds` – Highlight Label Cutoffs

These values control when an issue earns a highlight label (🌟 Popular, ⏰ Aging, 📈 Trending). They do **not** affect the numeric score directly — only whether a label badge appears.

```json
"thresholds": {
  "aging_days":        90,
  "trending_comments": 10,
  "trending_days":     14,
  "popular_reactions":  5
}
```

| Field | Type | Used By | Description |
|-------|------|---------|-------------|
| `aging_days` | int | ⏰ Aging | Issue must be open longer than this **and** carry the `needs-triage` label to get the Aging badge. |
| `trending_comments` | int | 📈 Trending | Minimum comment count required for the Trending badge. |
| `trending_days` | int | 📈 Trending | Issue must have been updated within this many days **and** meet `trending_comments` to qualify. Ensures "trending" means trending *now*, not historically. |
| `popular_reactions` | int | 🌟 Popular | Minimum total reactions to earn the Popular badge. |

### Tuning tips

- **Tighter Trending window**: Lower `trending_days` to 7 to surface only very recent activity.
- **Broader Popular threshold**: Lower `popular_reactions` to 3 if your repo gets fewer reactions.
- **Stricter Aging**: Raise `aging_days` to 180 if a 90-day backlog is normal.

---

## `labelPriority` – Highlight Label Order

Determines which highlight labels are assigned first when an issue qualifies for more than `maxLabelsPerIssue` labels. Labels earlier in the array win.

In Phase 1, scripts emit only `popular`, `aging`, and `trending` labels. Legacy entries such as `regression` and `blocker` may remain in config for forward compatibility.

```json
"labelPriority": [
  "regression",
  "blocker",
  "popular",
  "aging",
  "trending"
]
```

| Position | Internal Name | Display Label | Condition |
|----------|---------------|---------------|-----------|
| 1 | `popular` | 🌟 Popular | Reactions ≥ `thresholds.popular_reactions` |
| 2 | `aging` | ⏰ Aging | Days open > `thresholds.aging_days` AND has `needs-triage` label |
| 3 | `trending` | 📈 Trending | Comments ≥ `thresholds.trending_comments` AND updated within `thresholds.trending_days` |

### Example

An issue with 20 reactions, open for 120 days with `needs-triage`, and 15 comments qualifies for Popular, Aging, and Trending. With `maxLabelsPerIssue: 2`, it receives the first two labels by configured priority.

---

## `maxLabelsPerIssue` – Label Cap

```json
"maxLabelsPerIssue": 2
```

Maximum number of highlight labels attached to any single issue. After the engine evaluates all conditions (in `labelPriority` order), it keeps only the first N labels. Increase this if you want richer badge detail; decrease to keep reports cleaner.

---

## `severityLabels` – Reserved for Agent Overrides (Phase 2)

Maps GitHub issue label strings to severity tiers for future override workflows.

In Phase 1, deterministic scripts do not derive severity from labels. Keep this section configured so Phase 2 can ingest agent assessments without reworking configuration.

```json
"severityLabels": {
  "critical": ["regression", "crash", "hang", "data-loss", "P0"],
  "high":     ["bug", "P1"],
  "medium":   ["performance", "feature proposal", "feature-proposal", "P2"],
  "low":      ["documentation", "enhancement", "P3"]
}
```

| Tier | Intended use |
|------|--------------|
| `critical` | Regressions, crashes, data loss |
| `high` | Serious functionality bugs |
| `medium` | Performance issues, feature proposals |
| `low` | Docs, enhancements |

### Customization

- **Add a label**: Append it to the appropriate tier array (e.g., add `"memory-leak"` to `critical`).
- **Reclassify a label**: Move it between tier arrays.
- **Support custom P-labels**: The arrays already include `P0`–`P3`; add `P4`, `P5`, etc. to `low` if needed.
- **Order within a tier** doesn't matter — the engine matches the first label found on the issue against all tiers, checking from `critical` down to `low`.

---

## Composite Score Formula

```
Total = reactions_pts + age_pts + comments_pts + severity_pts + blockers_pts

Phase 1 deterministic scripts compute:

Total = reactions_pts + age_pts + comments_pts

because `severity_pts = 0` and `blockers_pts = 0` until agent override ingestion is added in Phase 2.
```

### Worked Example

Issue #2894 with 25 reactions, open 120 days, 8 comments:

| Factor | Raw | Bracket | Points |
|--------|-----|---------|--------|
| Reactions | 25 | 20–49 → 80% | 24/30 |
| Age | 120 days | 91–180 → 75% | 22/30 |
| Comments | 8 | 6–10 → 67% | 20/30 |
| Severity | — | Phase 1 deterministic (disabled) | 0/10 |
| Blockers | — | Phase 1 deterministic (disabled) | 0/0 |
| **Total** | | | **66/100** |

---

## Agent Content Assessment

Deterministic scripts in this skill do not compute severity, blocker status, or confidence values. They produce score, score breakdown, and highlight labels only.

If a final report includes annotations such as `[severity:high]`, `[blocker:no]`, and `[confidence:85]`, those values must be assigned by the agent after reviewing title, body, labels, and recent discussion.

Recommended severity rubric:

| Tier | Meaning |
|------|---------|
| `critical` | Crash, data loss, or severe regression with broad impact |
| `high` | Major scenario broken with limited/no workaround |
| `medium` | User-visible defect with reasonable workaround |
| `low` | Minor functional or quality issue |
| `none` | No clear severity signal in issue content |

Recommended blocker rule:

- Use `[blocker:yes]` only when issue text clearly indicates blocked-by or blocking-release dependency.
- Otherwise use `[blocker:no]`.

Recommended rubric:

| Score | Level | Meaning |
|-------|-------|---------|
| **80-100** | High | Strong textual and scoring evidence supports highlighting the issue |
| **60-79** | Medium-High | Good support with limited ambiguity |
| **40-59** | Medium | Plausible highlight, but evidence is mixed or incomplete |
| **20-39** | Low | Weak supporting context beyond the numeric score |
| **0-19** | Very Low | The agent cannot confidently defend the highlight |

```powershell
# Find high-confidence highlights in an agent-reviewed report
Select-String -Path report.md -Pattern '\[confidence:[89][0-9]\]'

# Find low-confidence highlights in an agent-reviewed report
Select-String -Path report.md -Pattern '\[confidence:[0-4][0-9]\]'
```

---

## Validation Rules

`Get-ScoringConfig` in `ReportLib.ps1` enforces these constraints at load time — if any fail, the script throws immediately:

| Rule | Error if violated |
|------|-------------------|
| File must be named `ScoringConfig.json` | `ConfigPath must point to ScoringConfig.json` |
| Top-level sections `weights`, `thresholds`, `maxLabelsPerIssue`, `severityLabels` must all exist | `missing required section: '<name>'` |
| `weights` must contain: `reactions`, `age`, `comments`, `severity`, `blockers` | `'weights' missing required field: '<name>'` |
| `thresholds` must contain: `aging_days`, `trending_comments`, `trending_days`, `popular_reactions` | `'thresholds' missing required field: '<name>'` |
| `severityLabels` must contain: `critical`, `high`, `medium`, `low` | `'severityLabels' missing required level: '<name>'` |

`labelPriority` is the only optional field — if omitted, highlight labels are still assigned by the hardcoded priority in `Get-HighlightLabels`.

---

## Script Architecture & Function Reference

The deterministic scoring scripts dot-source `ReportLib.ps1` and load `ScoringConfig.json` through `Get-ScoringConfig`.

```
ScoringConfig.json
       │
       ▼
 Get-ScoringConfig()          ◄── ReportLib.ps1 (shared library)
       │
       ├──► Get-IssueScore()       scores one issue (canonical math)
       └──► Get-HighlightLabels()  assigns badge labels
              │
       ┌──────┴──────────────────────────────────┐
       ▼                                         ▼
 Get-HighlightScore.ps1                Generate-FeatureAreaReport.ps1
 (single-issue CLI tool)               (full report pipeline)
       │                                         │
       ▼                                         ▼
 Get-DetailedIssueScore()              Get-HighlightedIssues()
 Format-ScoreBreakdown()               Format-ReportMarkdown()

 Validate-FeatureAreaReport.ps1        Get-AreaContacts.ps1
 (live issue counts — no scoring)      (contact lookup — no scoring)

Agent review happens after these scripts run. Confidence is an agent-authored annotation, not part of the PowerShell pipeline.
```

---

### `ReportLib.ps1` — Shared Library

Location: `./scripts/ReportLib.ps1`

All scoring math lives here. Other scripts call these functions — they never duplicate the logic.

#### Core Functions

| Function | Purpose | Config Fields Read |
|----------|---------|-------------------|
| `Get-ScoringConfig` | Loads and validates `ScoringConfig.json`. Returns a hashtable consumed by every other function. | All fields (validation only) |
| `Get-IssueScore` | **Canonical scorer.** Takes one issue + config, returns a hashtable with per-factor scores (`Reactions`, `Age`, `Comments`, `Severity`, `Blockers`), raw values, and `Total`. | `weights.*`, `severityLabels.*` |
| `Get-HighlightLabels` | Evaluates label conditions and returns up to `maxLabelsPerIssue` badge strings (e.g., `🌟 Popular`). Checks in `labelPriority` order. | `thresholds.*`, `maxLabelsPerIssue` |

#### Helper Functions

| Function | Purpose |
|----------|---------|
| `Get-TotalReactions` | Sums `users.totalCount` across all `reactionGroups` on an issue. |
| `Get-IssueAgeInDays` | Calculates `(UTC now − createdAt)` in whole days. |
| `Test-HasLabel` | Exact-match check for a single label name on an issue. |
| `Test-HasLabelMatching` | Regex-match check for a label pattern (e.g., `block\|blocker`). |
| `Format-IssueLink` | Returns `[#NNN](url)` markdown link. |

#### `Get-IssueScore` Return Shape

```powershell
@{
    Reactions      = [int]    # Points awarded (0 – weights.reactions)
    Age            = [int]    # Points awarded (0 – weights.age)
    Comments       = [int]    # Points awarded (0 – weights.comments)
    Severity       = [int]    # Points awarded (0 – weights.severity)
    Blockers       = [int]    # Points awarded (0 – weights.blockers)
    Total          = [int]    # Sum of above
    RawReactions   = [int]    # Actual reaction count
    RawAge         = [int]    # Days since creation
    RawComments    = [int]    # Actual comment count
    RawUpdateAgeDays = [int]  # Days since last update
    SeverityLabel  = [string] # First matching severity label (e.g., "bug")
    IsBlocker      = [bool]   # True if any label matches block|blocker|blocking
}
```

---

### `Get-HighlightScore.ps1` — Single-Issue Scorer

Location: `./scripts/Get-HighlightScore.ps1`

CLI tool that fetches one issue from GitHub and displays its score breakdown.

#### Functions

| Function | Purpose |
|----------|---------|
| `Get-DetailedIssueScore` | Wraps `Get-IssueScore` (ReportLib) and adds presentation metadata — reason strings (e.g., `"🌟 Popular (community interest)"`) and `MaxScore` per factor. Does **not** duplicate scoring math. |
| `Format-ScoreBreakdown` | Renders the visual bar-chart output (`█░`) with factor-by-factor breakdown, total score, and a priority recommendation (HIGH / MEDIUM / NORMAL / LOW). |

#### Usage

```powershell
# Quick score
./scripts/Get-HighlightScore.ps1 -IssueNumber 4651

# Detailed breakdown with visual bars
./scripts/Get-HighlightScore.ps1 -IssueNumber 4651 -Verbose

# Custom config path
./scripts/Get-HighlightScore.ps1 -IssueNumber 4651 -ConfigPath .\custom-config.json
```

#### Output (Verbose)

```
═══════════════════════════════════════════════════════════
  Issue #4651: Example issue title
═══════════════════════════════════════════════════════════

  SCORE BREAKDOWN:
  ───────────────────────────────────────────────────────
  Reactions    [████░░░░░░] 12/30  (raw: 7)
               └─ 🌟 Popular (community interest)
  Age          [██████████] 30/30  (raw: 200)
               └─ ⏰ Aging (needs triage for 200 days)
  Comments     [████████░░] 20/30  (raw: 8)
  Severity     [████████░░]  8/10  (raw: bug)
               └─ 🟠 High: bug
  ───────────────────────────────────────────────────────
       TOTAL SCORE: 70 / 100

  Recommendation: 🔴 HIGH PRIORITY - Should be highlighted in triage report
```

---

### `Generate-FeatureAreaReport.ps1` — Report Pipeline

Location: `./scripts/Generate-FeatureAreaReport.ps1`

Generates the full Feature Area Status report by iterating every `area-*` label.

#### Data Flow

```
1. Get-AllAreaLabels          Fetch all area-* labels from the repo
       │
2. Get-IssuesForArea          For each area, fetch open (and optionally closed) issues
       │
3. Get-IssueStats             Count totals, needs-triage, proposals, bugs per area
       │
4. Get-HighlightedIssues      Score every issue via Get-IssueScore (ReportLib),
       │                      assign labels via Get-HighlightLabels (ReportLib),
       │                      sort descending, take top N
       │
5. Format-HighlightsMarkdown  Format highlights as "🌟 [#NNN](url)"
       │
6. Format-ReportMarkdown      Assemble the final markdown table with all areas
```

#### Functions

| Function | Purpose | Calls from ReportLib |
|----------|---------|---------------------|
| `Get-AllAreaLabels` | Discovers `area-*` labels via `Get-RepositoryLabels.ps1` (from the triage-meeting-prep skill). | — |
| `Get-IssuesForArea` | Fetches issues for one area label using `gh issue list`. | — |
| `Get-IssueStats` | Counts open, needs-triage, proposals, and bugs from label names. | — |
| `Get-HighlightedIssues` | Orchestrator: scores all issues, assigns labels, sorts, and returns top N. | `Get-IssueScore`, `Get-HighlightLabels` |
| `Format-HighlightsMarkdown` | Joins highlight entries into a comma-separated markdown string. | — |
| `Format-ReportMarkdown` | Builds the full markdown table with header, rows, and special-case handling (zero bugs, external area). | — |

#### Usage

```powershell
# Default markdown report
./scripts/Generate-FeatureAreaReport.ps1

# JSON output with 5 highlights per area
./scripts/Generate-FeatureAreaReport.ps1 -OutputFormat json -HighlightCount 5

# Include recently closed issues
./scripts/Generate-FeatureAreaReport.ps1 -IncludeClosed
```

---

### `Validate-FeatureAreaReport.ps1` — Live Counts

Location: `./scripts/Validate-FeatureAreaReport.ps1`

Queries live issue counts per area and prints a formatted console table. **Does not use `ScoringConfig.json` or any scoring functions** — it only counts open, needs-triage, proposal, and closed (30-day) issues.

Use this script to sanity-check raw numbers before interpreting scored highlights.

---

### `Get-AreaContacts.ps1` — Contact Lookup

Location: `./scripts/Get-AreaContacts.ps1`

Manages the area → contact mapping. **Does not use `ScoringConfig.json`** — it reads from `area-contacts.json` (user copy at `.user/issue-triage-report/area-contacts.json`, template at `references/area-contacts.json`).

---

## Config → Function Cross-Reference

Quick lookup: which function reads which `ScoringConfig.json` field.

| Config Field | Read By | Effect |
|---|---|---|
| `weights.reactions` | `Get-IssueScore` | Max points for reaction count |
| `weights.age` | `Get-IssueScore` | Max points for issue age |
| `weights.comments` | `Get-IssueScore` | Max points for comment count |
| `weights.severity` | `Get-IssueScore` | Max points for severity label match |
| `weights.blockers` | `Get-IssueScore` | Max points for blocker labels (0 = disabled) |
| `thresholds.aging_days` | `Get-HighlightLabels` | Minimum days to qualify for ⏰ Aging badge |
| `thresholds.trending_comments` | `Get-HighlightLabels` | Minimum comments to qualify for 📈 Trending badge |
| `thresholds.trending_days` | `Get-HighlightLabels` | Maximum days since update to qualify for 📈 Trending badge |
| `thresholds.popular_reactions` | `Get-HighlightLabels` | Minimum reactions to qualify for 🌟 Popular badge |
| `labelPriority` | `Get-HighlightLabels` | Order of label assignment when issue qualifies for multiple |
| `maxLabelsPerIssue` | `Get-HighlightLabels` | Cap on badges per issue |
| `severityLabels.critical` | `Get-IssueScore` | Labels that earn 100% of `weights.severity` |
| `severityLabels.high` | `Get-IssueScore` | Labels that earn 80% of `weights.severity` |
| `severityLabels.medium` | `Get-IssueScore` | Labels that earn 50% of `weights.severity` |
| `severityLabels.low` | `Get-IssueScore` | Labels that earn 20% of `weights.severity` |

---

## Special Report Indicators

These are not configured in `ScoringConfig.json` but appear in report output:

| Indicator | Meaning |
|-----------|---------|
| `0️⃣🐛🥳` | Feature area has zero open bugs |
| `🆕` | New area with no historical data |
| `N/A` | `area-External` — issues pending redirection to other teams |
