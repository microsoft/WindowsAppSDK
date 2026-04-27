# Windows App SDK Visual Studio Extensions

This directory contains the Visual Studio extensions (VSIX) for Windows App SDK, including project templates, item templates, and project wizards for creating WinUI 3 applications.

## Structure

```
dev/VSIX/
├── Extension/          # VSIX extension packages
│   ├── Cs/            # C# extension
│   └── Cpp/           # C++ extension
├── ProjectTemplates/  # Visual Studio project templates
│   ├── Desktop/       # Desktop app templates (C#, C++)
│   └── Neutral/       # Platform-neutral templates
├── ItemTemplates/     # Visual Studio item templates
│   ├── Desktop/       # Desktop-specific items
│   └── Neutral/       # Platform-neutral items
├── Shared/            # Shared code used by wizards and extensions
│   ├── WizardImplementation.cs  # Main wizard logic
│   ├── WizardInfoBarEvents.cs   # InfoBar event handlers
│   └── OutputWindowHelper.cs    # Output window utilities
└── Tests/             # Unit tests for VSIX components
    └── WindowsAppSDK.VSIX.UnitTests/
```

## Testing

### Unit Tests

The `Tests/WindowsAppSDK.VSIX.UnitTests` project contains comprehensive unit tests for the VSIX wizard and UI components.

#### Test Categories

1. **WizardInfoBarEventsTests** - Tests for InfoBar hyperlink handling
   - Null parameter handling and defensive programming
   - Action context routing (ManageNuGetPackages, SeeErrorDetails)
   - VS service integration (DTE commands, Output window)

2. **Other test files** - (Add as implemented)

#### Running Tests

```powershell
# Run all tests
dotnet test Tests\WindowsAppSDK.VSIX.UnitTests\WindowsAppSDK.VSIX.UnitTests.csproj

# Run specific test class
dotnet test --filter "FullyQualifiedName~WizardInfoBarEventsTests"
```

### Test Infrastructure

The tests use:
- **MSTest** - Test framework
- **Moq** - Mocking framework for VS interfaces
- **VsTestBase** - Base class that configures ThreadHelper for UI thread simulation

Key helper classes:
- `VsTestBase` - Configures test environment for VS SDK types
- `MockServiceSetup` - Creates mock VS services and projects

### Testing VS Integration

Due to the complexity of mocking `ServiceProvider.GlobalProvider`, integration tests verify:
- **Code path correctness** - Ensures the right methods are called based on action contexts
- **Defensive error handling** - Validates graceful handling of null services
- **Command documentation** - Documents expected DTE command GUIDs and IDs

For full verification of VS service calls, consider:
1. Integration tests with real VS services (requires VS test host)
2. Dependency injection refactoring to make VS services mockable

## Building

The VSIX extensions are built as part of the main Windows App SDK solution:

```powershell
# Build from repository root
.\BuildAll.ps1
```

## Key Components

### Wizard Implementation

`Shared/WizardImplementation.cs` implements the VS project wizard that:
- Detects project type (C# vs C++)
- Installs required NuGet packages
- Displays InfoBars for errors with actionable hyperlinks

### InfoBar Events

`Shared/WizardInfoBarEvents.cs` handles user interactions with InfoBar hyperlinks:
- **ManageNuGetPackages** - Opens NuGet Package Manager
  - Command: `{25fd982b-8cae-4cbd-a440-e03ffccde106}`, ID: `0x100`
  - Reference: [Invoke Manage NuGet Packages Dialog Programmatically](https://devblogs.microsoft.com/dotnet/invoke-manage-nuget-packages-dialog-programmatically/)
- **SeeErrorDetails** - Shows detailed error information in Output window

### Output Window Helper

`Shared/OutputWindowHelper.cs` provides utilities for writing messages to the VS Output window with proper pane activation and formatting.

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
