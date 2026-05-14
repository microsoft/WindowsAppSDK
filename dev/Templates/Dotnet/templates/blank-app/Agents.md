# Copilot Agent Instructions -- WinUI 3 / WinAppSDK

## Project Overview

This is a **WinUI 3** desktop application built on the **Windows App SDK**. It uses MSIX packaging and supports x86, x64, and ARM64 architectures.

> **Source of truth for versions & names:** Always read the project `.csproj` to determine the current `TargetFramework`, `RuntimeIdentifiers`, `Platforms`, `RootNamespace`, and `Microsoft.WindowsAppSDK` package version. Never hard-code project names or version numbers in instruction files.
>
> Throughout this document and the instruction files, `<ProjectName>` is a placeholder -- replace it with the actual project folder/assembly name (derived from the `.csproj` filename).

| Property | How to determine |
|---|---|
| UI Framework | WinUI 3 (`Microsoft.UI.Xaml`) -- always used |
| App SDK | Read `Microsoft.WindowsAppSDK` version from `.csproj` `<PackageReference>` |
| Runtime / TFM | Read `<TargetFramework>` from `.csproj` (e.g., `net10.0-windows10.0.26100.0`) |
| Target OS | Derived from `<TargetFramework>` and `<TargetPlatformMinVersion>` in `.csproj` |
| Platforms | Read `<Platforms>` from `.csproj` (e.g., `x86;x64;ARM64`) |
| Packaging | MSIX (`<EnableMsixTooling>true</EnableMsixTooling>`) |
| Namespace | Read `<RootNamespace>` from `.csproj` |
| Nullable | Read `<Nullable>` from `.csproj` |

