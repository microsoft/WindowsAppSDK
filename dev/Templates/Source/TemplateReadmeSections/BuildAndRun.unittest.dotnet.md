## Build and run tests

- `dotnet test` — builds the test container, registers it as a loose-layout MSIX, runs MSTest, reports results to the CLI.
- Subset by name: `dotnet test --filter "FullyQualifiedName~MyTestClass"`.
- Subset by trait: decorate with `[TestCategory("Smoke")]`, run `dotnet test --filter "TestCategory=Smoke"`.
- Verbose: `dotnet test -v normal` (or `detailed`).

For the full filter syntax, see [Filter MSTest tests](https://learn.microsoft.com/dotnet/core/testing/selective-unit-tests).
