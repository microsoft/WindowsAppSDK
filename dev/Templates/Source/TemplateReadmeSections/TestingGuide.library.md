## Testing guide

- Companion test template: `dotnet new winui-unittest -n MyLibrary.Tests`, then `dotnet add reference ../MyLibrary/MyLibrary.csproj`.
- Tests run inside an MSIX, so dependency-property and `INotifyPropertyChanged` plumbing works in test cases.
- API-break detection: [Microsoft.DotNet.ApiCompat.Tool](https://www.nuget.org/packages/Microsoft.DotNet.ApiCompat.Tool).
- Mocking: [Moq](https://github.com/devlooped/moq), [NSubstitute](https://nsubstitute.github.io/).

See [Unit testing with MSTest](https://learn.microsoft.com/dotnet/core/testing/unit-testing-mstest-intro).
