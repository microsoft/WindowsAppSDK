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
| 1 | `DeploymentManager::GetStatus()` | `Microsoft.Windows.ApplicationModel.WindowsAppRuntime` | ✅ YES | ✅ YES | 0xC0000409 (process crash) | AppModel/Deployment team | **CRITICAL**: Calling GetStatus() causes fast-fail crash (STATUS_STACK_BUFFER_OVERRUN) in BOTH directions. Test host process is killed. |
| 2 | `UniversalBGTask.Task` | `Microsoft.Windows.ApplicationModel.Background.UniversalBGTask` | ✅ YES | ✅ YES | REGDB_E_CLASSNOTREG (0x80040154) | AppModel/Background team | Class not registered in either runtime direction. |
| 3 | `WidgetManager` | `Microsoft.Windows.Widgets.Providers` | ✅ YES | ✅ YES | REGDB_E_CLASSNOTREG (0x80040154) | Widgets team | Class not registered. May require Widget host infrastructure not present in test environment. |
| 4 | `FeedManager` | `Microsoft.Windows.Widgets.Feeds.Providers` | ✅ YES | ✅ YES | REGDB_E_CLASSNOTREG (0x80040154) | Widgets/Feeds team | Class not registered. May require Widget host infrastructure not present in test environment. |

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
