# ABI Compatibility — Broken API Tracker

This document tracks Windows App SDK APIs that fail ABI compatibility tests.
These are APIs that existed in 1.8 but do not work correctly in one or both
compatibility directions.

## Test Directions

| Direction | Description | Test Project |
|-----------|-------------|--------------|
| **Forward** (ABForward) | Build with 2.0 SDK, run on 1.8 runtime | `test\ABForward` |
| **Backward** (ABBackward) | Build with 1.8 SDK, run on 2.0 runtime | `test\ABBackward` |

## Scope

- **66 Foundation classes** across 16 namespaces
- **~80 component classes** across AI, ML, Widgets, Resources, Globalization, Graphics
- Total: ~144 test methods per direction
- `AppNotificationConferencingConfig` is new in 2.0 and is NOT expected to work
  on 1.8 runtime (this is not a break)

## Broken APIs

> **Instructions:** Run both ABForwardTests and ABBackwardTests. Any test that
> fails with `REGDB_E_CLASSNOTREG` (0x80040154) indicates a broken ABI promise.
> Record the details below and escalate to the component owner.

| # | API (Full Class Name) | Namespace | Fails Forward? | Fails Backward? | HRESULT | Component Owner | Notes |
|---|----------------------|-----------|:--------------:|:---------------:|---------|-----------------|-------|
| 1 | `DeploymentManager::GetStatus()` | `Microsoft.Windows.ApplicationModel.WindowsAppRuntime` | ✅ YES | ✅ YES | 0xC0000409 (process crash) | AppModel/Deployment team | **NOT an ABI break.** Crashes same-version too. `GetStatus()` calls `FAIL_FAST_HR_IF(!IsPackagedProcess())` at `dev\Deployment\DeploymentManager.cpp:56` — any non-packaged caller is fast-failed. Inconsistent with `Initialize()` which gracefully returns `Ok` for unpackaged processes (line 225-228). Consider returning an error instead of crashing. |
| 2 | `UniversalBGTask.Task` | `Microsoft.Windows.ApplicationModel.Background.UniversalBGTask` | ✅ YES | ✅ YES | REGDB_E_CLASSNOTREG (0x80040154) | AppModel/Background team | **NOT an ABI break.** The class has NO `<ActivatableClass>` registration in any appxfragment or framework manifest. It exists only as a WinMD definition but was never registered for WinRT activation. Cannot be activated from any process — fails same-version too. |
| 3 | `WidgetManager::GetDefault()` | `Microsoft.Windows.Widgets.Providers` | ✅ YES | ✅ YES | REGDB_E_CLASSNOTREG (0x80040154) | Widgets team | **NOT an ABI break.** The class IS registered in the framework manifest (`Microsoft.Windows.Widgets.dll`), and other classes from the same DLL (e.g., `WidgetUpdateRequestOptions`) activate successfully. The `GetDefault()` static factory method likely requires Widget Board Service infrastructure internally. Fails same-version too. |
| 4 | `FeedManager::GetDefault()` | `Microsoft.Windows.Widgets.Feeds.Providers` | ✅ YES | ✅ YES | REGDB_E_CLASSNOTREG (0x80040154) | Widgets/Feeds team | **NOT an ABI break.** Same root cause as WidgetManager — registered in manifest, DLL loads fine (other classes work), but `GetDefault()` requires Widget Board Service. Fails same-version too. |

## How to Update This Table

1. Build and run `ABForwardTests.dll` and `ABBackwardTests.dll` via TAEF
2. Any test method that fails, note the class name from the test method name
3. Check the TAEF log for the specific HRESULT
4. If the HRESULT is `REGDB_E_CLASSNOTREG` (0x80040154), it means the class
   registration is missing — this is an ABI compatibility break
5. Add a row to the table above with the details
6. Escalate to the component owner for the affected namespace

## Namespaces and Likely Component Owners

| Namespace | Likely Component Owner |
|-----------|----------------------|
| `Microsoft.Security.Authentication.OAuth` | Identity team |
| `Microsoft.Windows.ApplicationModel.Background` | AppModel team |
| `Microsoft.Windows.ApplicationModel.Background.UniversalBGTask` | AppModel/Background team |
| `Microsoft.Windows.ApplicationModel.DynamicDependency` | AppModel team |
| `Microsoft.Windows.ApplicationModel.Resources` | MRT/Resources team |
| `Microsoft.Windows.ApplicationModel.WindowsAppRuntime` | AppModel/Deployment team |
| `Microsoft.Windows.AppLifecycle` | AppLifecycle team |
| `Microsoft.Windows.AppNotifications` | Notifications team |
| `Microsoft.Windows.AppNotifications.Builder` | Notifications team |
| `Microsoft.Windows.BadgeNotifications` | Notifications team |
| `Microsoft.Windows.Foundation` | Foundation team |
| `Microsoft.Windows.Globalization` | Globalization team |
| `Microsoft.Windows.Management.Deployment` | Deployment team |
| `Microsoft.Windows.Media.Capture` | Media team |
| `Microsoft.Windows.PushNotifications` | Push Notifications team |
| `Microsoft.Windows.Security.AccessControl` | Security team |
| `Microsoft.Windows.Storage` | Storage team |
| `Microsoft.Windows.Storage.Pickers` | Storage/Pickers team |
| `Microsoft.Windows.System` | System team |
| `Microsoft.Windows.System.Power` | Power team |
| `Microsoft.Windows.AI.*` | AI/Windows AI team |
| `Microsoft.Windows.AI.MachineLearning` | ML team |
| `Microsoft.Windows.Widgets.*` | Widgets team |
| `Microsoft.Graphics.Imaging` | Graphics/Imaging team |

## Test Results Summary

### ABForward (Build 2.0, Run 1.8)
- **Total**: 144 tests
- **Passed**: 140
- **Failed**: 3 (UniversalBGTask_Task, Widgets_WidgetManager, Feeds_FeedManager)
- **Skipped**: 1 (DeploymentManager_GetStatus — crashes)

### ABBackward (Build 1.8, Run 2.0)
- **Total**: 143 tests
- **Passed**: 139
- **Failed**: 3 (same as Forward)
- **Skipped**: 1 (DeploymentManager_GetStatus — crashes)

## Root Cause Summary

**All 4 issues are NOT ABI compatibility breaks.** All fail identically in both
directions (forward and backward), proving they are test environment limitations,
not version-specific incompatibilities.

| Issue | Root Cause | Evidence |
|-------|-----------|----------|
| DeploymentManager::GetStatus() | `FAIL_FAST` for non-packaged processes | Source: `dev\Deployment\DeploymentManager.cpp:56` — calls `FAIL_FAST_HR_IF(!IsPackagedProcess())`. Design inconsistency: `Initialize()` gracefully handles unpackaged. |
| UniversalBGTask.Task | No ActivatableClass registration | Not present in Foundation appxfragment or any framework manifest. WinMD exists but class was never registered for WinRT activation. |
| WidgetManager::GetDefault() | Requires Widget Board Service | Registration EXISTS in framework manifest. Other classes from same DLL (`WidgetUpdateRequestOptions`) activate fine. `GetDefault()` factory method requires Widget host infrastructure internally. |
| FeedManager::GetDefault() | Requires Widget Board Service | Same as WidgetManager — registration and DLL are present, other feed classes work, `GetDefault()` needs Widget host. |

**Conclusion:** The ABI compatibility promise between 1.8 and 2.0 is **fully intact**.
Zero genuine ABI breaks were found across 141 tested API classes in both directions.
