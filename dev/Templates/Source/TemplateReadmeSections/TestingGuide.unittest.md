## Writing tests guide

- Reference code under test: `dotnet add reference ..\MyApp\MyApp.csproj` (or `dotnet add package <library>`). For internal types, add `[assembly: InternalsVisibleTo("MyApp.Tests")]`.
- Mocking: [Moq](https://github.com/devlooped/moq), [NSubstitute](https://nsubstitute.github.io/).

See [Unit testing with MSTest](https://learn.microsoft.com/dotnet/core/testing/unit-testing-mstest-intro) for `[TestMethod]`, `[DataTestMethod]`, `[TestInitialize]`, etc.
