# Enum Name Generation

Generate a `RuntimeCompatibilityChange` enum entry name for a servicing cherry-pick.

## Context

- **PR Title:** {{PR_TITLE}}
- **PR Description:** {{PR_BODY}}
- **Changed Files:** {{CHANGED_FILES}}

## Requirements

1. The name must be in PascalCase with underscores separating logical components
2. Format: `<Component>_<BriefDescription>Fix` or `<Component>_<BriefDescription>`
3. Keep it concise but descriptive (under 60 characters)
4. It should reflect the fix being applied, not the symptom

## Examples from the codebase

- `DeploymentManager_ResetActivityDataFix`
- `FileTypeChoices_InsertionOrderFix`
- `CoreMessaging_RescheduleFix`
- `PenInput_X86CrashFix`
- `DirectManipulation_SubtractionUnderflowFix`
- `Islands_TransparentCutoutFix`

## Instructions

Return ONLY the enum name, nothing else. No explanation, no quotes, just the name.
