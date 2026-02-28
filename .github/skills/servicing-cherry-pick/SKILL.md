---
name: servicing-cherry-pick
description: Automates cherry-picking merged PRs to release branches with containment wrapping, ADO bugs, and GitHub PRs.
license: Complete terms in LICENSE.txt
---

# Servicing Cherry-Pick Automation

Automates the end-to-end process of "servicing" (backporting) a merged PR from `main` to active release branches like `release/1.7-stable` and `release/1.8-stable`.

## When to Use This Skill

- **Primary trigger** — A fix has merged to `main` and needs to be cherry-picked to one or more release branches
- **What it automates** — Creating ADO servicing bugs, cherry-picking commits, wrapping changes with containment checks (`IsChangeEnabled<>`), updating the RuntimeCompatibilityOptions IDL, and creating GitHub PRs
- **Anti-patterns** — Do NOT use for forward-porting (release→main), for non-servicing cherry-picks, or for changes that don't need containment

## Prerequisites

| Tool | Purpose | Install |
|------|---------|---------|
| **git** | Cherry-pick and worktree operations | https://git-scm.com/ |
| **gh** (GitHub CLI) | Fetch PR details, create PRs | https://cli.github.com/ → `gh auth login` |
| **az** (Azure CLI) | Create ADO work items | https://aka.ms/installazurecli → `az login` |
| **copilot** (Copilot CLI) | AI-powered containment wrapping (preferred) | `gh copilot` or install directly |
| **claude** (Claude CLI) | AI fallback if copilot unavailable | Optional |

### AI Provider Priority

The AI wrapper (`Get-AiCompletion.ps1`) auto-detects available providers in this order:

1. **`copilot`** — preferred; uses `copilot -p "..." -s` for non-interactive output
2. **`claude`** — fallback; uses `claude --print --max-turns 1`
3. **Manual input** — last resort; displays the prompt and accepts human input

If a provider fails, the script automatically falls through to the next one. You can force a specific provider with `-Provider copilot|claude|manual`.

## Quick Start

### Full automated run
```powershell
./scripts/Invoke-ServicingProcess.ps1 -PullRequestNumber 5865
```

### Dry run (preview without changes)
```powershell
./scripts/Invoke-ServicingProcess.ps1 -PullRequestNumber 5865 -DryRun
```

### Single branch with approval gates
```powershell
./scripts/Invoke-ServicingProcess.ps1 -PullRequestNumber 5865 `
    -TargetBranches "release/1.8-stable" -RequireApproval
```

### Skip ADO bugs (for testing)
```powershell
./scripts/Invoke-ServicingProcess.ps1 -PullRequestNumber 5865 -SkipAdoBugs
```

## Available Scripts

### Orchestrator

| Script | Synopsis |
|--------|----------|
| **`Invoke-ServicingProcess.ps1`** | Main orchestrator — runs the full cherry-pick workflow |

**Parameters:**

| Parameter | Required | Default | Description |
|-----------|----------|---------|-------------|
| `-PullRequestNumber` | Yes | — | The merged PR number to cherry-pick |
| `-Repository` | No | `microsoft/WindowsAppSDK` | GitHub repo in owner/repo format |
| `-TargetBranches` | No | Auto-detected | Override which release branches to target |
| `-ConfigPath` | No | `config/servicing-config.json` | Custom configuration path |
| `-SkipAdoBugs` | No | `$false` | Skip ADO bug creation |
| `-DryRun` | No | `$false` | Preview without executing |
| `-RequireApproval` | No | `$false` | Human review at each AI output |

### Individual Scripts

Each step can be run independently for testing or manual workflows:

| Script | Purpose | AI? |
|--------|---------|-----|
| `Get-PullRequestDetails.ps1` | Fetch PR metadata and diff | No |
| `Get-ServicingBranches.ps1` | List eligible release branches | No |
| `Get-NextPatchVersion.ps1` | Parse IDL for next patch version | No |
| `New-ServicingWorktree.ps1` | Create worktree on release branch | No |
| `Invoke-CherryPick.ps1` | Cherry-pick the merge commit | No |
| `Add-ContainmentWrapping.ps1` | Wrap changes with containment | **Yes** |
| `Update-RuntimeCompatibilityIdl.ps1` | Insert enum entry into IDL | No |
| `New-AdoServicingBug.ps1` | Create ADO work item | No |
| `New-ServicingPullRequest.ps1` | Commit, push, create GitHub PR | No |
| `Get-AiCompletion.ps1` | AI invocation wrapper | **Yes** |

### Shared Library

| File | Purpose |
|------|---------|
| `ServicingLib.ps1` | Logging, state persistence, prerequisites, string helpers |

## Workflow

```
Invoke-ServicingProcess.ps1 -PullRequestNumber <N>
  │
  [1] Validate prerequisites (git, gh, az, copilot/claude)
  [2] Fetch PR details (title, body, diff, merge commit)
  [3] Discover target release branches
  │
  FOR EACH branch:
    [4a] Get next patch version from IDL
    [4b] 🤖 Generate enum name
    [4c] 🤖 Generate ADO bug description
    [4d] Create ADO servicing bug
    [4e] Create worktree on release branch
    [4f] Cherry-pick merge commit
    [4g] 🤖 Apply containment wrapping
    [4h] Update RuntimeCompatibilityOptions.idl
    [4i] Generate PR body
    [4j] Create GitHub PR
    [4k] Link PR to ADO bug
    [4l] Save checkpoint
  │
  [5] Print summary report
