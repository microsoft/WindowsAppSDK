# ScoringConfig.json and Assessment-Driven Scoring

This document describes the scoring model implemented by:

- `./scripts/ReportLib.ps1`
- `./scripts/Get-HighlightScore.ps1`
- `./scripts/Generate-FeatureAreaReport.ps1`


## File Location

```text
.github/skills/issue-triage-report/scripts/ScoringConfig.json
```

## Top-Level Config Structure

```jsonc
{
  "weights": { ... },
  "thresholds": { ... },
  "labelPriority": [ ... ],      // optional, currently not used for label ordering
  "maxLabelsPerIssue": 2,
  "severityMultipliers": { ... }
}
```

## weights

`weights` controls how strongly each signal contributes.

| Field | Type | Description |
|---|---|---|
| `reactions` | double | Multiplier for total GitHub reactions. |
| `age` | double | Multiplier for issue age in days. |
| `comments` | double | Multiplier for comment count. |
| `severity` | double | Base severity points, scaled by `severityMultipliers` tier. |
| `blockers` | double | Blocker points when assessment sets `isBlocker=true`. |

### Factor formulas

```text
reactionsPts = floor(weights.reactions * rawReactions)
agePts       = floor(weights.age * rawAgeDays)
commentsPts  = floor(weights.comments * rawComments)
severityPts  = weights.severity * severityMultipliers[severityTier]
blockerPts   = (isBlocker and weights.blockers > 0) ? weights.blockers : 0
```

## Assessment sources and precedence

Severity and blocker values are sourced from JSON assessments, not issue labels.

1. Baseline assessments (highest precedence, human-edited):
  - `./references/IssueAssessments.json`
2. Runtime agent assessments:
  - `./references/AgentAssessments.json`

Both loaders are fail-soft:

- Missing file: warning/status, continue.
- Malformed JSON: warning/status, continue.
- Missing `assessments` object: warning/status, continue.

If both files include the same issue number, `IssueAssessments.json` is used for that issue.

## thresholds

`thresholds` control highlight badges only, not numeric score math.

```json
"thresholds": {
  "aging_days": 90,
  "trending_comments": 10,
  "trending_days": 14,
  "popular_reactions": 5
}
```

| Field | Used by | Meaning |
|---|---|---|
| `aging_days` | `⏰ Aging` | Issue age must be greater than this and issue must have `needs-triage`. |
| `trending_comments` | `📈 Trending` | Minimum comment count. |
| `trending_days` | `📈 Trending` | Maximum days since `updatedAt`. |
| `popular_reactions` | `🌟 Popular` | Minimum total reactions. |

## Highlight label assignment

Current implementation in `Get-HighlightLabels` applies labels in fixed order:

1. `🌟 Popular`
2. `⏰ Aging`
3. `📈 Trending`

Then it trims to `maxLabelsPerIssue`.

`labelPriority` is loaded by `Get-ScoringConfig` but is currently not used to drive ordering in `Get-HighlightLabels`.

## maxLabelsPerIssue

```json
"maxLabelsPerIssue": 2
```

Caps badge count per issue after labels are evaluated.

## severityMultipliers

`severityMultipliers` maps assessment tiers to a multiplier applied to `weights.severity`.

```json
"severityMultipliers": {
  "critical": 1.0,
  "high": 0.8,
  "medium": 0.5,
  "low": 0.2,
  "none": 0.0
}
```

| Tier | Formula |
|---|---|
| `critical` | `weights.severity * 1.0` |
| `high` | `weights.severity * 0.8` |
| `medium` | `weights.severity * 0.5` |
| `low` | `weights.severity * 0.2` |
| `none` | `weights.severity * 0.0` |

## Composite score formula

```text
Total = int(reactionsPts) + int(agePts) + int(commentsPts) + int(severityPts) + int(blockerPts)
```

Important implementation detail:

- `reactionsPts`, `agePts`, and `commentsPts` are already integer via `floor(...)`.
- `severityPts` and `blockerPts` are cast to int during total calculation.
- With default config (`weights.severity = 0.1`, `weights.blockers = 0`), severity and blocker typically contribute `0` to total.

