## Common next steps

- **Add a test class**: any `.cs` file with `[TestClass]` and `[TestMethod]` is picked up by the MSTest runner.
- **Reference the code under test**: `dotnet add reference ../MyApp/MyApp.csproj`, or `dotnet add package <name>` for a NuGet library.
- **Update the SDK**: `dotnet add package Microsoft.WindowsAppSDK`.

For more, see [Unit testing with MSTest](https://learn.microsoft.com/dotnet/core/testing/unit-testing-mstest-intro).
