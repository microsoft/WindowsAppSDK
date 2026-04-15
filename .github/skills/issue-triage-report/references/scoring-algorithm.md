# ScoringConfig.json and Assessment-Driven Scoring

This document describes the scoring model implemented by:

- `./scripts/ReportLib.ps1`
- `./scripts/Get-HighlightScore.ps1`
- `./scripts/Generate-FeatureAreaReport.ps1`

# Get-IssueScore

## Function goals
* A quick, at-a-glance way to gauge an issue's priority
* The ability to factor in numeric criteria (e.g. number of comments, reactions) and other factors that are harder to quantify (severity, blocks other issues)
* A way to condense scores on different scales (e.g. more days have passed than number of reactions on an issue) without larger raw counts disproportionally impacting calculation
* Make it easy to tweak scoring criteria from a single config file

## Composite score formula

```text
Total = min(100, round(reactionsPts + agePts + commentsPts + severityPts + blockerPts, 1))
```
Total is between 0 and 100 so the value approximates priority and can be compared against other issues. But how do we determine how many points each category should get? We consider weight (how much each factor should contribute to the total) and factor level (how many points should this issue get for this category).

```text
CategoryPoints = weight * FactorLevel
```

Let's break those down.

## Weights

`weights` controls how strongly each signal contributes. All weights must sum to `1.0`. We chose 1.0 to match the heuristic of using decimals as percentages.

| Field | Type | Description |
|---|---|---|
| `reactions` | double | Share of total score allocated to reactions. |
| `age` | double | Share of total score allocated to issue age. |
| `comments` | double | Share of total score allocated to comment count. |
| `severity` | double | Base severity points, scaled by `severityMultipliers` tier. |
| `blockers` | double | Blocker points when assessment sets `isBlocker=true`. |

## Factor Levels

Each category calculates their factor level based on what type of data the category captures.

For count-based categories (**reactions**, **age**, and **comments**), we calculate a rank by dividing the count of each category by a ceiling (what amount is significant enough to allocate all possible points for that category) in `ScoringConfig.json`.

```text
reactionsRank = min(1, max(0, rawReactions / rankingCeilings.reactions))
ageRank       = min(1, max(0, rawAgeDays   / rankingCeilings.ageDays))
commentsRank  = min(1, max(0, rawComments  / rankingCeilings.comments))

reactionsPts = round(min(1, max(0, rawReactions / rankingCeilings.reactions)) * weights.reactions * 100, 1)
agePts       = round(ageRank       * weights.age       * 100, 1)
commentsPts  = round(commentsRank  * weights.comments  * 100, 1)
```

We tend to think of issue **severity** in categories like "P0, P1, P2", "high, medium, low", etc. In our script, we use the tiers `critical`, `high`, `medium`, `low`, and `none`. To turn this category into a number of points, we assign each severity tier to a normalized factor, then multiply the corresponding severity multiplier by 100 and by the weight.

```text
severityPts  = round(weights.severity * severityMultipliers[severityTier] * 100, 1)
```

You can adjust the severityMultipliers in the `severityMulitpliers` key of `ScoringConfig.json`.

Unlike the other factors, **isBlocker** is a boolean. To translate it into points, we first determine if the the issue is a blocker and if the weight is non-zero. If both are true, we multiply by the weight times 100 to get the point value. If either is false, no blocker points contribute to the total.

```text
blockerPts   = (isBlocker and weights.blockers > 0) ? round(weights.blockers * 100, 1) : 0
```

## Assessment sources and precedence

Severity and blocker values (not weights or multipliers) are sourced from JSON assessments instead of the GitHub API.

1. Baseline assessments (highest precedence, human-edited):
  - `./references/IssueAssessments.json`
2. Runtime agent assessments:
  - `./references/AgentAssessments.json`

We use two assessment files here to prevent the agent from overwriting human assessments and to track how an agent scored each issue.

Both loaders are fail-soft:

- Missing file: warning/status, continue.
- Malformed JSON: warning/status, continue.
- Missing `assessments` object: warning/status, continue.

If both files include the same issue number, `IssueAssessments.json` is used for that issue.

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

# Highlight labels

## Goals
* Surface top issues for a feature area based on the highlight criteria below

## Highlight label assignment

Current implementation in `Get-HighlightLabels` applies labels in fixed order:

1. `🌟 Popular`
2. `⏰ Aging`
3. `📈 Trending`

Then it trims to `maxLabelsPerIssue` in `ScoringConfig.json` after labels are evaluated.

## thresholds

We use `thresholds` in `ScoringConfig.json` to determine whether a badge should be applied to an issue. Thresholds control highlight badges only, not the points in `Get-IssueScore`.

| Field | Used by | Meaning |
|---|---|---|
| `aging_days` | `⏰ Aging` | Issue age must be greater than this and issue must have `needs-triage`. |
| `trending_comments` | `📈 Trending` | Minimum comment count. |
| `trending_days` | `📈 Trending` | Maximum days since `updatedAt`. |
| `popular_reactions` | `🌟 Popular` | Minimum total reactions. |

## recommendationBands

`recommendationBands` defines fixed score-ratio thresholds used by `Get-HighlightScore.ps1` to classify output priority.

Threshold math:

```text
highThreshold   = maxPossible * recommendationBands.high
mediumThreshold = maxPossible * recommendationBands.medium
normalThreshold = maxPossible * recommendationBands.normal
```

# ScoringConfig.json

## Location

```text
.github/skills/issue-triage-report/scripts/ScoringConfig.json
```

## Top-Level  Structure

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

# Scoring maps

## Script architecture

```text
ScoringConfig.json
    -> (is used in) Get-ScoringConfig()
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
| `N/A` | `area-External` redirect area |
