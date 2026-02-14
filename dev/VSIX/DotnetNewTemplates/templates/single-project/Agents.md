# Copilot Agent Instructions — WinUI 3 / WinAppSDK

## Project Overview

This is a **WinUI 3** desktop application built on the **Windows App SDK**. It uses MSIX packaging and supports x86, x64, and ARM64 architectures.

> **Source of truth for versions & names:** Always read the project `.csproj` to determine the current `TargetFramework`, `RuntimeIdentifiers`, `Platforms`, `RootNamespace`, and `Microsoft.WindowsAppSDK` package version. Never hard-code project names or version numbers in instruction files.
>
> Throughout this document and the instruction files, `<ProjectName>` is a placeholder — replace it with the actual project folder/assembly name (derived from the `.csproj` filename).

| Property | How to determine |
|---|---|
| UI Framework | WinUI 3 (`Microsoft.UI.Xaml`) — always used |
| App SDK | Read `Microsoft.WindowsAppSDK` version from `.csproj` `<PackageReference>` |
| Runtime / TFM | Read `<TargetFramework>` from `.csproj` (e.g., `net8.0-windows10.0.19041.0`) |
| Target OS | Derived from `<TargetFramework>` and `<TargetPlatformMinVersion>` in `.csproj` |
| Platforms | Read `<Platforms>` from `.csproj` (e.g., `x86;x64;ARM64`) |
| Packaging | MSIX (`<EnableMsixTooling>true</EnableMsixTooling>`) |
| Namespace | Read `<RootNamespace>` from `.csproj` |
| Nullable | Read `<Nullable>` from `.csproj` |

## Instruction Files Index

All detailed agent instructions are organized under `instructions/`:

| File | Scope |
|---|---|
| [design-principles.instructions.md](instructions/design-principles.instructions.md) | DRY, KISS, SOLID, YAGNI |
| [globalization.instructions.md](instructions/globalization.instructions.md) | Globalization & Localization |
| [accessibility.instructions.md](instructions/accessibility.instructions.md) | Accessibility |
| [security.instructions.md](instructions/security.instructions.md) | Security |
| [performance.instructions.md](instructions/performance.instructions.md) | Performance |
| [code-quality.instructions.md](instructions/code-quality.instructions.md) | Static Analysis, StyleCop, Code Cleanup |
| [winui-best-practices.instructions.md](instructions/winui-best-practices.instructions.md) | WinUI 3 / WinAppSDK patterns & references |
| [testing.instructions.md](instructions/testing.instructions.md) | Unit Testing, Build & Run |

## Core Agent Workflow

Every time you work on this codebase, follow this checklist:

### Before Writing Code
1. **Review the original goal** — Re-read the user's request and confirm you understand the intent.
2. **Check existing code** — Search for related implementations to avoid duplication (DRY).
3. **Find the right API** — If the task involves a platform capability (UI controls, file access, camera, notifications, sensors, etc.), look up the correct API in the [WinUI 3 API Reference](https://learn.microsoft.com/en-us/windows/windows-app-sdk/api/winrt/) before writing code.
4. **Plan the approach** — Consider SOLID principles and identify which classes/interfaces are involved.

### While Writing Code
5. **Apply Design Principles** — DRY, KISS, SOLID, YAGNI (see [design-principles](instructions/design-principles.instructions.md)).
6. **Follow Fundamentals** — Globalization ([globalization](instructions/globalization.instructions.md)), Accessibility ([accessibility](instructions/accessibility.instructions.md)), Security ([security](instructions/security.instructions.md)), Performance ([performance](instructions/performance.instructions.md)).
7. **Respect Code Quality Rules** — Static analysis & StyleCop (see [code-quality](instructions/code-quality.instructions.md)).
8. **Follow WinUI Patterns** — MVVM, x:Bind, community toolkit, and API verification (see [winui-best-practices](instructions/winui-best-practices.instructions.md)).

### After Writing Code
9. **Remove unused code** — Delete unused `using` statements, dead code, commented-out blocks.
10. **Write unit tests** — Every new public method/class needs tests (see [testing](instructions/testing.instructions.md)).
11. **Build the project** — Run `dotnet build -c Debug -p:Platform=x64` from the project folder and fix all warnings/errors.
12. **Run tests** — Run tests related to the change using `--filter` (see [testing](instructions/testing.instructions.md)). Run the full suite only when the change is cross-cutting.
13. **Register the MSIX package** — See [Build, Run & Deploy](#build-run--deploy) below.
14. **Re-review against original goal** — Confirm the implementation matches the user's request.

## Build, Run & Deploy

This is an MSIX-packaged WinUI 3 app. You **must** pass both `-c` (Configuration) and `-p:Platform=` to every `dotnet` command.

### Prerequisites

- **Developer Mode must be enabled** on Windows. Verify with:
  ```powershell
  # Check developer mode
  Get-WindowsDeveloperLicense
  # If not enabled: Settings → System → For developers → Developer Mode → On
  ```

### Build

```powershell
# Run from the project folder containing the .csproj
cd <ProjectName>

# Debug x64 (default development target)
dotnet build -c Debug -p:Platform=x64

# Release x64
dotnet build -c Release -p:Platform=x64

# Other platforms
dotnet build -c Debug -p:Platform=x86
dotnet build -c Debug -p:Platform=ARM64
```

### Register & Run the MSIX Package (Sideload)

After building, register the app package so Windows can launch it:

```powershell
# Register the built MSIX package from the build output
# Path pattern: .\<ProjectName>\bin\<Platform>\<Configuration>\<TargetFramework>\win-<rid>\AppxManifest.xml
# Read <TargetFramework> from the project .csproj to build the correct path.
Add-AppxPackage -Register .\<ProjectName>\bin\x64\Debug\<TargetFramework>\win-x64\AppxManifest.xml
```

> **Note:** Replace `$(TargetFramework)` with the actual value from `.csproj` (e.g., `net8.0-windows10.0.19041.0`).
> Adjust `<Platform>` and `<Configuration>` to match your build target.

### Run Tests

```powershell
# Run from the test project folder
cd <ProjectName>.Tests
dotnet test -c Debug -p:Platform=x64
```

## Key Rules (Always Enforced)

- **Every change must build and pass tests** — Run `dotnet build` and `dotnet test` (see [Build, Run & Deploy](#build-run--deploy)) before considering any task complete.
- **Follow all instruction files** — The detailed rules in `instructions/` are authoritative. Do not skip them.
