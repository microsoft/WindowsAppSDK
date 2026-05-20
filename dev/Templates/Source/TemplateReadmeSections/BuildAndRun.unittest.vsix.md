## Build and run tests

Open **Test Explorer** (*Test → Test Explorer*) and click *Run All Tests*,
or right-click a test in the editor and choose *Run Tests*. Visual Studio
builds the test container, deploys it as a loose-layout MSIX, runs MSTest
inside it, and reports results in Test Explorer.

From a Developer PowerShell:

```powershell
dotnet test
```

### Running a subset

- **In Test Explorer**: filter by class name, category, or outcome.
- **From the CLI**: `dotnet test --filter "FullyQualifiedName~MyTestClass"`
  or `dotnet test --filter "TestCategory=Smoke"`.

See [Filter MSTest tests](https://learn.microsoft.com/dotnet/core/testing/selective-unit-tests)
for the full filter syntax.
