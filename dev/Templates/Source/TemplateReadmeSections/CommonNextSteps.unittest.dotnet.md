## Common next steps

- Add a test class: any `.cs` with `[TestClass]` / `[TestMethod]` is discovered by MSTest.
- Reference code under test: `dotnet add reference ../MyApp/MyApp.csproj` (or `dotnet add package <library>`).
- Update SDK: `dotnet add package Microsoft.WindowsAppSDK`.

See [Unit testing with MSTest](https://learn.microsoft.com/dotnet/core/testing/unit-testing-mstest-intro).
