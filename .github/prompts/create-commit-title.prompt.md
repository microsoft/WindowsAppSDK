---
agent: 'agent'
description: 'Generate an 80-character git commit title for the local diff'
---

# Generate Commit Title

## Purpose
Provide a single-line, ready-to-paste git commit title (<= 80 characters) that reflects the most important local changes since `HEAD`.

## Input to collect
- Run exactly one command to view the local diff:
  ```@terminal
  git diff HEAD
  ```

## How to decide the title
1. From the diff, find the dominant area (e.g., `dev/AppLifecycle/*`, `docs/**`) and the change type (new feature, bug fix, docs update, config tweak).
2. Draft an imperative, plain-ASCII title that:
   - Mentions the primary component when obvious (e.g., `AppLifecycle:` or `Docs:`)
   - Stays within 80 characters and has no trailing punctuation

## Final output
- Reply with only the commit title on a single line—no extra text.

## PR title convention (when asked)
Use Conventional Commits style:

`<type>(<scope>): <summary>`

**Allowed types**
- feat, fix, docs, refactor, perf, test, build, ci, chore

**Scope rules**
- Use a short, WindowsAppSDK-focused scope (one word preferred). Common scopes:
    - Core: `docs`, `build`, `ci`, `tools`, `repo`
    - Components: `applifecycle`, `activation`, `dynamicdependency`, `deployment`, `mrtcore`, `notifications`, `push`, `appnotifications`, `packaging`, `bootstrap`, `winrt`, `interop`, `licensing`, `oauth`, `environmentmanager`, `powernotifications`, `backgroundtask`, `projections`, `insights`
- If unclear, pick the closest component or area; omit only if unavoidable

**Summary rules**
- Imperative, present tense (“add”, “update”, “remove”, “fix”)
- Keep it <= 72 characters when possible; be specific, avoid “misc changes”

**Examples**
- `feat(applifecycle): add restart API support`
- `fix(notifications): correct push notification channel registration`
- `docs(deployment): document MSIX package requirements`
- `build(ci): update Foundation pipeline configuration`
- `refactor(dynamicdependency): simplify package resolution logic`
