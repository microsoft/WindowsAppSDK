# Release Notes Generation

Generate a release notes entry for a servicing fix.

## Context

- **Original PR:** #{{PR_NUMBER}} - {{PR_TITLE}}
- **PR Description:** {{PR_BODY}}
- **Version:** {{VERSION_STRING}}

## Requirements

1. One or two sentences describing the fix from the user's perspective
2. Focus on the symptom that was fixed, not the internal implementation
3. Use past tense ("Fixed...", "Resolved...")
4. Do not mention internal implementation details like containment, IDL changes, etc.

## Examples

- "Fixed an issue where FileTypeChoices in Storage Pickers did not preserve insertion order."
- "Resolved a crash that could occur when using pen input on x86 applications."
- "Fixed UI freezes in CoreMessaging when rescheduling operations under heavy load."

## Instructions

Return ONLY the release notes text, nothing else. No bullet points, no markdown, just the plain text.
