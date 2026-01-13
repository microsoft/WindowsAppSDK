---
agent: 'agent'
model: 'GPT-5.1-Codex-Max'
description: 'Perform a comprehensive PR review with per-step Markdown and machine-readable outputs'
---

# Review Pull Request

**Goal**: Given `{{pr_number}}`, run a *one-topic-per-step* review. Write files to `Generated Files/prReview/{{pr_number}}/` (replace `{{pr_number}}` with the integer). Emit machine‑readable blocks for a GitHub MCP to post review comments.

## Prerequisites — GitHub MCP availability

Before starting, verify the GitHub MCP tools are available by checking if `mcp_github_pull_request_read` can be invoked.

### If MCP is unavailable

Display this message to the user and pause:

> **GitHub MCP not detected.** This prompt requires the GitHub Pull Requests MCP for full functionality.
>
> **Install options:**
> 1. **VS Code extension** (recommended): Install [GitHub Pull Requests](https://marketplace.visualstudio.com/items?itemName=GitHub.vscode-pull-request-github) extension, then enable MCP in settings
> 2. **Manual MCP setup**: Follow [GitHub MCP documentation](https://docs.github.com/en/copilot/customizing-copilot/extending-copilot-chat-in-vs-code/using-model-context-protocol-servers-in-vs-code)
>
> After installation, restart VS Code and re-run this prompt.

### Fallback mode (limited functionality)

If the user chooses to proceed without MCP:
- Use `gh` CLI commands as fallback (requires GitHub CLI installed and authenticated)
- PR discovery: `gh pr list --assignee @me --state open --json number,updatedAt --limit 20`
- PR details: `gh pr view {{pr_number}} --json number,baseRefName,headRefName,baseRefOid,headRefOid,files`
- Changed files: `gh api repos/:owner/:repo/pulls/{{pr_number}}/files?per_page=250`
- **Note**: Review comment posting will be disabled in fallback mode; findings will only be written to local files.

## PR selection
Resolve the target PR using these fallbacks in order:
1. Parse the invocation text for an explicit identifier (first integer following patterns such as a leading hash and digits or the text `PR:` followed by digits).
2. If no PR is found yet, locate the newest `Generated Files/prReview/_batch/batch-overview-*.md` file (highest timestamp in filename, fallback newest mtime) and take the first entry in its `## PRs` list whose review folder is missing `00-OVERVIEW.md` or contains `__error.flag`.
3. If the batch file has no pending PRs, use `mcp_github_search_pull_requests` with `query: "assignee:@me is:open"`, `sort: "updated"`, `order: "desc"`, `perPage: 20` and pick the most recently updated PR that does not already have a completed review folder.
4. If still unknown, use `mcp_github_list_pull_requests` filtered by the current branch name (`head` parameter) and use that result when it is unambiguous.
5. If every step above fails, prompt the user for a PR number before proceeding.

## Fetch PR data with GitHub MCP

### Core PR information
Use `mcp_github_pull_request_read` (owner, repo, pullNumber required):
- `method: "get"` → returns number, baseRefName, headRefName, baseRefOid, headRefOid, title, body, state
- `method: "get_files"` → returns list of changed files with filename, status, additions, deletions, patch
- `method: "get_diff"` → returns unified diff with patch hunks for line mapping

### File contents at specific ref
Use `activate_file_management_tools` → `Get file contents`:
- Specify `owner`, `repo`, `path`, and `ref` (branch name or SHA) to fetch base version of files

### Incremental review workflow
1. **Check for existing review**: Read `Generated Files/prReview/{{pr_number}}/00-OVERVIEW.md`
2. **Extract state**: Parse `Last reviewed SHA:` from review metadata section
3. **Detect changes**: Use `activate_branch_and_commit_management_tools` → `List commits` on the head branch to check if `last_sha` exists in recent history. Then use `mcp_github_pull_request_read` with `method: "get_files"` to get current changed files and compare against cached file list from previous iteration.
4. **Analyze result**:
   - If force-push detected (last SHA not in commit history) → Full review needed
   - If commits added since last review → Review only changed files (diff current vs cached file list)
   - If no changes → Skip review (update iteration history with "No changes since last review")
5. **Apply smart filtering**: Use the file patterns in smart step filtering table to skip irrelevant steps
6. **Update metadata**: After completing review, save current `headRefOid` as `Last reviewed SHA:` in `00-OVERVIEW.md`

## Output files
Folder: `Generated Files/prReview/{{pr_number}}/`
Files: `00-OVERVIEW.md`, `01-functionality.md`, `02-compatibility.md`, `03-performance.md`, `04-accessibility.md`, `05-security.md`, `06-localization.md`, `07-globalization.md`, `08-extensibility.md`, `09-solid-design.md`, `10-repo-patterns.md`, `11-docs-automation.md`, `12-code-comments.md`, `13-copilot-guidance.md` *(only if guidance md exists).* 
- **Write-after-step rule:** Immediately after completing each TODO step, persist that step's markdown file before proceeding to the next. Generate `00-OVERVIEW.md` only after every step file has been refreshed for the current run.

## Iteration management
- Determine the current review iteration by reading `00-OVERVIEW.md` (look for `Review iteration:`). If missing, assume iteration `1`.
- Extract the last reviewed SHA from `00-OVERVIEW.md` (look for `Last reviewed SHA:` in the review metadata section). If missing, this is iteration 1.
- **Incremental review detection**:
  1. Use `activate_branch_and_commit_management_tools` → `List commits` to check commit history and verify `last_sha` exists.
  2. If `last_sha` not found in history (force-push), do a full review.
  3. If incremental, compare current `get_files` output against cached file list from previous iteration and review only changed files. Apply smart step filtering (see below).
- Increment the iteration for each review run and propagate the new value to all step files and the overview.
- Preserve prior iteration notes by keeping/expanding an `## Iteration history` section in each markdown file, appending the newest summary under `### Iteration <N>`.
- Summaries should capture key deltas since the previous iteration so reruns can pick up context quickly.
- **After review completion**, update `Last reviewed SHA:` in `00-OVERVIEW.md` with the current `headRefOid` and update the timestamp.

### Smart step filtering (incremental reviews only)
When performing incremental review, skip steps that are irrelevant based on changed file types:

| File pattern | Required steps | Skippable steps |
| --- | --- | --- |
| `**/*.cs`, `**/*.cpp`, `**/*.h` | Functionality, Compatibility, Performance, Security, SOLID, Repo patterns, Code comments | (depends on files) |
| `**/*.resx`, `**/Resources/*.xaml` | Localization, Globalization | Most others |
| `**/*.md` (docs) | Docs & automation | Most others (unless copilot guidance) |
| `**/*copilot*.md`, `.github/prompts/*.md` | Copilot guidance, Docs & automation | Most others |
| `**/*.csproj`, `**/*.vcxproj`, `**/packages.config` | Compatibility, Security, Repo patterns | Localization, Globalization, Accessibility |
| `**/UI/**`, `**/*View.xaml` | Accessibility, Localization | Performance (unless perf-sensitive controls) |

**Default**: If uncertain or files span multiple categories, run all applicable steps. When in doubt, be conservative and review more rather than less.

## TODO steps (one concern each)
1) Functionality — Does the implementation correctly follows SDK patterns?
2) Compatibility — Windows 10 1809+, x64/x86/ARM64, Debug/Release configurations
3) Performance — No unnecessary allocations or blocking operations
4) Accessibility — Follows [accessibility checklist](https://docs.microsoft.com/windows/apps/design/accessibility/accessibility-checklist)
5) Security — No hardcoded secrets, proper input validation
6) Localization — Resources properly externalized where applicable
7) Globalization — Culture-aware formatting where applicable
8) Extensibility — Clear patterns for developers to adapt
9) SOLID principles — Clean, maintainable SDK code
10) Repo patterns — Follows [Coding-Guidelines.md](docs/Coding-Guidelines.md) conventions
11) Docs & automation — Documentation updated, CI pipeline configured
12) Code comments — Appropriate copyright headers, helpful inline comments
13) Copilot guidance (conditional): if changed folders contain `*copilot*.md` or `.github/prompts/*.md`, review diffs **against** that guidance and write `13-copilot-guidance.md` (omit if none).

