# Copilot Agent Instructions ΓÇö WinUI 3 / WinAppSDK

## Project Overview

This is a **WinUI 3** desktop application built on the **Windows App SDK**. It uses MSIX packaging and supports x86, x64, and ARM64 architectures.

> **Source of truth for versions & names:** Always read the project `.csproj` to determine the current `TargetFramework`, `RuntimeIdentifiers`, `Platforms`, `RootNamespace`, and `Microsoft.WindowsAppSDK` package version. Never hard-code project names or version numbers in instruction files.
>
> Throughout this document and the instruction files, `<ProjectName>` is a placeholder ΓÇö replace it with the actual project folder/assembly name (derived from the `.csproj` filename).

| Property | How to determine |
|---|---|
| UI Framework | WinUI 3 (`Microsoft.UI.Xaml`) ΓÇö always used |
| App SDK | Read `Microsoft.WindowsAppSDK` version from `.csproj` `<PackageReference>` |
| Runtime / TFM | Read `<TargetFramework>` from `.csproj` (e.g., `net8.0-windows10.0.19041.0`) |
| Target OS | Derived from `<TargetFramework>` and `<TargetPlatformMinVersion>` in `.csproj` |
| Platforms | Read `<Platforms>` from `.csproj` (e.g., `x86;x64;ARM64`) |
| Packaging | MSIX (`<EnableMsixTooling>true</EnableMsixTooling>`) |
| Namespace | Read `<RootNamespace>` from `.csproj` |
| Nullable | Read `<Nullable>` from `.csproj` |

> **Default TFM:** Templates ship with `net8.0` by default. Pass
> `--dotnet-version <tfm>` (for example `net10.0`) when running `dotnet new ...`
> or edit `<TargetFramework>` inside the generated `.csproj` before the first
> build if you need a newer framework. Keep `<RuntimeIdentifiers>` synchronized
> with the framework you pick.

## Instruction Files Index

All detailed agent instructions are organized under `.github/instructions/`:

| File | Scope |
|---|---|
| [design-principles.instructions.md](.github/instructions/design-principles.instructions.md) | DRY, KISS, SOLID, YAGNI |
| [globalization.instructions.md](.github/instructions/globalization.instructions.md) | Globalization & Localization |
| [accessibility.instructions.md](.github/instructions/accessibility.instructions.md) | Accessibility |
| [security.instructions.md](.github/instructions/security.instructions.md) | Security |
| [performance.instructions.md](.github/instructions/performance.instructions.md) | Performance |
| [code-quality.instructions.md](.github/instructions/code-quality.instructions.md) | Static Analysis, StyleCop, Code Cleanup |
| [winui-best-practices.instructions.md](.github/instructions/winui-best-practices.instructions.md) | WinUI 3 / WinAppSDK patterns & references |
| [windows-apis.instructions.md](.github/instructions/windows-apis.instructions.md) | WinAppSDK & Platform SDK API namespace catalog & lookup guidance |
| [testing.instructions.md](.github/instructions/testing.instructions.md) | Unit Testing, Build & Run |

## Core Agent Workflow

Every time you work on this codebase, follow this checklist:

