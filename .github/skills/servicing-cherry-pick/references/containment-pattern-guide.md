# Containment Pattern Guide

This document describes how containment (runtime compatibility) works in Windows App SDK servicing.

## Purpose

When a fix is cherry-picked from `main` to a release branch (e.g., `release/1.7-stable`), it must be wrapped with containment checks. This allows:

1. **Apps to opt-out** of specific fixes if they cause regressions
2. **Patch-level versioning** so apps can lock behavior to a specific servicing release
3. **Safe rollback** without requiring a new servicing release

## Architecture

### Components

1. **`FrameworkUdk/Containment.h`** - Header with `IsChangeEnabled<>` template and `WinAppSDKPatchVersion` enum
2. **`RuntimeCompatibilityOptions.idl`** - Public API for apps to configure compatibility
3. **`#define WINAPPSDK_CHANGEID_*`** - Per-file macros linking bug IDs to patch versions

### How It Works

```
App calls RuntimeCompatibilityOptions.Apply()
  → Sets WinAppSDKRuntimeConfiguration
    → patchVersion: which patch level to behave as
    → disabledChanges: specific bug IDs to disable

When code calls IsChangeEnabled<bugId, patchVersion>():
  → If bugId is in disabledChanges → returns false
  → If patchVersion > configured patchVersion → returns false
  → Otherwise → returns true (fix is active)
```

## Code Pattern

### Step 1: Include and Define

At the top of each modified source file, after existing includes:

```cpp
#include <FrameworkUdk/Containment.h>

// Bug <BUG_ID>: [<VERSION> servicing] <Description>
#define WINAPPSDK_CHANGEID_<BUG_ID> <BUG_ID>, WinAppSDK_<MAJOR>_<MINOR>_<PATCH>
```

**Example:**
```cpp
#include <FrameworkUdk/Containment.h>

// Bug 61124052: [1.7.9 servicing] Fix reset activity data on deployment initialization
#define WINAPPSDK_CHANGEID_61124052 61124052, WinAppSDK_1_7_9
```

### Step 2: Wrap Added Code

New code introduced by the fix gets a positive containment check:

```cpp
if (WinAppSdk::Containment::IsChangeEnabled<WINAPPSDK_CHANGEID_61124052>())
{
    // New behavior from the fix
    ResetActivityData();
}
```

### Step 3: Preserve Removed Code

Code that was removed by the fix is kept with an inverted check:

```cpp
if (!WinAppSdk::Containment::IsChangeEnabled<WINAPPSDK_CHANGEID_61124052>())
{
    // Old behavior, preserved for rollback
    SkipActivityDataReset();
}
```

### Step 4: Handle Modified Code

When code is both removed and replaced:

```cpp
if (WinAppSdk::Containment::IsChangeEnabled<WINAPPSDK_CHANGEID_61124052>())
{
    // New implementation
    auto result = NewApiCall();
}
else
{
    // Old implementation (rollback path)
    auto result = OldApiCall();
}
```

## IDL Update

Each containment change needs an entry in `RuntimeCompatibilityOptions.idl`:

```idl
enum RuntimeCompatibilityChange
{
    None = 0,

    // 1.7.9
    DeploymentManager_ResetActivityDataFix = 61124052,
};
```

The enum value is the ADO bug ID. The version comment groups entries by servicing patch.

## Important Rules

1. **Only wrap actual changes** - don't wrap unchanged code or unrelated includes
2. **One macro per bug** - all containment checks in a file use the same `WINAPPSDK_CHANGEID_*`
3. **Don't wrap include additions** - new `#include` lines don't need containment guards
4. **Match existing style** - use the same indentation and brace style as surrounding code
5. **Security fixes** use `WinAppSDK_Security` instead of a versioned symbol (always enabled)
6. **Static caching** - `IsChangeEnabled` caches its result, so it's safe in hot paths

## WinAppSDKPatchVersion Values

The patch version enum uses a computed value: `major * 10000 + minor * 100 + patch`

| Version | Symbol | Numeric Value |
|---------|--------|---------------|
| 1.7.1   | WinAppSDK_1_7_1 | 10701 |
| 1.7.2   | WinAppSDK_1_7_2 | 10702 |
| 1.8.1   | WinAppSDK_1_8_1 | 10801 |
| 1.8.3   | WinAppSDK_1_8_3 | 10803 |
| Security | WinAppSDK_Security | 0 |
| Latest  | WinAppSDK_Latest | 999999999 |

## Real Examples from the Codebase

### Bug 56686624 (1.7.1): Access violation fix

```cpp
#include <FrameworkUdk/Containment.h>

// Bug 56686624: Access violation in CUIElement::FlushPendingKeepVisibleOperations
#define WINAPPSDK_CHANGEID_56686624 56686624, WinAppSDK_1_7_1

// In the function:
if (WinAppSdk::Containment::IsChangeEnabled<WINAPPSDK_CHANGEID_56686624>())
{
    // Fixed null check
    if (pElement != nullptr)
    {
        pElement->FlushPendingKeepVisibleOperations();
    }
}
else
{
    // Original code without null check
    pElement->FlushPendingKeepVisibleOperations();
}
```

### Bug 59722070 (1.8.3): Islands transparent cutout fix

```cpp
// Bug 59722070: Allow islands under current island with transparent cutout
#define WINAPPSDK_CHANGEID_59722070 59722070, WinAppSDK_1_8_3

if (WinAppSdk::Containment::IsChangeEnabled<WINAPPSDK_CHANGEID_59722070>())
{
    // New behavior: allow transparent cutout for islands
    SetTransparentCutoutEnabled(true);
}
```