## Per-step file template (use verbatim)
```md
# <STEP TITLE>
**PR:** (populate with PR identifier) — Base:<baseRefName> Head:<headRefName>
**Review iteration:** ITERATION

## Iteration history
- Maintain subsections titled `### Iteration N` in reverse chronological order (append the latest at the top) with 2–4 bullet highlights.

### Iteration ITERATION
- <Latest key point 1>
- <Latest key point 2>

## Checks executed
- List the concrete checks for *this step only* (5–10 bullets).

## Findings
(If none, write **None**. Defaults have one or more blocks:)

```mcp-review-comment
{"file":"relative/path.ext","start_line":123,"end_line":125,"severity":"high|medium|low|info","tags":["<step-slug>","pr-tag-here"],"related_files":["optional/other/file1"],"body":"Problem → Why it matters → Concrete fix. If spans multiple files, name them here."}
```
Use the second tag to encode the PR number.

```
## Overview file (`00-OVERVIEW.md`) template
```md
# PR Review Overview — (populate with PR identifier)
**Review iteration:** ITERATION
**Changed files:** <n> | **High severity issues:** <count>

## Review metadata
**Last reviewed SHA:** <headRefOid from gh pr view>
**Last review timestamp:** <ISO8601 timestamp>
**Review mode:** <Full|Incremental (N files changed since iteration X)>
**Base ref:** <baseRefName>
**Head ref:** <headRefName>

