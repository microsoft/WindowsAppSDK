# Windows App SDK Visual Studio Extensions

This directory contains the Visual Studio extensions (VSIX) for Windows App SDK, including project templates, item templates, and project wizards for creating WinUI 3 applications.

## Structure

```
dev/VSIX/
├── Extension/                      # VSIX extension packages
│   ├── Cs/                         # C# extension
│   │   ├── Common/                 # Localized VSPackage resource files
│   │   └── Dev17/                  # VS 2022 extension project & manifests
│   └── Cpp/                        # C++ extension
│       ├── Common/                 # Localized VSPackage resource files
│       └── Dev17/                  # VS 2022 extension project, manifests & NuGetPackageList.cs
├── ProjectTemplates/               # Visual Studio project templates
│   ├── Desktop/                    # Desktop app templates
│   │   ├── CSharp/                 # SingleProjectPackagedApp, PackagedApp, ClassLibrary, UnitTestApp
│   │   └── CppWinRT/              # SingleProjectPackagedApp, PackagedApp, UnitTestApp
│   └── Neutral/                    # Platform-neutral templates
│       └── CppWinRT/              # RuntimeComponent
├── ItemTemplates/                  # Visual Studio item templates
│   ├── Desktop/                    # Desktop-specific items
│   │   ├── CSharp/                # BlankWindow
│   │   └── CppWinRT/             # BlankWindow
│   └── Neutral/                    # Platform-neutral items
│       ├── CSharp/                # BlankPage, UserControl, TemplatedControl, ResourceDictionary, Resw
│       └── CppWinRT/             # BlankPage, UserControl, TemplatedControl, ResourceDictionary, Resw
├── Shared/                         # Shared code used by wizards and extensions
│   ├── WizardImplementation.cs     # Main wizard logic (NuGetPackageInstaller)
│   ├── WizardInfoBarEvents.cs      # InfoBar event handlers (NuGetInfoBarUIEvents)
│   └── OutputWindowHelper.cs       # Output window utilities
└── Tests/                          # Unit tests for VSIX components
    └── WindowsAppSDK.VSIX.UnitTests/
```

## Testing

### Unit Tests

The `Tests/WindowsAppSDK.VSIX.UnitTests` project contains unit tests for the VSIX wizard and UI components, targeting `net8.0-windows10.0.19041.0`.

#### Test Classes

1. **NuGetPackageInstallerTests** (20 tests) — Package parsing, `ProjectFinishedGenerating` behavior, NuGet installation failures, happy-path installation, `ShouldAddProjectItem`, and template-specific package count verification.

2. **WizardInfoBarEventsTests** (9 tests) — Null parameter handling, `OnClosed`, constructor storage, `SeeErrorDetails` / `ManageNuGetPackages` hyperlink routing, unknown action context, and non-hyperlink action items.

3. **ErrorMessageTests** (8 tests) — `CreateErrorMessage` for InfoBar and MessageBox formats (single/multiple packages, null project fallback, format differences) and `CreateDetailedErrorMessage` content/structure.

#### Running Tests

```powershell
# Run all VSIX unit tests
dotnet test dev\VSIX\Tests\WindowsAppSDK.VSIX.UnitTests\WindowsAppSDK.VSIX.UnitTests.csproj

# Run a specific test class
dotnet test dev\VSIX\Tests\WindowsAppSDK.VSIX.UnitTests\WindowsAppSDK.VSIX.UnitTests.csproj --filter "FullyQualifiedName~NuGetPackageInstallerTests"
```

### Test Infrastructure

The tests use:
- **MSTest** — Test framework
- **Moq** — Mocking framework for VS SDK interfaces
- **VsTestBase** — Abstract base class that pins culture to `en-US` and configures `ThreadHelper` via reflection so `ThrowIfNotOnUIThread()` passes in tests

Key helper classes:
- `VsTestBase` — Configures `JoinableTaskContext` with the test thread as the main thread
- `MockServiceSetup` — Creates mock `IComponentModel`, `EnvDTE.Project` instances (C# and C++), and provides reflection helpers (`SetPrivateField`, `GetPrivateField`, `InvokePrivateMethod`)
- `TemplateTestData` — Defines NuGet package lists and `TemplateInfo` metadata for all shipped project templates

### Shared Source Linking

The unit test project compiles the same shared wizard source files used by the extension projects (`WizardImplementation.cs`, `WizardInfoBarEvents.cs`, `OutputWindowHelper.cs`) with the `CSHARP_EXTENSION` constant defined. It also links the C# extension's `VSPackage.resx` and `VSPackage.Designer.cs` for resource string access.

## Building

The VSIX extensions are built as part of the main Windows App SDK solution:

```powershell
# Build from repository root
.\BuildAll.ps1
```

## Key Components

### Wizard Implementation

`Shared/WizardImplementation.cs` implements the `NuGetPackageInstaller` VS project wizard (`IWizard`) that:
- Parses the `$NuGetPackages$` replacement parameter to determine required packages
- Detects project type (C++ via `SolutionVCProjectGuid` vs C#)
- For C++ projects, installs NuGet packages immediately in `ProjectFinishedGenerating`
- For C# projects, defers installation until `SolutionRestoreFinished`
- Constructs error messages (`CreateErrorMessage`, `CreateDetailedErrorMessage`) and displays them via InfoBar or MessageBox

### InfoBar Events

`Shared/WizardInfoBarEvents.cs` implements `NuGetInfoBarUIEvents` (`IVsInfoBarUIEvents`) to handle user interactions with InfoBar hyperlinks:
- **ManageNuGetPackages** — Opens NuGet Package Manager via DTE command `{25fd982b-8cae-4cbd-a440-e03ffccde106}`, ID `0x100`
- **SeeErrorDetails** — Writes detailed error information to the VS Output window

### Output Window Helper

`Shared/OutputWindowHelper.cs` provides `ShowMessageInOutputWindow` for writing messages to the VS Output window with proper pane creation, activation, and formatting.

## Design Principles

### Defensive Programming

The wizard and UI components follow defensive programming practices:
- Null checks on all VS service calls
- Graceful degradation when services are unavailable
- Error logging to Output window instead of throwing exceptions
- Try-catch blocks around external service interactions

### Robustness

- InfoBar event handlers never crash the extension
- Failed package installations show user-friendly error messages
- Missing VS services log warnings rather than failing silently

## Contributing

When adding new features:
1. Add corresponding unit tests in `Tests/WindowsAppSDK.VSIX.UnitTests`
2. Follow the defensive programming patterns used in existing code
3. Document expected VS service interactions
4. Ensure all builds and tests pass before submitting

## Related Documentation

- [Windows App SDK Documentation](https://docs.microsoft.com/windows/apps/windows-app-sdk/)
- [Coding Guidelines](../../docs/Coding-Guidelines.md)
- [Contributor Guide](../../docs/contributor-guide.md)
