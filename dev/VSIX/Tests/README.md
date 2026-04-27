# VSIX Template Tests

Unit and integration tests for the Windows App SDK Visual Studio project templates.

## Prerequisites

### Unit Tests
- .NET Framework 4.7.2 developer pack
- No Visual Studio installation required

### Integration Tests
- Visual Studio 2022 (Enterprise, Professional, or Community)
- Windows App SDK VSIX installed in the VS experimental instance
- Set `VSIX_TEST_DEVENV_PATH` env var if VS is not in a standard location

## Running Tests

### Unit Tests (fast, no VS required)
```powershell
cd dev\VSIX\Tests
dotnet test WindowsAppSDK.VSIX.UnitTests --verbosity normal
```

### Integration Tests (slow, requires VS)
```powershell
cd dev\VSIX\Tests
dotnet test WindowsAppSDK.VSIX.IntegrationTests --filter "TestCategory=Integration" --verbosity normal
```

### All Tests
```powershell
cd dev\VSIX
dotnet test WindowsAppSDK.Extension.sln --verbosity normal
```

## Test Coverage

### Unit Tests (89 tests)
| Area | Tests | Description |
|------|-------|-------------|
| AddPackageReferences | 9 | SDK-style and legacy .csproj package reference insertion, null/error handling |
| BuildGuard | 31 | Build blocking/enabling lifecycle, Dispose, shell property changes, update solution callbacks |
| NuGetPackageInstaller | 18 | Package parsing, ProjectFinishedGenerating, StartInstallation, failure handling |
| NuGetRestoreDetection | 11 | Exception message matching for disabled NuGet restore scenarios |
| ErrorMessages | 8 | CreateErrorMessage (InfoBar/MessageBox), CreateDetailedErrorMessage formats |
| WizardInfoBarEvents | 9 | Hyperlink routing, null handling, unknown action context, constructor |
| ShouldAddProjectItem | 1 | Always returns true |
| Template Package Counts | 2 | Correct package count per template type |

### Integration Tests (11 tests)
| Template | Language | Scenario |
|----------|----------|----------|
| SingleProjectPackagedApp | C# | Instantiate → NuGet → Build → Verify .exe |
| ClassLibrary | C# | Instantiate → NuGet → Build → Verify .dll (PE check) |
| UnitTestApp | C# | Instantiate → NuGet → Build → Verify test .dll |
| PackagedApp | C# | Instantiate ProjectGroup → NuGet → Build → Verify .exe |
| SingleProjectPackagedApp | C++ | Instantiate → NuGet → Build → Verify .exe |
| UnitTestApp | C++ | Instantiate → NuGet → Build → Verify .dll |
| PackagedApp | C++ | Instantiate ProjectGroup → NuGet → Build → Verify .exe |
| RuntimeComponent | C++ | Instantiate → NuGet → Build → Verify .dll + .winmd |
| NuGet Failure (C#) | C# | Empty NuGet feed → Verify wizard error handling |
| NuGet Failure (C++) | C++ | Empty NuGet feed → Verify wizard error handling |

## Architecture Notes

- **Unit tests** compile the shared wizard source (`WizardImplementation.cs`, etc.) with `CSHARP_EXTENSION` defined
- **ThreadHelper** is configured via reflection to treat the test thread as the UI thread
- **StartInstallationAsync** is called directly via reflection, bypassing `JoinableTaskFactory.Run` which requires a VS message pump
- **Error paths** that call `SwitchToMainThreadAsync` are tested for invocation but not full error message display (requires VS message pump)
- **Integration tests** use `EnvDTE` COM automation with a controlled VS experimental instance
- **NuGet failure tests** use an isolated `NuGet.config` with `<clear />` and an empty local feed
