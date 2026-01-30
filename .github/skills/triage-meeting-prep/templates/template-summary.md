# WinAppSDK Triage Meeting Summary

**Date:** {{date}}  
**Previous Triage:** {{previous_date}}  
**Generated:** {{timestamp}}

---

## 📊 Quick Stats — What's Changed

| Metric | Count | Description |
|--------|-------|-------------|
| 🔥 **Hot Issues** | {{hot_count}} | ≥5 combined comments + reactions increase |
| �️ **Needing Area Label** | {{no_area_count}} | Open + Needs-Triage + no area label |
| ↳ 🆕 Created This Week | {{new_this_week_count}} | New issues (created since last weekly triage) |
| ↳ ⏳ Older | {{older_pending_count}} | Older issues still pending |
| ✅ **Resolved** | {{resolved_count}} | Issues that got area labels or properly closed |
| ✅ **Closed (cleanup)** | {{closed_count}} | Closed but still has Needs-Triage label |

---

## 🔥 HOT Issues — Trending Since Last Triage

**These issues have significant increased community engagement (≥5 combined new comments + reactions) since last triage:**

{{#if hot_issues.length}}
| # | Title | 👍 Change | 💬 Change | Total Change | Current | Labels |
|---|-------|-----------|-----------|--------------|---------|--------|
{{#each hot_issues}}
| [#{{this.number}}]({{this.url}}) | {{this.title}} | +{{this.reaction_change}} | +{{this.comment_change}} | **+{{this.total_change}}** | 👍{{this.total_reactions}} 💬{{this.total_comments}} | {{this.labels}} |
{{/each}}
{{else}}
*No issues with significant activity increase (≥5 comments + reactions) since last triage.*
{{/if}}

> **Threshold**: Combined increase of ≥5 (comments + reactions). Single comment/reaction changes don't qualify.

---

## 🆕 Created This Week — New Issues

**Issues created since last weekly triage that need area labels:**

{{#if new_this_week_issues.length}}
| # | Title | Author | Created | 👍 | Comments | Suggested Area | Review |
|---|-------|--------|---------|-----|----------|----------------|--------|
{{#each new_this_week_issues}}
| [#{{this.number}}]({{this.url}}) | {{this.title}} | @{{this.author}} | {{this.created}} | {{this.thumbsUp}} | {{this.commentCount}} | `{{this.suggested_area}}` | [📋](../../issueReview/{{this.number}}/overview.md) |
{{/each}}
{{else}}
✅ *No new issues created this week.*
{{/if}}

---

## ⏳ Older Pending — Not Yet Actioned

**These older issues still don't have area labels:**

{{#if older_pending_issues.length}}
| # | Title | Created | 👍 | Comments | Suggested Area | Review |
|---|-------|---------|-----|----------|----------------|--------|
{{#each older_pending_issues}}
| [#{{this.number}}]({{this.url}}) | {{this.title}} | {{this.created}} | {{this.thumbsUp}} | {{this.commentCount}} | `{{this.suggested_area}}` | [📋](../../issueReview/{{this.number}}/overview.md) |
{{/each}}

> ⚠️ **Follow-up needed**: These issues have been waiting for triage.
{{else}}
✅ *No older pending issues!*
{{/if}}

---

## ✅ Resolved Since Last Triage

**These issues left the "Needs-Triage without area" queue:**

{{#if resolved_issues.length}}
| # | Title | Resolution |
|---|-------|------------|
{{#each resolved_issues}}
| [#{{this.number}}]({{this.url}}) | {{this.title}} | {{this.resolution}} |
{{/each}}
{{else}}
*No issues resolved since last triage.*
{{/if}}

---

## 📋 Detailed Review: NEW Issues Action Items

**Each NEW issue was analyzed using [review-issue.prompt.md](../../prompts/review-issue.prompt.md). Full details in `Generated Files/issueReview/<issue-number>/overview.md`.**

{{#each new_issues}}
### [#{{this.number}}]({{this.url}}) — {{this.title}}

**Scores**: Business: {{this.business_score}}/100 | Community: {{this.community_score}}/100 | Feasibility: {{this.feasibility_score}}/100 | Clarity: {{this.clarity_score}}/100

#### Label Recommendations
{{#each this.label_recommendations}}
- {{this.action}}: `{{this.label}}` — {{this.reason}}
{{/each}}

#### Clarifying Questions (if Clarity < 50)
{{#if this.clarifying_questions}}
{{#each this.clarifying_questions}}
{{@index}}. {{this}}
{{/each}}
{{else}}
*Requirements are clear — no questions needed.*
{{/if}}

#### Similar Issues Found
{{#if this.similar_issues}}
{{#each this.similar_issues}}
- #{{this.number}} — {{this.title}} ({{this.state}})
{{/each}}
{{else}}
*No similar issues found.*
{{/if}}

#### Potential Assignees
{{#each this.potential_assignees}}
- @{{this.username}} — {{this.reason}}
{{/each}}

#### Documentation Check
{{#if this.doc_check}}
- **Scenario**: {{this.doc_check.scenario_type}}
- **Reference**: {{this.doc_check.url}}
- **Summary**: {{this.doc_check.summary}}
{{else}}
*No documentation limitation found.*
{{/if}}

---

{{/each}}

## ✅ Closed Issues (still Needs-Triage) — Need Follow-up Reply

**These issues are closed but customer activity requires a response. Each reply is backed by research:**

{{#if closed_issues.length}}
{{#each closed_issues}}
### [#{{this.number}}]({{this.url}}) — {{this.title}}

**Status**: Closed on {{this.closed_date}} | **Last Activity**: {{this.last_activity}}

**Why Needs-Triage?** {{this.reason_for_triage}}

#### 🔍 Research Summary

**Similar Issues Found:**
{{#each this.research.similar_issues}}
- [#{{this.number}}]({{this.url}}) — {{this.title}} ({{this.state}}) — {{this.relevance}}
{{/each}}
{{#unless this.research.similar_issues}}
- *No directly related issues found*
{{/unless}}

**Codebase Findings:**
{{#each this.research.codebase_findings}}
- `{{this.file}}` — {{this.finding}}
{{/each}}
{{#unless this.research.codebase_findings}}
- *No relevant code patterns found*
{{/unless}}

**Documentation:**
{{#if this.research.documentation}}
- [{{this.research.documentation.title}}]({{this.research.documentation.url}}) — {{this.research.documentation.summary}}
{{else}}
- *No specific documentation found*
{{/if}}

**Area Owner:** {{this.research.area_owner}}

#### 💬 Suggested Reply (Confidence: {{this.reply_confidence}}/100)

> **📝 Copy this reply to post on the issue:**

---

{{this.suggested_reply}}

---

**Reasoning**: {{this.reply_reasoning}}

**Recommended Action**: {{this.recommended_action}}

---

{{/each}}
{{else}}
✅ *No closed issues needing follow-up.*
{{/if}}

---

## 🎯 Consolidated Action Items

### 🆕 NEW Issues — Label Changes (copy-paste ready)

{{#each new_issues}}
**#{{this.number}}**:
{{#each this.label_recommendations}}
- {{this.action}}: `{{this.label}}`
{{/each}}

{{/each}}

### ⏳ PENDING Issues — Follow Up Required

{{#if pending_issues.length}}
These issues need attention — check why they weren't actioned in previous meeting(s):

{{#each pending_issues}}
- [ ] **#{{this.number}}** (pending {{this.weeks_pending}} week(s)): {{this.last_action}}
{{/each}}
{{else}}
✅ *No pending issues — all previous items actioned!*
{{/if}}

### ✅ Closed Issues — Remove Needs-Triage Label

{{#each closed_issues}}
- [ ] **#{{this.number}}**: Remove `Needs-Triage` label
{{/each}}

### ❓ Questions to Post (NEW issues with Clarity < 50)

{{#each new_issues}}
{{#if this.clarifying_questions}}
**#{{this.number}}** — Post these questions:
{{#each this.clarifying_questions}}
> {{this}}
{{/each}}

{{/if}}
{{/each}}

---

## 🔗 Quick Links

- [All Open Needs-Triage](https://github.com/microsoft/WindowsAppSDK/issues?q=is%3Aissue+is%3Aopen+label%3A%22Needs-Triage%22) *(filter locally for no area label)*
- [Closed with Needs-Triage](https://github.com/microsoft/WindowsAppSDK/issues?q=is%3Aissue+is%3Aclosed+label%3A%22Needs-Triage%22)

---

## 📝 Meeting Notes

*Add discussion notes below during the meeting:*

### Decisions Made

- 

### Parking Lot (defer to next meeting)

- 

### Action Item Owners

| Action | Owner | Due Date |
|--------|-------|----------|
| | | |

---

*Generated by triage-meeting-prep skill. See individual issue reviews in `Generated Files/issueReview/<issue-number>/`*
