## Build and run tests

- Visual Studio: *Test → Test Explorer → Run All Tests*, or right-click a test in the editor → *Run Tests*.
- Developer PowerShell: `dotnet test`.
- Subset from CLI: `dotnet test --filter "FullyQualifiedName~MyTestClass"` or `dotnet test --filter "TestCategory=Smoke"`.

For the full filter syntax, see [Filter MSTest tests](https://learn.microsoft.com/dotnet/core/testing/selective-unit-tests).