```

## State and Resumability

State is persisted to `Generated Files/servicing/<PR>/state.json` after each branch operation. If a run fails partway through, re-running the same command resumes from the last checkpoint. Completed branches are skipped.

## Configuration

Default configuration is in `config/servicing-config.json`:

```json
{
  "repository": "microsoft/WindowsAppSDK",
  "ado": {
    "organization": "https://dev.azure.com/microsoft",
    "project": "OS",
    "areaPath": "OS\\WinAppSDK",
    "workItemType": "Bug",
    "tags": "AskMode;Servicing"
  },
  "branches": { "minVersion": "1.7" },
  "naming": {
    "branchPattern": "user/{author}/cherry-pick-{slug}-{version}",
    "prTitlePattern": "Cherry-pick: {originalTitle}"
  }
}
```

## Containment Pattern

All servicing code changes are wrapped with runtime containment checks:

```cpp
#include <FrameworkUdk/Containment.h>

// Bug <ID>: [<version> servicing] <description>
#define WINAPPSDK_CHANGEID_<ID> <ID>, WinAppSDK_<M>_<N>_<P>

if (WinAppSdk::Containment::IsChangeEnabled<WINAPPSDK_CHANGEID_<ID>>())
{
    // new behavior (the fix)
}
else
{
    // old behavior (rollback path)
}
```

See `references/containment-pattern-guide.md` for detailed documentation.

## Prompt Templates

| Template | Purpose |
|----------|---------|
| `templates/containment-prompt.md` | Instructs AI to wrap code with containment |
| `templates/enum-naming-prompt.md` | Generates enum entry name |
| `templates/ado-bug-prompt.md` | Generates ADO bug description fields |
| `templates/release-notes-prompt.md` | Generates release notes text |
| `templates/pr-body-template.md` | PR body markdown template |

## Troubleshooting

| Symptom | Solution |
|---------|----------|
| `gh` not authenticated | Run `gh auth login` |
| `az` not authenticated | Run `az login` |
| Cherry-pick conflicts | AI will attempt resolution; use `-RequireApproval` to review |
| AI output invalid | Re-run with `-RequireApproval` to manually edit AI output |
| Run failed partway | Re-run the same command; completed branches are skipped |
| Wrong target branches | Use `-TargetBranches` to override auto-detection |
| No AI CLI available | Auto-falls through: copilot → claude → manual input |
| Want to force a specific AI | Use `-Provider copilot` or `-Provider claude` on `Get-AiCompletion.ps1` |

## Related Resources

- [RuntimeCompatibilityOptions Spec](../../specs/Compatibility/RuntimeCompatibilityOptions.md)
- [Containment Pattern Guide](references/containment-pattern-guide.md)
- [Worktree Manager Skill](../worktree-manager/SKILL.md)
