# Containment Wrapping Task

You are wrapping cherry-picked code changes with Windows App SDK containment checks for servicing.

## Context

- **Bug ID:** {{BUG_ID}}
- **Patch Version Symbol:** {{PATCH_VERSION_SYMBOL}}
- **Version:** {{VERSION_STRING}}
- **PR Title:** {{PR_TITLE}}

## Containment Pattern Guide

{{CONTAINMENT_GUIDE}}

## What You Must Do

For every code change introduced by the cherry-pick, wrap it with containment checks:

### 1. Add the containment macro define at the top of each modified file

Place this after the existing `#include` statements:

```cpp
#include <FrameworkUdk/Containment.h>

// Bug {{BUG_ID}}: [{{VERSION_STRING}} servicing] {{PR_TITLE}}
#define WINAPPSDK_CHANGEID_{{BUG_ID}} {{BUG_ID}}, {{PATCH_VERSION_SYMBOL}}
```

If `<FrameworkUdk/Containment.h>` is already included, do not add it again. If a `WINAPPSDK_CHANGEID_{{BUG_ID}}` macro already exists, do not duplicate it.

### 2. Wrap NEW/ADDED code with positive containment check

```cpp
if (WinAppSdk::Containment::IsChangeEnabled<WINAPPSDK_CHANGEID_{{BUG_ID}}>())
{
    // <new code from the cherry-pick goes here>
}
```

### 3. Preserve REMOVED code with negative containment check

If the cherry-pick removes code, keep the removed code wrapped in an inverted check:

```cpp
if (!WinAppSdk::Containment::IsChangeEnabled<WINAPPSDK_CHANGEID_{{BUG_ID}}>())
{
    // <old code that was removed, kept for rollback>
}
```

### 4. Handle MODIFIED code (both removed and added)

```cpp
if (WinAppSdk::Containment::IsChangeEnabled<WINAPPSDK_CHANGEID_{{BUG_ID}}>())
{
    // <new version of the code>
}
else
{
    // <old version of the code>
}
```

## Important Rules

1. **Only wrap the actual changes** - do not wrap surrounding unchanged code
2. **Maintain correct indentation** matching the existing code style
3. **Do not modify** any code that wasn't part of the original cherry-pick diff
4. **Include all necessary headers** (`#include <FrameworkUdk/Containment.h>`)
5. **Place the `#define`** near the top of the file, after includes
6. If a file only has new includes added, the includes themselves don't need wrapping
7. For changes in header files (.h), follow the same pattern
8. Ensure proper bracket matching in all output

## Original PR Diff (what was changed on main)

```diff
{{ORIGINAL_DIFF}}
```

## Cherry-Pick Diff (what was applied to the release branch)

```diff
{{CHERRY_PICK_DIFF}}
```

## Current File Contents (after cherry-pick, before containment)

{{FILE_CONTENTS}}

## Output Format

Return ONLY the complete modified file contents in this exact format for each file you modify:

=== FILE: path/to/file.cpp ===
<complete file contents with containment wrapping applied>
=== END FILE ===

Do not include any explanation or commentary outside the file blocks.
Only include files that need containment changes.
