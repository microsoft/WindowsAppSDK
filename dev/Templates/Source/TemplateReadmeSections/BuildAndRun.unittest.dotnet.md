## Build and run tests

- `dotnet test` — builds the test container, registers it as a loose-layout MSIX, runs MSTest.
- Filter: `dotnet test --filter "FullyQualifiedName~MyTestClass"` or `... "TestCategory=Smoke"`.

See [Filter MSTest tests](https://learn.microsoft.com/dotnet/core/testing/selective-unit-tests).
