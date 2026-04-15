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
  "maxLabelsPerIssue": 2,
  "rankingCeilings": { ... },
  "recommendationBands": { ... },
  "severityMultipliers": { ... }
}
```

## weights

`weights` controls how strongly each signal contributes. All weights must sum to `1.0`.

| Field | Type | Description |
|---|---|---|
| `reactions` | double | Share of total score allocated to reactions. |
| `age` | double | Share of total score allocated to issue age. |
| `comments` | double | Share of total score allocated to comment count. |
| `severity` | double | Base severity points, scaled by `severityMultipliers` tier. |
| `blockers` | double | Blocker points when assessment sets `isBlocker=true`. |

### Factor formulas

```text
reactionsRank = min(1, max(0, rawReactions / rankingCeilings.reactions))
ageRank       = min(1, max(0, rawAgeDays   / rankingCeilings.ageDays))
commentsRank  = min(1, max(0, rawComments  / rankingCeilings.comments))

reactionsPts = round(reactionsRank * weights.reactions * 100, 1)
agePts       = round(ageRank       * weights.age       * 100, 1)
commentsPts  = round(commentsRank  * weights.comments  * 100, 1)
severityPts  = round(weights.severity * severityMultipliers[severityTier] * 100, 1)
blockerPts   = (isBlocker and weights.blockers > 0) ? round(weights.blockers * 100, 1) : 0
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

## maxLabelsPerIssue

```json
"maxLabelsPerIssue": 2
```

Caps badge count per issue after labels are evaluated.

## rankingCeilings

`rankingCeilings` defines the raw value where each deterministic factor reaches full normalized rank (`1.0`).

| Field | Used by | Meaning |
|---|---|---|
| `reactions` | `Get-IssueScore` | Raw reaction count at full reactions rank. |
| `ageDays` | `Get-IssueScore` | Open age in days at full age rank. |
| `comments` | `Get-IssueScore` | Comment count at full comments rank. |

Values do not need to sum to anything. They are independent per-factor scales.

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

## recommendationBands

`recommendationBands` defines fixed score-ratio thresholds used by `Get-HighlightScore.ps1` to classify output priority.

Threshold math:

```text
highThreshold   = maxPossible * recommendationBands.high
mediumThreshold = maxPossible * recommendationBands.medium
normalThreshold = maxPossible * recommendationBands.normal
```

These are fixed ratio cutoffs, not statistical percentiles.

## Composite score formula

```text
Total = min(100, round(reactionsPts + agePts + commentsPts + severityPts + blockerPts, 1))
```

Important implementation detail:

- `Total` is a normalized composite in the range `0..100`.
- Deterministic factors (`reactions`, `age`, `comments`) saturate at full credit once they hit their configured ceiling.
- Severity and blocker contribute directly as weighted points in the same `0..100` scale.

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
| Reactions | `round(min(1, 25/10) * 0.3 * 100, 1)` | `30.0` |
| Age | `round(min(1, 120/365) * 0.3 * 100, 1)` | `9.9` |
| Comments | `round(min(1, 8/20) * 0.3 * 100, 1)` | `12.0` |
| Severity | `round(0.1 * 0.8 * 100, 1)` | `8.0` |
| Blockers | `false` | `0` |
| **Total** | `min(100, round(sum, 1))` | **59.9** |

## Validation rules enforced by Get-ScoringConfig

`Get-ScoringConfig` throws on load if required schema is missing.

| Rule | Error shape |
|---|---|
| File must be named `ScoringConfig.json` | `ConfigPath must point to ScoringConfig.json` |
| Required sections: `weights`, `thresholds`, `maxLabelsPerIssue`, `rankingCeilings`, `recommendationBands`, `severityMultipliers` | `missing required section: '<name>'` |
| Required `weights` fields: `reactions`, `age`, `comments`, `severity`, `blockers` | `'weights' missing required field: '<name>'` |
| Required `thresholds` fields: `aging_days`, `trending_comments`, `trending_days`, `popular_reactions` | `'thresholds' missing required field: '<name>'` |
| Required `rankingCeilings` fields: `reactions`, `ageDays`, `comments` | `'rankingCeilings' missing required field: '<name>'` |
| Required `recommendationBands` fields: `high`, `medium`, `normal` | `'recommendationBands' missing required field: '<name>'` |
| Required `severityMultipliers` levels: `critical`, `high`, `medium`, `low`, `none` | `'severityMultipliers' missing required level: '<name>'` |
| `weights` must sum to `1.0` | `'weights' must sum to 1.0` |

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
  Reactions        = [double]
  Age              = [double]
  Comments         = [double]
    Severity         = [double]
    Blockers         = [double]
  Total            = [double]
    RawReactions     = [int]
    RawAge           = [int]
    RawComments      = [int]
    RawUpdateAgeDays = [int]
  ReactionsRank    = [double]
  AgeRank          = [double]
  CommentsRank     = [double]
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
| `rankingCeilings.reactions` | `Get-IssueScore` | Reactions rank saturation point |
| `rankingCeilings.ageDays` | `Get-IssueScore` | Age rank saturation point |
| `rankingCeilings.comments` | `Get-IssueScore` | Comments rank saturation point |
| `thresholds.aging_days` | `Get-HighlightLabels` | Aging badge cutoff |
| `thresholds.trending_comments` | `Get-HighlightLabels` | Trending badge comment cutoff |
| `thresholds.trending_days` | `Get-HighlightLabels` | Trending badge recency cutoff |
| `thresholds.popular_reactions` | `Get-HighlightLabels` | Popular badge cutoff |
| `maxLabelsPerIssue` | `Get-HighlightLabels` | Badge count cap |
| `recommendationBands.high` | `Get-DetailedIssueScore` | High recommendation cutoff ratio |
| `recommendationBands.medium` | `Get-DetailedIssueScore` | Medium recommendation cutoff ratio |
| `recommendationBands.normal` | `Get-DetailedIssueScore` | Normal recommendation cutoff ratio |
| `severityMultipliers.*` | `Get-IssueScore` | Assessment tier multipliers |

## Special report indicators

| Indicator | Meaning |
|---|---|
| `0️⃣🐛🥳` | Feature area has zero open bugs |
| `🆕` | New area with no historical data |
| `N/A` | `area-External` redirect area |
