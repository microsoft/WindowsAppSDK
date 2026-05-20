## Common next steps

- **Add a test class**: any `.cs` file with `[TestClass]` and
  `[TestMethod]` attributes is picked up by the MSTest runner.
- **Reference the code under test**:
  `dotnet add reference ../MyApp/MyApp.csproj` (or
  `dotnet add package <name>` for a NuGet'd library).
- **Update the SDK**: `dotnet add package Microsoft.WindowsAppSDK`.
