## Testing guide

- Keep view-model and service logic free of `Microsoft.UI.Xaml.*` references so it runs without a UI thread.
- Add a unit test project alongside the app: `dotnet new winui-unittest -n MyApp.Tests`, then `dotnet add reference` the app project.
- Mock services with [Moq](https://github.com/devlooped/moq) or [NSubstitute](https://nsubstitute.github.io/).
- For end-to-end UI tests, drive the running MSIX with [WinAppDriver](https://github.com/microsoft/WinAppDriver).

For more, see [Unit testing with MSTest](https://learn.microsoft.com/dotnet/core/testing/unit-testing-mstest-intro).
