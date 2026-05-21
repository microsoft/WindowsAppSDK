## Testing guide

- Add a unit test project alongside: `dotnet new winui-unittest -n MyLibrary.Tests`.
- Reference the library: `dotnet add reference ../MyLibrary/MyLibrary.csproj`.
- MSTest's `[TestClass]` / `[TestMethod]` handles both pure types and types that touch XAML (tests run inside an MSIX, so dependency-property and `INotifyPropertyChanged` plumbing works).
- Mock dependencies with [Moq](https://github.com/devlooped/moq) or [NSubstitute](https://nsubstitute.github.io/).
- For NuGet-shipped libraries, catch accidental API breaks with [Microsoft.DotNet.ApiCompat.Tool](https://www.nuget.org/packages/Microsoft.DotNet.ApiCompat.Tool).

For more, see [Unit testing with MSTest](https://learn.microsoft.com/dotnet/core/testing/unit-testing-mstest-intro).
