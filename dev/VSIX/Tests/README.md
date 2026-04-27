# VSIX Unit Tests

Unit tests for the Windows App SDK Visual Studio project template wizard and UI components.

## Prerequisites

- .NET 8.0 SDK (target framework: `net8.0-windows10.0.19041.0`)
- No Visual Studio installation required

> **Note:** While the VSIX extension and template projects require Visual Studio /
> `msbuild` to build (they depend on VSSDK targets not available in the `dotnet` CLI),
> the unit test project uses the SDK-style format and can be built and run with
> `dotnet test` independently.

## Running Tests

```powershell
# Run all VSIX unit tests
dotnet test dev\VSIX\Tests\WindowsAppSDK.VSIX.UnitTests\WindowsAppSDK.VSIX.UnitTests.csproj --verbosity normal

# Run a specific test class
dotnet test dev\VSIX\Tests\WindowsAppSDK.VSIX.UnitTests\WindowsAppSDK.VSIX.UnitTests.csproj --filter "FullyQualifiedName~NuGetPackageInstallerTests"
```

## Test Coverage (37 tests)

| Area | Tests | Description |
|------|-------|-------------|
| NuGetPackageInstaller | 20 | Package parsing (standard, empty, C++, unit-test, null), `ProjectFinishedGenerating` (C++ immediate install, C# deferred, project ref storage), installation failures (exception catch, partial failure, null component model / installer / project), happy path (all succeed, `RunFinished` no failures / with failures), `ShouldAddProjectItem`, and template-specific package counts |
| WizardInfoBarEvents | 9 | Null parameter handling (null element, null action item, both null), `OnClosed`, constructor storage, `SeeErrorDetails` routing, `ManageNuGetPackages` routing, unknown action context, non-hyperlink action item |
| ErrorMessages | 8 | `CreateErrorMessage` for InfoBar (single/multiple packages, null project fallback) and MessageBox formats, InfoBar vs MessageBox difference, `CreateDetailedErrorMessage` (exception type/message, multiple packages, manual-install instruction) |

## Project Structure

```
Tests/
├── Directory.Build.props                       # Overrides VSIX build props for test projects
└── WindowsAppSDK.VSIX.UnitTests/
    ├── WindowsAppSDK.VSIX.UnitTests.csproj     # SDK-style project (net8.0-windows)
    ├── NuGetPackageInstallerTests.cs            # Tests for NuGetPackageInstaller wizard
    ├── WizardInfoBarEventsTests.cs              # Tests for NuGetInfoBarUIEvents
    ├── ErrorMessageTests.cs                     # Tests for error message construction
    └── TestHelpers/
        ├── VsTestBase.cs                       # Base class: ThreadHelper + culture setup
        ├── MockServiceSetup.cs                 # Mock factory: IComponentModel, EnvDTE.Project, reflection helpers
        └── TemplateTestData.cs                 # NuGet package lists and TemplateInfo for all templates
```

## Architecture Notes

- **Shared source linking** — Unit tests compile the same shared wizard source files (`WizardImplementation.cs`, `WizardInfoBarEvents.cs`, `OutputWindowHelper.cs`) with the `CSHARP_EXTENSION` constant defined, matching the C# extension project.
- **VSPackage resources** — The C# extension's `VSPackage.resx` and `VSPackage.Designer.cs` are linked into the test project so that resource strings (e.g., `Resources._1044`) resolve at runtime.
- **ThreadHelper configuration** — `VsTestBase` creates a `JoinableTaskContext` with the test thread as the main thread and sets it on `ThreadHelper` via reflection so `ThrowIfNotOnUIThread()` passes.
- **StartInstallationAsync** — Called directly via reflection, bypassing the `JoinableTaskFactory.Run` wrapper in `ProjectFinishedGenerating` which requires a VS message pump.
- **Error paths** that call `SwitchToMainThreadAsync` are tested for invocation but not full error message display (requires a VS message pump).
- **MessageBox interception** — `NuGetPackageInstaller.ShowMessageBox` is a replaceable `Func<>` field, allowing tests to capture and verify MessageBox content without blocking UI.
