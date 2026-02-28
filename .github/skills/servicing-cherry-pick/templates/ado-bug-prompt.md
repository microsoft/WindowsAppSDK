# ADO Bug Description Generation

Generate the description fields for an ADO servicing bug work item.

## Context

- **Original PR:** #{{PR_NUMBER}} - {{PR_TITLE}}
- **PR Description:** {{PR_BODY}}
- **Target Branch:** {{TARGET_BRANCH}}
- **Version:** {{VERSION_STRING}}
- **Enum Name:** {{ENUM_NAME}}

## Required Output

Return a JSON object with these fields:

```json
{
  "title": "[{{VERSION_STRING}} servicing] <brief description of the fix>",
  "description": "<HTML description for the ADO bug body>",
  "reproSteps": "<Steps to reproduce the original issue>",
  "customerImpact": "<Who is affected and how>",
  "riskAssessment": "<Low/Medium/High with justification>"
}
```

## Guidelines

1. **Title**: Should start with `[{{VERSION_STRING}} servicing]` followed by a concise description
2. **Description**: Include:
   - Link to the original PR
   - What the fix does
   - Why it needs to be serviced (cherry-picked to release branch)
   - The containment enum name for tracking
3. **Repro Steps**: Based on what the original PR fixes
4. **Customer Impact**: Who would hit this bug and how severely
5. **Risk Assessment**: Consider scope of changes, test coverage, rollback capability via containment

Return ONLY the JSON object, no other text.