### Before Writing Code
1. **Review the original goal** ΓÇö Re-read the user's request and confirm you understand the intent.
2. **Check existing code** ΓÇö Search for related implementations to avoid duplication (DRY).
3. **Find the right API** ΓÇö If the task involves a platform capability (AI, UI controls, file access, notifications, windowing, widgets, sensors, etc.), first check the [Windows APIs catalog](.github/instructions/windows-apis.instructions.md) and then look up the correct API in the [WinUI 3 API Reference](https://learn.microsoft.com/en-us/windows/windows-app-sdk/api/winrt/) before writing code.
4. **Plan the approach** ΓÇö Consider SOLID principles and identify which classes/interfaces are involved.

### While Writing Code

> **Agent Rule ΓÇö MANDATORY:** Steps 5ΓÇô8 are **not** passive references. You **must** actually open and read the linked instruction file before writing code that falls within its scope. Do not skip this ΓÇö these files contain rules, anti-patterns, and checklists that must be applied.

5. **Apply Design Principles** ΓÇö **Read** [design-principles](.github/instructions/design-principles.instructions.md) before adding/refactoring classes or logic. Apply DRY, KISS, SOLID, YAGNI.
6. **Follow Fundamentals** ΓÇö **Read the applicable instruction files** based on what you're changing:
   - Adding or changing **UI controls / XAML**? ΓåÆ Read [accessibility](.github/instructions/accessibility.instructions.md) (AutomationProperties, keyboard nav, contrast) AND [performance](.github/instructions/performance.instructions.md) (x:Bind, x:Load, virtualization).
   - Adding or changing **user-facing strings** (labels, messages, tooltips)? ΓåÆ Read [globalization](.github/instructions/globalization.instructions.md) (`.resw` files, `x:Uid`, `ResourceLoader`).
   - Handling **secrets, user input, HTTP, or permissions**? ΓåÆ Read [security](.github/instructions/security.instructions.md) (no hard-coded secrets, input validation, least privilege).
   - Working on **data binding, collections, async/IO, or layout**? ΓåÆ Read [performance](.github/instructions/performance.instructions.md) (x:Bind, virtualization, async patterns).
7. **Respect Code Quality Rules** ΓÇö **Read** [code-quality](.github/instructions/code-quality.instructions.md) before writing code. Follow all CA*/SA*/IDE* analyzer rules and naming conventions.
8. **Follow WinUI Patterns** ΓÇö **Read** [winui-best-practices](.github/instructions/winui-best-practices.instructions.md) for MVVM, x:Bind, community toolkit, and API verification.

### After Writing Code
9. **Remove unused code** ΓÇö Delete unused `using` statements, dead code, commented-out blocks.
10. **Write unit tests** ΓÇö Every new public method/class needs tests. **Read** [testing](.github/instructions/testing.instructions.md) for framework setup, naming conventions (`MethodName_Scenario_ExpectedResult`), AAA pattern, and `dotnet test` commands.
11. **Build the project** ΓÇö Detect the platform first (`$Platform = $env:PROCESSOR_ARCHITECTURE`), then run `dotnet build -c Debug -p:Platform=$Platform` from the project folder and fix all warnings/errors. **If build errors occur, follow the Troubleshooting Build Errors workflow below.**
12. **Run tests** ΓÇö Run tests related to the change using `--filter` (see [testing](.github/instructions/testing.instructions.md)). Run the full suite only when the change is cross-cutting.
13. **Register the MSIX package** ΓÇö See [Build, Run & Deploy](#build-run--deploy) below.
14. **Re-review against original goal** ΓÇö Confirm the implementation matches the user's request.

### Troubleshooting Build Errors

> **Agent Rule ΓÇö MANDATORY:** When a build fails due to an unknown type, missing namespace, unresolved API, or similar definition error, follow this escalation order. **Do NOT jump straight to reading `.winmd` files or using `ildasm`/decompilers** ΓÇö always try web search first.

**Step 1 ΓÇö Web Search (ALWAYS try first):**
1. Open and read [windows-apis.instructions.md](.github/instructions/windows-apis.instructions.md) ΓÇö it contains the API namespace catalog and lookup guidance.
2. Translate the unknown type/namespace into search keywords (e.g., `ImageDescription` ΓåÆ "WinAppSDK ImageDescription API").
3. Use `web_search` or `web_fetch` to search the [WinAppSDK API Reference](https://learn.microsoft.com/en-us/windows/windows-app-sdk/api/winrt/) and the [Platform SDK API Reference](https://learn.microsoft.com/en-us/uwp/api/) for the correct namespace, class name, and method signatures.
4. Check the [release notes](https://learn.microsoft.com/en-us/windows/apps/windows-app-sdk/stable-channel) to verify the API is available in the project's SDK version (read from `.csproj`).

**Step 2 ΓÇö Sample Repos:**
If web search finds the API but usage is unclear, search the sample repositories listed in [windows-apis.instructions.md](.github/instructions/windows-apis.instructions.md) for working examples.

**Step 3 ΓÇö WinMD / Decompiler (last resort only):**
Only if Steps 1ΓÇô2 fail to resolve the issue, then inspect `.winmd` metadata files or use decompilation tools to discover the exact type definitions. This is a fallback, not the default approach.

## Build, Run & Deploy

This is an MSIX-packaged WinUI 3 app. You **must** pass both `-c` (Configuration) and `-p:Platform=` to every `dotnet` command.

### Dotnet CLI Workflow

- Prefer `dotnet new` for scaffolding projects and items so namespaces, GUIDs,
  and resource wiring stay correct.
- Common commands:
  - `dotnet new winui -n MyApp`
  - `dotnet new winui-page -n SettingsPage --project .\MyApp\MyApp.csproj`
  - `dotnet new winui-usercontrol -n ProfileCard --project .\MyApp\MyApp.csproj`
- Discover available scaffolds with `dotnet new winui --list` (shows supported
  parameters such as `--dotnet-version`).
- Need a newer TFM? Supply `--dotnet-version net10.0` during scaffold or edit
  `<TargetFramework>` afterward before the first build.

### Prerequisites

- **Developer Mode must be enabled** on Windows. Verify with:
  ```powershell
  # Check developer mode
  Get-WindowsDeveloperLicense
  # If not enabled: Settings ΓåÆ System ΓåÆ For developers ΓåÆ Developer Mode ΓåÆ On
  ```

### Detect Platform

**Always detect the machine's architecture first** ΓÇö never hardcode a platform value. Run this once at the start of every build/test session:

```powershell
# Detect the current machine's CPU architecture (returns x64, ARM64, or x86)
$Platform = $env:PROCESSOR_ARCHITECTURE
```

Use `$Platform` in all subsequent `dotnet` commands.

### Build

```powershell
# Run from the project folder containing the .csproj
cd <ProjectName>

# Detect platform
$Platform = $env:PROCESSOR_ARCHITECTURE

# Debug build (matches current machine)
dotnet build -c Debug -p:Platform=$Platform

# Release build
dotnet build -c Release -p:Platform=$Platform
```

### Register & Run the MSIX Package (Sideload)

After building, register the app package so Windows can launch it:

```powershell
$Platform = $env:PROCESSOR_ARCHITECTURE
$Rid = $Platform.ToLower()   # e.g. arm64, x64, x86

# Register the built MSIX package from the build output
# Read <TargetFramework> from the project .csproj to build the correct path.
Add-AppxPackage -Register ".\<ProjectName>\bin\$Platform\Debug\<TargetFramework>\win-$Rid\AppxManifest.xml"
```

> **Note:** Replace `<TargetFramework>` with the actual value from `.csproj` (e.g., `net8.0-windows10.0.19041.0`).

### Run from the CLI

- Quick smoke tests: `dotnet run -c Debug -p:Platform=$Platform` from the
  project folder.
- Launch a packaged build: `winapp run .\<ProjectName>\bin\$Platform\Debug\<TargetFramework>\<ProjectName>.exe` after registering the MSIX output.
- If the launch fails because an old instance is still running, terminate it
  with `taskkill /IM <ProjectName>.exe /F` before re-running.

### Run Tests

```powershell
# Run from the test project folder
cd <ProjectName>.Tests
$Platform = $env:PROCESSOR_ARCHITECTURE
dotnet test -c Debug -p:Platform=$Platform
```

## Key Rules (Always Enforced)

- **Every change must build and pass tests** ΓÇö Run `dotnet build` and `dotnet test` (see [Build, Run & Deploy](#build-run--deploy)) before considering any task complete.
- **Follow all instruction files** ΓÇö The detailed rules in `.github/instructions/` are authoritative. **You must actually open and read them** (not just acknowledge they exist) when working within their scope. See the trigger conditions in steps 5ΓÇô8 above.
- **Web search before decompilation** ΓÇö When facing unknown types or build errors, always search the web / API docs first. Only use WinMD/ILDASM as a last resort (see [Troubleshooting Build Errors](#troubleshooting-build-errors)).

## Windows AI Prerequisites

When integrating Phi Silica, Windows Vision, or other Windows AI APIs (see
[windows-apis.instructions.md](.github/instructions/windows-apis.instructions.md)):

1. **Manifest capabilities:** Add the required capabilities (for example
  `internetClient`, `machineLearning`, `systemManagement`) to the app manifest
  before calling these APIs.
2. **LAF token:** Phi Silica endpoints need a Local API key. Acquire it via the
  Windows AI documentation, store it securely (never in source), and document
  the manual step in the PR.
3. **MSBuild overrides:** Some scenarios need temporary
  `<WindowsAppSDKSelfContained>` or package-version overrides. Capture the
  reasoning in the PR description and remove overrides once upstream fixes
  land.
4. **Fallback path:** If LAF or required hardware is unavailable, use the
  Windows Vision / AI APIs that do not require the token and describe the
  limitations in the instruction files or README so Copilot can pick the right
  approach.

