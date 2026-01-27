# Issue Highlight Scoring Algorithm

This document describes the scoring algorithm used to identify high-priority issues that should be highlighted in the Feature Area Status report.

## Overview

Each open issue receives a score from 0-100 based on weighted factors. Issues with the highest scores per feature area are marked as highlights with descriptive labels indicating why they're important.

## Scoring Factors

### 1. Reactions (Weight: 25 points max)

Community engagement measured by GitHub reactions (👍, ❤️, 🚀, 👀, 🎉, 😕, 😄).

| Reactions | Score |
|-----------|-------|
| 0 | 0 |
| 1-4 | 5 |
| 5-9 | 10 |
| 10-19 | 15 |
| 20-49 | 20 |
| 50+ | 25 |

**Rationale**: High reaction counts indicate community demand and widespread impact.

**Highlight Label**: `🔥 Hot` when reactions ≥ 10

---

### 2. Age (Weight: 20 points max)

Time since issue was created, with higher scores for older untriaged issues.

| Days Open | Score |
|-----------|-------|
| 0-30 | 0 |
| 31-60 | 5 |
| 61-90 | 10 |
| 91-180 | 15 |
| 181+ | 20 |

**Rationale**: Older issues without resolution deserve attention to prevent backlog growth.

**Highlight Label**: `⏰ Aging` when days > 90 AND has `needs-triage` label

---

### 3. Comments (Weight: 15 points max)

Discussion activity measured by comment count.

| Comments | Score |
|----------|-------|
| 0 | 0 |
| 1-2 | 3 |
| 3-5 | 6 |
| 6-10 | 10 |
| 11+ | 15 |

**Recent Activity Bonus**: +5 if commented in last 14 days

**Rationale**: Active discussions indicate ongoing relevance and potential blockers.

**Highlight Label**: `📈 Trending` when comments ≥ 5 AND recent activity (shows the issue is heating up NOW)

---

### 4. Severity Labels (Weight: 15 points max)

Priority based on issue labels indicating severity or type.

| Label | Score |
|-------|-------|
| `regression` | 15 |
| `crash`, `hang`, `data-loss` | 12 |
| `bug` | 8 |
| `performance` | 6 |
| `documentation` | 2 |
| None of above | 0 |

**Rationale**: Regressions and crashes have direct user impact.

**Highlight Labels**:
- `🐛 Regression` when has `regression` label
- (Bug severity shown in score, not separate label)

---

### 6. Blocker Status (Weight: 10 points max)

Issues that block other work or teams.

| Condition | Score |
|-----------|-------|
| Has `blocking` or `blocker` label | 10 |
| Linked as blocking another issue | 8 |
| Mentioned in blocking context | 5 |
| No blocker indicators | 0 |

**Rationale**: Blockers have multiplicative impact on productivity.

**Highlight Label**: `🚧 Blocker` when has blocking indicators

---

## Composite Score Calculation

```
Total Score = Σ(factor_score × factor_weight / max_factor_weight)

Normalized Score = (Total Score / 100) × 100
```

### Example Calculation

Issue #2894:
- Reactions: 25 (score: 24)
- Age: 120 days (score: 18)
- Comments: 8 (score: 13)
- Labels: `bug` (score: 8)
- Blocker: No (score: 0)

**Total**: 24 + 18 + 13 + 8 + 0 = **63/100**

---

## Highlight Label Assignment

After scoring, assign labels based on the highest-scoring factors:

| Priority | Label | Condition |
|----------|-------|-----------|
| 1 | `🐛 Regression` | Has `regression` label |
| 2 | `🚧 Blocker` | Has blocking indicators |
| 3 | `🔥 Hot` | Reactions ≥ 10 (all-time popularity) |
| 4 | `⏰ Aging` | Days > 90 + needs-triage |
| 5 | `📈 Trending` | Comments ≥ 5 + recent activity (heating up NOW) |
| 6 | ` Popular` | Feature proposal + reactions ≥ 5 |

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

These thresholds can be adjusted in `ScoringConfig.json`:

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
    "trending_comments": 5,
    "trending_days": 14,
    "popular_reactions": 5
  },
  "labelPriority": [
    "regression",
    "blocker",
    "hot",
    "aging",
    "trending",
    "popular"
  ],
  "maxLabelsPerIssue": 2
}
```

---

## Usage in Reports

When generating reports:

1. Fetch all open issues per area
2. Calculate scores for each issue
3. Sort by score descending
4. Take top N issues (default: 3)
5. Assign highlight labels
6. Format for display

### Output Example

```markdown
| Feature Area | ... | Highlights |
|--------------|-----|------------|
| area-Notification | ... | 🔥 [#2894](link) Hot, ⏰ [#3001](link) Aging |
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
