# Windows App SDK – AI Contributor Guide

Comprehensive guidance for AI contributions to the Windows App SDK.

## Quick Reference

- **Build**: Use `BuildAll.ps1` or `BuildAll.cmd` at repo root (builds the full SDK solution)
- **Run**: Deploy and test on Desktop (x64, x86, ARM64) in Debug and Release configurations
- **Verify**: Run tests with `TestAll.ps1` or `TestAll.cmd`
- **Exit code 0 = success** – do not proceed if build fails

### Build Examples
```powershell
./BuildAll.ps1                                       # Build all SDK components
./BuildAll.ps1 -Platform x64 -Configuration Release # Specific platform and config
msbuild WindowsAppRuntime.sln /p:Configuration=Debug /p:Platform=x64
```

## Key Rules

- Code should be **production-quality** – follow SDK coding standards and best practices
- Follow **modular design** – each component should have clear boundaries and responsibilities
- Support all platforms: x64, x86, ARM64 in both Debug and Release
- Set minimum supported OS version to Windows 10 version 1809 (build 17763)
- Include copyright headers in all source files
- Build clean with no warnings or errors
- Ensure all tests pass before submitting changes

## Project Structure

The SDK follows this organization:
```
\dev                    # Source code for SDK components
     \<ComponentName>   # Individual SDK component
\build                  # Build scripts and pipeline definitions
\test                   # Test projects
\tools                  # Development tools and utilities
\specs                  # Feature specifications
\docs                   # Documentation
```

- **ComponentName**: SDK component (e.g., `AppLifecycle`, `DynamicDependency`, `MRTCore`)
- **Language**: Primarily C++ (C++/WinRT) with some C# projections
- **Tests**: Located under `\test` with component-specific test projects

## Style Enforcement

- **C#**: Follow `.editorconfig` at repo root (4-space indent, Allman braces, UTF-8 BOM)
- **C++**: Use C++/WinRT; follow `docs/Coding-Guidelines.md`
- **XAML**: Use consistent formatting

## Copyright Headers

For C#/C++/IDL files:
```csharp
// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.
```

For XAML files:
```xml
<!-- Copyright (c) Microsoft Corporation.
     Licensed under the MIT License. -->
```

## When to Ask for Clarification

- Ambiguous requirements after reviewing docs
- Cross-feature impact unclear
- API usage patterns not well documented

## Detailed Documentation

- [Coding Guidelines](docs/Coding-Guidelines.md) – Complete coding standards and checklist
- [Contributor Guide](docs/contributor-guide.md) – Contribution requirements
- [PR Template](docs/pull_request_template.md) – Pull request checklist
- [Windows App SDK Docs](https://docs.microsoft.com/windows/apps/windows-app-sdk/) – Official documentation
