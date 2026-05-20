## Build and run tests

```powershell
dotnet test
```

`dotnet test` builds the test container, registers it as a loose-layout
MSIX, runs the MSTest runner inside it, and reports results back to the
CLI — the same flow as Test Explorer in Visual Studio, but headless.

The packaged-launch integration comes from
[`Microsoft.Windows.SDK.BuildTools.WinApp`](https://www.nuget.org/packages/Microsoft.Windows.SDK.BuildTools.WinApp).

### Running a subset

- **By name**: `dotnet test --filter "FullyQualifiedName~MyTestClass"`
- **By trait**: decorate tests with `[TestCategory("Smoke")]` and run
  `dotnet test --filter "TestCategory=Smoke"`
- **Verbose output**: `dotnet test -v normal` (or `-v detailed`).

See [Filter MSTest tests](https://learn.microsoft.com/dotnet/core/testing/selective-unit-tests)
for the full filter syntax.
