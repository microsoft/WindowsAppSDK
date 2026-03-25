# Issue Highlight Scoring Algorithm

This document describes the scoring algorithm used to identify high-priority issues that should be highlighted in the Feature Area Status report.

## Overview

Each open issue receives a score from 0-100 based on weighted factors. Issues with the highest scores per feature area are marked as highlights with descriptive labels indicating why they're important.

Each score also includes a **confidence value** (0-100) in the format `[confidence:XX]` indicating how reliable the score is based on data completeness.

## Scoring Factors

### 1. Reactions (Weight: 30 points max)

Community engagement measured by GitHub reactions (👍, ❤️, 🚀, 👀, 🎉, 😕, 😄).

| Reactions | Score |
|-----------|-------|
| 0 | 0 |
| 1-4 | 6 |
| 5-9 | 12 |
| 10-19 | 18 |
| 20-49 | 24 |
| 50+ | 30 |

**Rationale**: High reaction counts indicate community demand and widespread impact.

**Highlight Label**: `🌟 Popular` when reactions ≥ 5

---

### 2. Age (Weight: 30 points max)

Time since issue was created, with higher scores for older untriaged issues.

| Days Open | Score |
|-----------|-------|
| 0-30 | 0 |
| 31-60 | 7 |
| 61-90 | 15 |
| 91-180 | 22 |
| 181+ | 30 |

**Rationale**: Older issues without resolution deserve attention to prevent backlog growth.

**Highlight Label**: `⏰ Aging` when days > 90 AND has `needs-triage` label

---

### 3. Comments (Weight: 30 points max)

Discussion activity measured by comment count.

| Comments | Score |
|----------|-------|
| 0 | 0 |
| 1-2 | 6 |
| 3-5 | 12 |
| 6-10 | 20 |
| 11+ | 30 |

**Rationale**: Active discussions indicate ongoing relevance and potential blockers.

**Highlight Label**: `📈 Trending` when comments ≥ 5 AND recent activity (shows the issue is trending NOW)

---

### 4. Severity Labels (Weight: 10 points max)

Priority based on issue labels indicating severity or type. Supports P-scale labels.

| Severity Tier | Labels | Score |
|---------------|--------|-------|
| Critical | `regression`, `crash`, `hang`, `data-loss`, `security`, `P0` | 10 |
| High | `bug`, `P1` | 8 |
| Medium | `performance`, `feature proposal`, `feature-proposal`, `P2` | 5 |
| Low | `documentation`, `enhancement`, `P3` | 2 |
| None | None of above | 0 |

**Rationale**: Regressions, crashes, and security issues have direct user impact.

**Highlight Labels**:
- `🐛 Regression` when has `regression` label
- (Other severity shown in score, not separate label)

---

### 5. Blocker Status (Weight: 0 points - disabled)

Previously tracked issues blocking other work. Now disabled to make room for equal weighting of reactions, age, and comments.

**Highlight Label**: `🚧 Blocker` when has blocking indicators (still shown as highlight even with 0 weight)

---

## Composite Score Calculation

```
Total Score = Reactions + Age + Comments + Severity
            = 30 + 30 + 30 + 10 = 100 max
```

### Example Calculation

Issue #2894:
- Reactions: 25 → 24 points (80% of 30)
- Age: 120 days → 22 points (91-180 bracket)
- Comments: 8 → 20 points (6-10 bracket)
- Labels: `bug` (P1 equivalent) → 8 points

**Total**: 24 + 22 + 20 + 8 = **74/100**

---

## Confidence Scoring

Each score includes a confidence value indicating data reliability:

### Confidence Factors

| Factor | Points |
|--------|--------|
| Has reactions data | +15 |
| Has comments data | +15 |
| Has labels | +15 |
| Has created date | +15 |
| Score ≥ 60 (clear priority) | +25 |
| Score 40-59 | +15 |
| Score 20-39 | +10 |
| 3+ factors contributing | +15 |
| 2 factors contributing | +10 |

**Output Format**: `[confidence:85]` — grep-friendly for filtering high-confidence items.

### Example

```bash
# Find high-confidence highlights (80+)
grep "\[confidence:[89][0-9]\]" report.md

# Find low-confidence items (below 50)
grep "\[confidence:[0-4][0-9]\]" report.md
```

```powershell
# Find high-confidence highlights (80+)
Select-String -Path report.md -Pattern '\[confidence:[89][0-9]\]'

# Find low-confidence items (below 50)
Select-String -Path report.md -Pattern '\[confidence:[0-4][0-9]\]'

# Count issues by confidence range
Get-Content report.md | Select-String '\[confidence:(\d+)\]' -AllMatches | 
    ForEach-Object { $_.Matches.Groups[1].Value } | 
    Group-Object { [math]::Floor([int]$_ / 10) * 10 } | 
    Sort-Object Name
```

---

## Highlight Label Assignment

After scoring, assign labels based on the highest-scoring factors:

| Priority | Label | Condition |
|----------|-------|-----------|
| 1 | `🐛 Regression` | Has `regression` label |
| 2 | `🚧 Blocker` | Has blocking indicators |
| 3 | `🌟 Popular` | Reactions ≥ 5 |
| 4 | `⏰ Aging` | Days > 90 + needs-triage |
| 5 | `📈 Trending` | Comments ≥ 10 |

**Rule**: Each issue gets **at most 2 labels** (most relevant based on score contribution).

---

## Special Cases

### Zero Issues (Celebration)

When a feature area has zero open bugs:
- Display: `0️⃣🐛🥳`
- Meaning: Celebrate zero bugs!

### New Area

When a feature area was recently created or has no historical data:
- Display: `🆕`
- Skip historical comparisons

### Redirect Area (area-External)

For `area-External` label (issues to redirect to other teams):
- Display: `N/A` for highlights
- Note: "Current backlog contains issues for redirection to other teams"

---

## Thresholds Configuration

These thresholds can be adjusted in `ScoringConfig.json` (`.github\skills\issue-triage-report\scripts\ScoringConfig.json`)

---

## Usage in Reports

When generating reports:

1. Fetch all open issues per area
2. Calculate scores for each issue
3. Calculate confidence for each score
4. Sort by score descending
5. Take top N issues (default: 3)
6. Assign highlight labels
7. Format for display with confidence

### Output Example

```markdown
| Feature Area | ... | Highlights |
|--------------|-----|------------|
| area-Notification | ... | 🌟 [#2894](link) [confidence:85], ⏰ [#3001](link) [confidence:72] |
```

---

## API Data Requirements

To calculate scores, fetch these fields per issue:

```json
{
  "number": 2894,
  "title": "...",
  "createdAt": "2024-01-15T...",
  "labels": [{"name": "area-Notification"}, {"name": "bug"}],
  "reactionGroups": [
    {"content": "THUMBS_UP", "users": {"totalCount": 12}},
    {"content": "HEART", "users": {"totalCount": 5}}
  ],
  "comments": {"totalCount": 8},
  "author": {"login": "contributor"},
  "linkedIssues": [...]
}
```

GitHub CLI command:
```bash
gh issue list --repo microsoft/WindowsAppSDK --label "area-Notification" --state open --json number,title,createdAt,labels,reactionGroups,comments,author
```