## Step results
Write lines like: `01 Functionality — <OK|Issues|Skipped> (see 01-functionality.md)` … through step 13.
Mark steps as "Skipped" when using incremental review smart filtering.

## Iteration history
- Maintain subsections titled `### Iteration N` mirroring the per-step convention with concise deltas and cross-links to the relevant step files.
- For incremental reviews, list the specific files that changed and which commits were added.
```

## Line numbers & multi‑file issues
- Map head‑side lines from `patch` hunks (`@@ -a,b +c,d @@` → new lines `+c..+c+d-1`).
- For cross‑file issues: set the primary `"file"`, list others in `"related_files"`, and name them in `"body"`.

## Posting (for MCP)
- Parse all ```mcp-review-comment``` blocks across step files and post as PR review comments.
- If posting isn’t available, still write all files.

## Constraint
Read/analyze only; don't modify code. Keep comments small, specific, and fix‑oriented.

## Scratch cache for large PRs

Create a local scratch workspace to progressively summarize diffs and reload state across runs.

### Paths
- Root: `Generated Files/prReview/{{pr_number}}/__tmp/`
- Files:
  - `index.jsonl` — append-only JSON Lines index of artifacts.
  - `todo-queue.json` — pending items (files/chunks/steps).
  - `rollup-<step>-v<N>.md` — iterative per-step aggregates.
  - `file-<hash>.txt` — optional saved chunk text (when needed).

### JSON schema (per line in `index.jsonl`)
```json
{"type":"chunk|summary|issue|crosslink",
 "path":"relative/file.ext","chunk_id":"f-12","step":"functionality|compatibility|...",
 "base_sha":"...", "head_sha":"...", "range":[start,end], "version":1,
 "notes":"short text or key:value map", "created_utc":"ISO8601"}
```

### Phases (stateful; resume-safe)
0. **Discover** PR + SHAs: Use `mcp_github_pull_request_read` with `method: "get"` for refs/SHAs, then `method: "get_files"` for changed files list.
1. **Chunk** each changed file (head): split into ~300–600 LOC or ~4k chars; stable `chunk_id` = hash(path+start).
   - Save `chunk` records. Optionally write `file-<hash>.txt` for expensive chunks.
2. **Summarize** per chunk: intent, APIs, risks per TODO step; emit `summary` records (≤600 tokens each).
3. **Issues**: convert findings to machine-readable blocks and emit `issue` records (later rendered to step MD).
4. **Rollups**: build/update `rollup-<step>-v<N>.md` from `summary`+`issue`. Keep prior versions.
5. **Finalize**: write per-step files + `00-OVERVIEW.md` from rollups. Post comments via MCP if available.

### Re-use & token limits
- Always **reload** `index.jsonl` first; skip chunks with same `head_sha` and `range`.
- **Incremental review optimization**: When comparing SHAs returns a subset of changed files, load only chunks from those files. Reuse existing chunks/summaries for unchanged files.
- Prefer re-summarizing only changed chunks; merge chunk summaries → file summaries → step rollups.
- When context is tight, load only the minimal chunk text (or its saved `file-<hash>.txt`) needed for a comment.

### Original vs diff
- Fetch base content when needed: prefer `git show <baseRefName>:<path>`; fallback `activate_file_management_tools` → `Get file contents` with `ref` set to base SHA.
- Use patch hunks from `mcp_github_pull_request_read` with `method: "get_files"` or `method: "get_diff"` to compute **head** line numbers.

### Queue-driven loop
- Seed `todo-queue.json` with all changed files.
- Process: chunk → summarize → detect issues → roll up.
- Append to `index.jsonl` after each step; never rewrite previous lines (append-only).

### Hygiene
- `__tmp/` is implementation detail; do not include in final artifacts.
- It is safe to delete to force a clean pass; the next run rebuilds it.