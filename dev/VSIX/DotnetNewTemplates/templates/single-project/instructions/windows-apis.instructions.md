---
description: 'WinAppSDK & Windows Platform SDK — API namespace catalog and lookup guidance'
applyTo: '**/*.cs, **/*.xaml, **/*.csproj'
---

# Windows APIs — WinAppSDK & Windows Platform SDK

## Sample-First Rule

> **Agent Rule — MANDATORY:** Before implementing **any** WinAppSDK or Windows Platform SDK API you have not used before, you **must** search the sample repositories below for a working example first. **Do not guess API usage patterns from documentation alone** — the docs often omit critical details that only the sample code reveals. Search **all** of the following repos, not just one:

| # | Repository | What it covers |
|---|---|---|
| 1 | [WindowsAppSDK-Samples](https://github.com/microsoft/WindowsAppSDK-Samples) | All WinAppSDK features (AI, windowing, lifecycle, notifications, etc.) |
| 2 | [AI Dev Gallery](https://github.com/microsoft/ai-dev-gallery) | On-device AI/ML patterns, model usage examples |
| 3 | [WinUI-Gallery](https://github.com/microsoft/WinUI-Gallery) | UI control patterns and XAML examples |

### How to apply

1. **Find the right API** — Translate the user's scenario/requirement into common API/programming keywords, then search the API references (Part A–B below) using those keywords to identify which API fits.
2. **Search for samples** — Once you know which API to use, search each sample repo above for the class name to find a working example.
3. **Study the sample** — Read the sample's Model / ViewModel / Service layer to understand how the API is actually called — object lifetime, required parameters, data preparation, error handling.
4. **Adapt** the sample pattern into our MVVM architecture — don't copy the sample structure wholesale, but match its API call sequence exactly.

---

> **Agent Rule:** Before implementing any feature that involves a platform capability, **consult this file** to check whether a built-in API already exists. Always verify exact class names, method signatures, and availability by following the reference links — do not guess API shapes.

---

## Part A — Windows App SDK APIs

**Full API reference:** <https://learn.microsoft.com/en-us/windows/windows-app-sdk/api/winrt/>

> **Agent Rule:** Do not rely on a hardcoded namespace list — the SDK is updated frequently. Instead, **search** the API reference above by converting the user's scenario into common programming keywords.

### How to search

1. **Translate** the user's request into API/programming terms. Examples:
   - "I want to describe an image" → search for: `image description`, `ImageDescription`, `describe image`
   - "Add a notification" → search for: `notification`, `toast`, `AppNotification`
   - "Pick a file" → search for: `file picker`, `StoragePicker`, `FileOpenPicker`
   - "Make the window always on top" → search for: `AppWindow`, `presenter`, `compact overlay`
2. **Search** the [WinAppSDK API reference](https://learn.microsoft.com/en-us/windows/windows-app-sdk/api/winrt/) using `web_search` or `web_fetch` with those keywords.
3. **Verify** the class/method exists in the SDK version used by this project (check `.csproj` `<PackageReference>` for `Microsoft.WindowsAppSDK` version).

### Key reference links

| # | Link | When to consult |
|---|---|---|
| 1 | [WinAppSDK API Reference (full)](https://learn.microsoft.com/en-us/windows/windows-app-sdk/api/winrt/) | **Always** — search and look up exact class/method signatures here |
| 2 | [Windows App SDK overview](https://learn.microsoft.com/en-us/windows/apps/windows-app-sdk/) | Feature overview, architecture |
| 3 | [Release notes (stable)](https://learn.microsoft.com/en-us/windows/apps/windows-app-sdk/stable-channel) | API availability, version support, breaking changes |
| 4 | [Windows AI overview](https://learn.microsoft.com/en-us/windows/ai/) | All AI options: Windows AI APIs, Windows ML, Foundry Local |
| 5 | [Get started with Windows AI APIs](https://learn.microsoft.com/en-us/windows/ai/apis/get-started) | Prerequisites, project setup, first AI call |
| 6 | [Windows ML overview](https://learn.microsoft.com/en-us/windows/ai/new-windows-ml/overview) | Custom ONNX model inference |
| 7 | [Foundry Local](https://learn.microsoft.com/en-us/windows/ai/foundry-local/get-started) | Run OSS LLMs locally |

---

## Part B — Windows Platform SDK (UWP / WinRT APIs)

**Full API reference:** <https://learn.microsoft.com/en-us/uwp/api/>

> **Agent Rule:** The Platform SDK (`Windows.*` namespaces) is very large and constantly evolving. Do not rely on a hardcoded list. **Search** the API reference by translating the user's requirement into programming keywords.

### How to search

1. **Translate** the user's request into API/programming terms. Examples:
   - "Send a Bluetooth message" → search for: `Bluetooth`, `RFCOMM`, `BluetoothDevice`
   - "Get the user's location" → search for: `geolocation`, `Geolocator`, `position`
   - "Read text from an image" → search for: `OCR`, `text recognition`, `OcrEngine`
   - "Copy to clipboard" → search for: `clipboard`, `DataTransfer`, `DataPackage`
2. **Search** the [Platform SDK API reference](https://learn.microsoft.com/en-us/uwp/api/) using `web_search` or `web_fetch` with those keywords.
3. **Check for WinAppSDK equivalent** — some Platform SDK APIs have newer equivalents in Part A. Always prefer the WinAppSDK version when both exist.

### Key reference links

| # | Link | When to consult |
|---|---|---|
| 1 | [Platform SDK API Reference (full)](https://learn.microsoft.com/en-us/uwp/api/) | **Search here** for any Windows capability not in WinAppSDK |
| 2 | [Windows SDK downloads](https://developer.microsoft.com/windows/downloads/windows-sdk/) | SDK versions and downloads |

---

## Validation

- Before implementing any platform feature, confirm the API is available in the current Windows App SDK version by checking the [release notes](https://learn.microsoft.com/en-us/windows/apps/windows-app-sdk/stable-channel).
- For Windows AI APIs, always implement the availability check pattern (`GetReadyState()` / `EnsureReadyAsync()`) — see the [Get started guide](https://learn.microsoft.com/en-us/windows/ai/apis/get-started).
- For features requiring specific hardware (NPU), provide a graceful fallback for unsupported devices.
- When both WinAppSDK and Platform SDK offer a similar API, prefer the WinAppSDK version.
