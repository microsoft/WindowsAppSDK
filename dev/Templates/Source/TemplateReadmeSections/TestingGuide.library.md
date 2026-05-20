## Testing guide

For a class library, the API surface deserves dedicated tests — they
double as living documentation of how the types are meant to be used.

It is recommended to add a unit test project alongside the library
(`dotnet new winui-unittest -n MyLibrary.Tests`) and reference the
library from it with `dotnet add reference`. MSTest's standard
`[TestClass]` / `[TestMethod]` shape handles both pure types and types
that touch XAML (the unit-test template runs inside an MSIX, so
dependency-property and `INotifyPropertyChanged` plumbing works).

For per-task guidance:

- **Unit-testing the public API**:
  [MSTest framework](https://learn.microsoft.com/dotnet/core/testing/unit-testing-mstest-intro).
- **Mocking dependencies**: [Moq](https://github.com/devlooped/moq) or
  [NSubstitute](https://nsubstitute.github.io/) for any
  service-shaped abstractions the library consumes.
- **Compatibility checks**: when the library is shipped as a NuGet
  package, [Microsoft.DotNet.ApiCompat.Tool](https://www.nuget.org/packages/Microsoft.DotNet.ApiCompat.Tool)
  flags accidental API breaks between versions.