> **Default TFM:** Templates ship with `net10.0` by default. Pass
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
1. **Review the original goal** -- Re-read the user's request and confirm you understand the intent.
2. **Check existing code** -- Search for related implementations to avoid duplication (DRY).
3. **Find the right API** -- If the task involves a platform capability (AI, UI controls, file access, notifications, windowing, widgets, sensors, etc.), first check the [Windows APIs catalog](.github/instructions/windows-apis.instructions.md) and then look up the correct API in the [WinUI 3 API Reference](https://learn.microsoft.com/en-us/windows/windows-app-sdk/api/winrt/) before writing code.
4. **Plan the approach** -- Consider SOLID principles and identify which classes/interfaces are involved.

### While Writing Code

> **Agent Rule -- MANDATORY:** Steps 5-8 are **not** passive references. You **must** actually open and read the linked instruction file before writing code that falls within its scope. Do not skip this -- these files contain rules, anti-patterns, and checklists that must be applied.

5. **Apply Design Principles** -- **Read** [design-principles](.github/instructions/design-principles.instructions.md) before adding/refactoring classes or logic. Apply DRY, KISS, SOLID, YAGNI.
6. **Follow Fundamentals** -- **Read the applicable instruction files** based on what you're changing:
   - Adding or changing **UI controls / XAML**? -> Read [accessibility](.github/instructions/accessibility.instructions.md) (AutomationProperties, keyboard nav, contrast) AND [performance](.github/instructions/performance.instructions.md) (x:Bind, x:Load, virtualization).
   - Adding or changing **user-facing strings** (labels, messages, tooltips)? -> Read [globalization](.github/instructions/globalization.instructions.md) (`.resw` files, `x:Uid`, `ResourceLoader`).
   - Handling **secrets, user input, HTTP, or permissions**? -> Read [security](.github/instructions/security.instructions.md) (no hard-coded secrets, input validation, least privilege).
   - Working on **data binding, collections, async/IO, or layout**? -> Read [performance](.github/instructions/performance.instructions.md) (x:Bind, virtualization, async patterns).
7. **Respect Code Quality Rules** -- **Read** [code-quality](.github/instructions/code-quality.instructions.md) before writing code. Follow all CA*/SA*/IDE* analyzer rules and naming conventions.
8. **Follow WinUI Patterns** -- **Read** [winui-best-practices](.github/instructions/winui-best-practices.instructions.md) for MVVM, x:Bind, community toolkit, and API verification.

### After Writing Code
9. **Remove unused code** -- Delete unused `using` statements, dead code, commented-out blocks.
10. **Write unit tests** -- Every new public method/class needs tests. **Read** [testing](.github/instructions/testing.instructions.md) for framework setup, naming conventions (`MethodName_Scenario_ExpectedResult`), AAA pattern, and `dotnet test` commands.
11. **Build the project** -- Detect the platform first (`$Platform = $env:PROCESSOR_ARCHITECTURE`), then run `dotnet build -c Debug -p:Platform=$Platform` from the project folder and fix all warnings/errors. **If build errors occur, follow the Troubleshooting Build Errors workflow below.**
12. **Run tests** -- Run tests related to the change using `--filter` (see [testing](.github/instructions/testing.instructions.md)). Run the full suite only when the change is cross-cutting.
13. **Run the app with package identity** -- Use `dotnet run` (preferred -- the project references `Microsoft.Windows.SDK.BuildTools.WinApp`, which automatically invokes `winapp run` to register a loose-layout package and launch via AUMID). See [Build, Run & Deploy](#build-run--deploy) below for advanced scenarios.
14. **Re-review against original goal** -- Confirm the implementation matches the user's request.

### Troubleshooting Build Errors

> **Agent Rule -- MANDATORY:** When a build fails due to an unknown type, missing namespace, unresolved API, or similar definition error, follow this escalation order. **Do NOT jump straight to reading `.winmd` files or using `ildasm`/decompilers** -- always try web search first.

**Step 1 -- Web Search (ALWAYS try first):**
1. Open and read [windows-apis.instructions.md](.github/instructions/windows-apis.instructions.md) -- it contains the API namespace catalog and lookup guidance.
2. Translate the unknown type/namespace into search keywords (e.g., `ImageDescription` -> "WinAppSDK ImageDescription API").
3. Use `web_search` or `web_fetch` to search the [WinAppSDK API Reference](https://learn.microsoft.com/en-us/windows/windows-app-sdk/api/winrt/) and the [Platform SDK API Reference](https://learn.microsoft.com/en-us/uwp/api/) for the correct namespace, class name, and method signatures.
4. Check the [release notes](https://learn.microsoft.com/en-us/windows/apps/windows-app-sdk/stable-channel) to verify the API is available in the project's SDK version (read from `.csproj`).

**Step 2 -- Sample Repos:**
If web search finds the API but usage is unclear, search the sample repositories listed in [windows-apis.instructions.md](.github/instructions/windows-apis.instructions.md) for working examples.

**Step 3 -- WinMD / Decompiler (last resort only):**
Only if Steps 1-2 fail to resolve the issue, then inspect `.winmd` metadata files or use decompilation tools to discover the exact type definitions. This is a fallback, not the default approach.

## Build, Run & Deploy

This is an MSIX-packaged WinUI 3 app. You **must** pass both `-c` (Configuration) and `-p:Platform=` to every `dotnet build`/`dotnet test` command.

This template references the [`Microsoft.Windows.SDK.BuildTools.WinApp`](https://www.nuget.org/packages/Microsoft.Windows.SDK.BuildTools.WinApp) NuGet package, which hooks `dotnet run` to invoke the [`winapp` CLI](https://github.com/microsoft/WinAppCli). Use `dotnet run` for everyday inner-loop development -- you do not need to call `Add-AppxPackage` or `MakeAppx.exe` by hand.

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
  # If not enabled: Settings -> System -> For developers -> Developer Mode -> On
  ```
- **`winapp` CLI** -- installed transitively via the `Microsoft.Windows.SDK.BuildTools.WinApp` NuGet reference (no separate install needed for `dotnet run`). To use `winapp` directly from the terminal for advanced scenarios (manifest editing, certificate management, packaging), install it standalone:
  ```powershell
  winget install Microsoft.WinAppCli --source winget
  ```

### Detect Platform

**Always detect the machine's architecture first** -- never hardcode a platform value. Run this once at the start of every build/test session:

```powershell
# Detect the current machine's CPU architecture
# (returns AMD64 on x64 boxes, ARM64 on ARM64 boxes, x86 on 32-bit boxes)
$arch = $env:PROCESSOR_ARCHITECTURE
$Platform = if ($arch -eq 'AMD64') { 'x64' } else { $arch }   # MSBuild expects x64/x86/ARM64
```

Use `$Platform` in all subsequent `dotnet` commands.

### Build

```powershell
# Run from the project folder containing the .csproj
cd <ProjectName>

# Detect platform (see above)
$arch = $env:PROCESSOR_ARCHITECTURE
$Platform = if ($arch -eq 'AMD64') { 'x64' } else { $arch }

# Debug build (matches current machine)
dotnet build -c Debug -p:Platform=$Platform

# Release build
dotnet build -c Release -p:Platform=$Platform
```

### Run with Package Identity (preferred)

The template references `Microsoft.Windows.SDK.BuildTools.WinApp`, which makes `dotnet run` register a loose-layout package via `winapp run` and launch the app via AUMID activation -- giving it the same package identity it would have in production:

```powershell
$arch = $env:PROCESSOR_ARCHITECTURE
$Platform = if ($arch -eq 'AMD64') { 'x64' } else { $arch }

dotnet run -c Debug -p:Platform=$Platform
```

The CLI prints the registered package's AUMID and the launched process's PID -- attach a debugger to that PID for runtime debugging.

#### Useful MSBuild knobs (set in `.csproj` `<PropertyGroup>`)

| Property | When to set |
|---|---|
| `EnableWinAppRunSupport=false` | Disable the `dotnet run` integration entirely (e.g., to launch unpackaged) |
| `WinAppRunUseExecutionAlias=true` | For console apps -- launches via `uap5:ExecutionAlias` so stdin/stdout stay in the terminal. Add the alias first with `winapp manifest add-alias`. |
| `WinAppRunNoLaunch=true` | Register the package but don't launch (attach your IDE's debugger before launch) |
| `WinAppLaunchArgs="--flag value"` | Pass arguments to the app on launch |

#### Manual `winapp run` (when not using `dotnet run`)

```powershell
# Read <TargetFramework> from .csproj first; example uses net10.0-windows10.0.26100.0
winapp run .\bin\$Platform\Debug\<TargetFramework>

# Pass args after -- to avoid escaping
winapp run .\bin\$Platform\Debug\<TargetFramework> -- --my-flag value

# Console app: keep stdin/stdout in the current terminal (requires uap5:ExecutionAlias)
winapp run .\bin\$Platform\Debug\<TargetFramework> --with-alias

# Wipe LocalState/settings between runs to test first-run behavior
winapp run .\bin\$Platform\Debug\<TargetFramework> --clean
```

#### Run Tests

```powershell
# Run from the test project folder
cd <ProjectName>.Tests
$arch = $env:PROCESSOR_ARCHITECTURE
$Platform = if ($arch -eq 'AMD64') { 'x64' } else { $arch }
dotnet test -c Debug -p:Platform=$Platform
```

### winapp CLI command reference

The `winapp` CLI is the canonical entry point for app-identity, packaging, certificate, and asset operations. Reach for it instead of hand-rolling `MakeAppx`/`SignTool`/`Add-AppxPackage` invocations.

| Scenario | Command | Notes |
|---|---|---|
| **Run/debug with identity (loose layout)** | `dotnet run` (or `winapp run <build-output>`) | Default for inner loop. Registers full loose-layout package. |
| **Console app inner loop** | Set `WinAppRunUseExecutionAlias=true` in `.csproj`, then `dotnet run` | Requires `uap5:ExecutionAlias` -- add via `winapp manifest add-alias`. |
| **Sparse identity on a single exe** | `winapp create-debug-identity .\bin\Debug\<TFM>\<ProjectName>.exe` | Use when the exe is outside the build folder, or for IDE F5 startup debugging. |
| **Stop debugging / clean up** | `winapp unregister` | Removes dev packages registered for the current project. |
| **Generate dev signing cert** | `winapp cert generate --manifest .\Package.appxmanifest --install` | Reads publisher from manifest. Stored as `devcert.pfx` in the project. |
| **Inspect a cert** | `winapp cert info .\devcert.pfx` | Verify subject matches manifest publisher. |
| **Sign a file** | `winapp sign .\MyApp.msix --cert .\devcert.pfx` | Wraps `signtool`. |
| **Build distribution MSIX** | `winapp pack .\bin\$Platform\Release\<TFM>\win-<rid> --cert .\devcert.pfx` | Auto-resolves `$targetnametoken$`, registers third-party WinRT components. |
| **Self-contained MSIX (bundles WinAppSDK)** | `winapp pack ... --self-contained` | No runtime dependency on the framework package. |
| **Regenerate Square44/Square150/etc. icons** | `winapp manifest update-assets .\branding\logo.svg` | SVG preferred -- rendered at all 5 scale and 14 targetsize variants. |
| **Add execution alias** | `winapp manifest add-alias` | Required for console-app inline I/O via `WinAppRunUseExecutionAlias`. |
| **Underlying SDK tools** | `winapp tool signtool ...`, `winapp tool makeappx ...` | Falls back to the raw [`Microsoft.Windows.SDK.BuildTools`](https://www.nuget.org/packages/Microsoft.Windows.SDK.BuildTools/) tools when needed. |

For full reference, see the [winapp CLI usage docs](https://github.com/microsoft/WinAppCli/blob/main/docs/usage.md) and the [Debugging Guide](https://github.com/microsoft/WinAppCli/blob/main/docs/debugging.md).

### Fallback: register a loose layout manually

Only use this if you've explicitly disabled the `winapp` integration (`<EnableWinAppRunSupport>false</EnableWinAppRunSupport>`) or are debugging the deployment itself. The supported path is `dotnet run` / `winapp run`.

```powershell
$arch = $env:PROCESSOR_ARCHITECTURE
$Platform = if ($arch -eq 'AMD64') { 'x64' } else { $arch }
$Rid = $Platform.ToLower()   # arm64, x64, x86

# Register the built MSIX package from the build output
# Read <TargetFramework> from .csproj to build the correct path.
Add-AppxPackage -Register ".\<ProjectName>\bin\$Platform\Debug\<TargetFramework>\win-$Rid\AppxManifest.xml"
```

> **Note:** Replace `<TargetFramework>` with the actual value from `.csproj` (e.g., `net10.0-windows10.0.26100.0`).

If the launch fails because an old instance is still running, terminate it with `taskkill /IM <ProjectName>.exe /F` before re-running.

## Key Rules (Always Enforced)

- **Every change must build and pass tests** -- Run `dotnet build` and `dotnet test` (see [Build, Run & Deploy](#build-run--deploy)) before considering any task complete.
- **Follow all instruction files** -- The detailed rules in `.github/instructions/` are authoritative. **You must actually open and read them** (not just acknowledge they exist) when working within their scope. See the trigger conditions in steps 5-8 above.
- **Web search before decompilation** -- When facing unknown types or build errors, always search the web / API docs first. Only use WinMD/ILDASM as a last resort (see [Troubleshooting Build Errors](#troubleshooting-build-errors)).
- **Use `winapp` for app-identity / packaging / signing** -- Don't hand-roll `MakeAppx`/`SignTool`/`Add-AppxPackage` invocations. The CLI keeps the manifest, certificate, and registration steps in sync.

## Windows AI Prerequisites

When integrating Windows AI APIs (Phi Silica, Windows Vision -- ImageDescription,
TextRecognizer, ImageScaler, etc.) -- see
[windows-apis.instructions.md](.github/instructions/windows-apis.instructions.md):

1. **Package identity is required.** All Windows AI APIs require the app to
   run with package identity. The `dotnet run` flow described above already
   provides this. If you're testing outside `dotnet run`, register identity
   first with `winapp run` or `winapp create-debug-identity`.
2. **Manifest capabilities.** Add the capabilities each API requires to
   `Package.appxmanifest` (commonly `runFullTrust`; some scenarios additionally
   need `internetClient`). Check the API's docs page for the exact list.
3. **Hardware / OS gating.** Some APIs require a Copilot+ PC (NPU) or a
   minimum Windows build. Always probe availability with the API's
   `IsAvailable` / `EnsureReadyAsync` pattern (or equivalent) and provide a
   graceful fallback for unsupported devices.
4. **Verify locally before checking in.** After capability or manifest
   changes, re-run `dotnet run` (or `winapp run`) so the registered identity
   reflects the updated manifest -- a stale registration will silently use
   the old capability set.