If you want severity/blocker to affect ranking, configure values that survive integer truncation (for example, `weights.severity >= 1` and `weights.blockers >= 1`).

## Worked example (default config)

Issue values:

- reactions: `25`
- age days: `120`
- comments: `8`
- assessment severity tier: `high`
- assessment blocker: `false`

Computation:

| Factor | Calculation | Points |
|---|---|---|
| Reactions | `floor(0.3 * 25)` | `7` |
| Age | `floor(0.3 * 120)` | `36` |
| Comments | `floor(0.3 * 8)` | `2` |
| Severity | `0.1 * 0.8 = 0.08 -> int(0.08)` | `0` |
| Blockers | `false` | `0` |
| **Total** | | **45** |

## Validation rules enforced by Get-ScoringConfig

`Get-ScoringConfig` throws on load if required schema is missing.

| Rule | Error shape |
|---|---|
| File must be named `ScoringConfig.json` | `ConfigPath must point to ScoringConfig.json` |
| Required sections: `weights`, `thresholds`, `maxLabelsPerIssue`, `severityMultipliers` | `missing required section: '<name>'` |
| Required `weights` fields: `reactions`, `age`, `comments`, `severity`, `blockers` | `'weights' missing required field: '<name>'` |
| Required `thresholds` fields: `aging_days`, `trending_comments`, `trending_days`, `popular_reactions` | `'thresholds' missing required field: '<name>'` |
| Required `severityMultipliers` levels: `critical`, `high`, `medium`, `low`, `none` | `'severityMultipliers' missing required level: '<name>'` |

`labelPriority` is optional.

## Script architecture

```text
ScoringConfig.json
    -> Get-ScoringConfig()
        -> Get-IssueScore()
        -> Get-HighlightLabels()

Get-HighlightScore.ps1
    -> Read-IssueAssessments()
    -> Read-AgentAssessments()
    -> Get-IssueScore()
    -> Get-DetailedIssueScore()
    -> Format-ScoreBreakdown()

Generate-FeatureAreaReport.ps1
    -> Read-IssueAssessments()
    -> Read-AgentAssessments()
    -> Get-IssueScore()
    -> Get-HighlightLabels()
    -> Format report output
```

## Get-IssueScore return shape

```powershell
@{
    Reactions        = [int]
    Age              = [int]
    Comments         = [int]
    Severity         = [double]
    Blockers         = [double]
    Total            = [int]
    RawReactions     = [int]
    RawAge           = [int]
    RawComments      = [int]
    RawUpdateAgeDays = [int]
    SeverityLabel    = [string] # normalized assessment tier
    IsBlocker        = [bool]   # assessment-derived
}
```

## Config to function cross-reference

| Config field | Read by | Effect |
|---|---|---|
| `weights.reactions` | `Get-IssueScore` | Reactions points multiplier |
| `weights.age` | `Get-IssueScore` | Age points multiplier |
| `weights.comments` | `Get-IssueScore` | Comments points multiplier |
| `weights.severity` | `Get-IssueScore` | Base severity points |
| `weights.blockers` | `Get-IssueScore` | Blocker points when assessed blocker |
| `thresholds.aging_days` | `Get-HighlightLabels` | Aging badge cutoff |
| `thresholds.trending_comments` | `Get-HighlightLabels` | Trending badge comment cutoff |
| `thresholds.trending_days` | `Get-HighlightLabels` | Trending badge recency cutoff |
| `thresholds.popular_reactions` | `Get-HighlightLabels` | Popular badge cutoff |
| `maxLabelsPerIssue` | `Get-HighlightLabels` | Badge count cap |
| `severityMultipliers.*` | `Get-IssueScore` | Assessment tier multipliers |
| `labelPriority` | `Get-ScoringConfig` | Loaded, currently unused by label assignment |

## Special report indicators

| Indicator | Meaning |
|---|---|
| `0️⃣🐛🥳` | Feature area has zero open bugs |
| `🆕` | New area with no historical data |
| `N/A` | `area-External` redirect area |
