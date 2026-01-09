# PowerToys Worktree Helper Scripts

This folder contains helper scripts to create and manage parallel Git worktree for developing multiple changes (including Copilot suggestions) concurrently without cloning the full repository each time.

## Why worktree?
Git worktree let you have several checked‑out branches sharing a single `.git` object store. Benefits:
- Fast context switching: no re-clone, no duplicate large binary/object downloads.
- Lower disk usage versus multiple full clones.
- Keeps each change isolated in its own folder so you can run builds/tests independently.
- Enables working in parallel with Copilot generated branches (e.g., feature + quick fix + perf experiment) while the main clone stays clean.

Recommended: keep active parallel worktree(s) to **≤ 3** per developer to reduce cognitive load and avoid excessive incremental build invalidations.

## Scripts Overview
| Script | Purpose |
|--------|---------|
| `New-WorktreeFromBranch.ps1/.cmd` | Create/reuse a worktree for an existing local or remote (origin) branch. Can normalize `origin/branch` to `branch`. |
| `New-WorktreeFromIssue.ps1/.cmd` | Start a new work item branch from a base (default `origin/main`) using naming `workitem/<number>-<slug>`. |
| `Delete-Worktree.ps1/.cmd` | Remove a worktree and optionally its local branch. |
| `WorktreeLib.ps1` | Shared helpers: unique folder naming, worktree listing, upstream setup, summary output, logging helpers. |

## Typical Flows
### 1. Create from an existing or remote branch
```
./New-WorktreeFromBranch.ps1 -Branch origin/feature/new-ui
```
Fetches if needed and creates a tracking branch if missing, then creates/reuses the worktree.

### 2. Start a new work item branch (Azure DevOps)
```
./New-WorktreeFromIssue.ps1 -Number 1234 -Title "Crash on launch"
```
Creates branch `workitem/1234-crash-on-launch` off `origin/main` (or `-Base`), then worktree.

### 3. Delete a worktree when done
```
./Delete-Worktree.ps1 -Pattern feature/perf-tweak
```
If only one match, removes the worktree directory. Add `-Force` to discard local changes. Use `-KeepBranch` if you still need the branch.

## After Creating a Worktree
Inside the new worktree directory:
1. Run the minimal build bootstrap in VSCode terminal:
```
tools\build\build-essentials.cmd
```
2. Build only the module(s) you need (e.g., open solution filter or run targeted project build) instead of a full PowerToys build. This speeds iteration and reduces noise.
3. Make changes, commit, push.
4. Finally delete the worktree when done.

## Naming & Locations
- Worktree is created as sibling folders of the repo root (e.g., `PowerToys` + `PowerToys-ab12`), using a hash/short pattern to avoid collisions.
- Work item branches: `workitem/<number>` or `workitem/<number>-<slug>`.

## Scenarios Covered / Limitations
Covered scenarios:
1. From an existing local or origin remote branch.
2. Creating a new branch for an Azure DevOps work item.

Not covered (manual steps needed):
- Creating from a non-origin upstream (add remote manually then use branch script).
- Batch creation of multiple worktree in one command.
- Automatic rebase / sync of many worktree at once (do that manually or script separately).

## Best Practices
- Keep ≤ 3 active parallel worktree(s) (e.g., main dev, a long-lived feature, a quick fix / experiment) plus the root clone.
- Delete stale worktree early; each adds file watchers & potential incremental build churn.
- Avoid editing the same file across multiple worktree simultaneously to reduce merge friction.
- Run `git fetch --all --prune` periodically in the primary repo, not in every worktree.

## Troubleshooting
| Symptom | Hint |
|---------|------|
| Cannot lock ref *.lock | Stale lock: run `git worktree prune` or manually delete the `.lock` file then retry.
| Worktree already exists error | Use `git worktree list` to locate existing path; open that folder instead of creating a duplicate.
| Local branch missing for remote | Use `git branch --track <name> origin/<name>` then re-run the branch script.

## Security & Safety Notes
- Scripts avoid force-deleting unless you pass `-Force` (Delete script).
- No network credentials are stored; they rely on your existing Git credential helper.

---
Maintainers: Keep the scripts lean; avoid adding heavy dependencies or global state. Update this doc if parameters or flows change.
