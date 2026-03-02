# Teams Review Message - Description

Write the "Description" section for a Teams message announcing a servicing cherry-pick for team review.

## Context

- **Original PR:** #{{PR_NUMBER}} - {{PR_TITLE}}
- **PR Description:** {{PR_BODY}}
- **ADO Bugs being filed:**

{{ADO_BUGS_SECTION}}

## Instructions

Write a concise 2-4 sentence description from the engineer's perspective explaining:
1. What was the original issue or fix
2. Why it matters for servicing (i.e., why it needs to be cherry-picked to release branches)

Write in first person ("I fixed...", "Last year I addressed..."). Keep it conversational but informative, as this will be posted in a Teams channel for team review.

## Example

Here is an example of a good description:

> Last year I fixed an issue on how the deployment manager telemetry collection was being done. In short, we were collecting telemetry on WinAppSDK by calling a WIL telemetry function that only works if the binary has its own telemetry provider, and the deployment manager DLL doesn't have its own. The fix is to call a different function that logs to a parent provider. This was already merged to main but needs to be serviced to release branches.

## Output

Return ONLY the description text. No headers, no labels, no "Description:" prefix. Just the plain text paragraph(s).
