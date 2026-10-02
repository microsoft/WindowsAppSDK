---
agent: 'agent'
description: 'Generate a WindowsAppSDK-ready pull request description from the local diff'
---

# Generate PR Summary

**Goal:** Produce a ready-to-paste PR title and description that follows WindowsAppSDK conventions by comparing the current branch against a user-selected target branch.

**Repo guardrails:**
- Treat `docs/pull_request_template.md` as the single source of truth; load it at runtime instead of embedding hardcoded content in this prompt.
- Preserve section order from the template but only surface checklist lines that are relevant for the detected changes, filling them with `[x]`/`[ ]` as appropriate.
- Cite touched paths with inline backticks, matching the guidance in `.github/copilot-instructions.md`.
- Call out build/test validation explicitly: state which platforms (x64, x86, ARM64) and configurations (Debug, Release) were tested, or why testing was not applicable.

**Workflow:**
1. Prepend the PR title above the filled template, applying the Conventional Commit type/scope rules from `.github/prompts/create-commit-title.prompt.md`; pick the dominant component from the diff and keep the title concise and imperative.
2. Determine the target branch from user context; default to `main` when no branch is supplied.
3. Run `git status --short` once to surface uncommitted files that may influence the summary.
4. Run `git diff <target-branch>...HEAD` a single time to review the detailed changes. Only when confidence stays low dig deeper with focused calls such as `git diff <target-branch>...HEAD -- <path>`.
5. From the diff, capture impacted areas (components, features), key file changes, behavioral risks, and noteworthy edge cases.
6. Confirm validation: list builds and tests executed with results, or state why they were skipped in line with repo guidance.
7. Load `docs/pull_request_template.md`, mirror its section order, and populate it with the gathered facts. Include only relevant checklist entries, marking them `[x]/[ ]` and noting any intentional omissions as "N/A".
8. Present the filled template inside a fenced ```markdown code block with no extra commentary so it is ready to paste into a PR, clearly flagging any placeholders that still need user input.
