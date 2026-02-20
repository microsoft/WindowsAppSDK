# Windows App SDK API Support Matrix

This document provides a centralized reference showing which Windows App SDK APIs
are supported under each packaging and configuration combination.

## Legend

| Symbol | Meaning |
|--------|---------|
| Y | Fully supported |
| N | Not supported |
| P | Partial support (see Notes) |

## Packaging and Configuration Combinations

| Combination | Description |
|-------------|-------------|
| **Packaged (MSIX)** | App deployed via MSIX Desktop Bridge with full package identity |
| **Unpackaged** | App deployed without MSIX packaging, no package identity |
| **Self-Contained** | App bundles the WinAppSDK runtime, no framework package dependency |
| **Framework-Dependent** | App depends on the WinAppSDK framework package being installed |

## App Notifications

| API | Packaged | Unpackaged | Self-Contained | Notes |
|-----|----------|-----------|----------------|-------|
| `AppNotificationManager.Register()` | Y | Y | Y | Packaged: uses manifest CLSID. Unpackaged: registers caller process as COM server |
| `AppNotificationManager.Register(String, Uri)` | N | Y | Y | Unpackaged only. Allows custom display name and icon |
| `AppNotificationManager.Show()` | Y | Y | Y | |
| `AppNotificationManager.GetAllAsync()` | Y | Y | Y | |
| `AppNotificationManager.RemoveAllAsync()` | Y | Y | Y | |
| `AppNotificationManager.Setting` | Y | Y | Y | `DisabledByManifest` status only applies to packaged apps |
| Image protocols in notifications | Y (ms-appx) | P (file:// only) | P (file:// only) | Unpackaged apps cannot use ms-appx:// protocol |

## Push Notifications

| API | Packaged | Unpackaged | Self-Contained | Notes |
|-----|----------|-----------|----------------|-------|
| `PushNotificationManager.CreateChannelAsync()` | Y | Y | P | Self-contained may not support push due to API limitations |
| `PushNotificationManager.Register()` | Y | Y | P | Unpackaged requires bootstrapper initialization |
| `PushNotificationManager.Unregister()` | Y | Y | P | |
| Raw push notifications | Y | Y | P | |
| Visual cloud toasts | Y | Y | P | |

## App Lifecycle

| API | Packaged | Unpackaged | Self-Contained | Notes |
|-----|----------|-----------|----------------|-------|
| `AppInstance.GetCurrent()` | Y | Y | Y | |
| `AppInstance.FindOrRegisterForKey()` | Y | Y | Y | |
| `AppInstance.Restart()` | Y | Y | Y | |
| `AppInstance.GetActivatedEventArgs()` | Y | Y | Y | |
| `ActivationRegistrationManager` | Y | Y | Y | Registration mechanisms differ by app type |

## MRT Core (Resources)

| API | Packaged | Unpackaged | Self-Contained | Notes |
|-----|----------|-----------|----------------|-------|
| `ResourceLoader` | Y | Y | Y | Unpackaged: loads from `[module].pri` or `resources.pri` |
| `ResourceManager` | Y | Y | Y | |
| `ApplicationLanguages.PrimaryLanguageOverride` | Y | Y | Y | Packaged: persisted across sessions. Unpackaged: process-lifetime only |
| `ApplicationLanguages.ManifestLanguages` | Y | N | N | Requires package manifest; returns empty list for unpackaged |

## Application Data

| API | Packaged | Unpackaged | Self-Contained | Notes |
|-----|----------|-----------|----------------|-------|
| `ApplicationData.GetDefault()` | Y | N | N | Requires package identity |
| `ApplicationData.GetForUnpackaged()` | N | Y | Y | Unpackaged apps only |

## Deployment

| API | Packaged | Unpackaged | Self-Contained | Notes |
|-----|----------|-----------|----------------|-------|
| `DeploymentManager.GetStatus()` | Y | Y | Y | |
| `DeploymentManager.Initialize()` | Y | Y | N | Not needed for self-contained |
| Bootstrap API (`MddBootstrapInitialize`) | N/A | Y | N/A | Framework-dependent unpackaged apps only |

## Windowing

| API | Packaged | Unpackaged | Self-Contained | Notes |
|-----|----------|-----------|----------------|-------|
| `AppWindow` | Y | Y | Y | |
| `DisplayArea` | Y | Y | Y | |
| Placement APIs (experimental) | Y | Y | Y | Requires WinAppSDK 2.0 Experimental |

## Version Info

| API | Packaged | Unpackaged | Self-Contained | Notes |
|-----|----------|-----------|----------------|-------|
| `ReleaseInfo` | Y | Y | Y | Available since WinAppSDK 1.8 stable |
| `RuntimeInfo` | Y | Y | Y | Available since WinAppSDK 1.8 stable |

## Named Object Security

| API | Packaged | Unpackaged | Self-Contained | Notes |
|-----|----------|-----------|----------------|-------|
| `GetSecurityDescriptorForAppContainerNames` | Y | Y | Y | Primarily useful for sharing between packaged and Win32 processes |

## Storage Pickers (Experimental)

| API | Packaged | Unpackaged | Self-Contained | Notes |
|-----|----------|-----------|----------------|-------|
| `FolderPicker` | Y | Y | Y | WinAppSDK pickers support both packaged and unpackaged |
| `FileOpenPicker` | Y | Y | Y | |
| `FileSavePicker` | Y | Y | Y | |

## Windows Copilot Runtime (WCR)

| API | Packaged | Unpackaged | Self-Contained | Notes |
|-----|----------|-----------|----------------|-------|
| Phi Silica / LanguageModel | Y | Y | N | Requires Copilot+ hardware; x64/ARM64 only (no x86) |
| ImageDescriptionGenerator | Y | Y | N | Requires Copilot+ hardware |
| TextRecognizer | Y | Y | N | Requires Copilot+ hardware |
| ImageSuperResolution | Y | Y | N | Requires Copilot+ hardware |

## Key Considerations

### Packaged vs Unpackaged

- **Packaged apps** have a package identity, which enables features like
  ms-appx:// URI scheme, ApplicationData.GetDefault(), manifest-based
  notification registration, and ManifestLanguages.
- **Unpackaged apps** must use alternative registration paths and cannot rely
  on package identity. Some APIs provide unpackaged-specific alternatives
  (e.g., `ApplicationData.GetForUnpackaged()`).

### Self-Contained vs Framework-Dependent

- **Self-contained** apps bundle the WinAppSDK runtime and do not need the
  framework package installed. However, some APIs that depend on framework
  package services (Push Notifications, WCR) may have limited support.
- **Framework-dependent** apps require the WinAppSDK framework package to be
  installed on the target machine. All APIs are available when the correct
  framework version is present.

### Minimum OS Version

- Windows App SDK generally requires Windows 10 version 1809 (build 17763)
  or later.
- Some features require newer Windows versions. Check the individual API
  documentation for specific version requirements.
- WCR features require Windows 11 with Copilot+ capable hardware.
