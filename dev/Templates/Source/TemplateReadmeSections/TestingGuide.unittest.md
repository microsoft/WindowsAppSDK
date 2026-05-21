## Writing tests guide

Tests are MSTest classes — any `.cs` file with `[TestClass]` and `[TestMethod]` is discovered automatically.

- Reference code under test: `dotnet add reference ..\MyApp\MyApp.csproj` (or `dotnet add package MyLibrary`). Types under test must be `public`, or add `[assembly: InternalsVisibleTo("MyApp.Tests")]`.
- Async tests: `[TestMethod] public async Task ...`
- Data-driven: `[DataTestMethod]` + `[DataRow(...)]`
- Setup / teardown: `[TestInitialize]` / `[TestCleanup]` (per test), `[ClassInitialize]` / `[ClassCleanup]` (per class).
- Mock dependencies with [Moq](https://github.com/devlooped/moq) or [NSubstitute](https://nsubstitute.github.io/).

For the full reference, see [Unit testing with MSTest](https://learn.microsoft.com/dotnet/core/testing/unit-testing-mstest-intro).
