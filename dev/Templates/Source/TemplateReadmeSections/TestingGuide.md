## Testing guide

For testing, the cheapest path is to keep view-model and service logic
free of `Microsoft.UI.Xaml.*` references so it can be exercised by a
plain `dotnet new winui-unittest` project — no UI thread needed.

It is recommended to add the unit test project alongside the app early
(`dotnet new winui-unittest -n MyApp.Tests`) and reference the app
project from it with `dotnet add reference`. View models, converters,
and services can then be tested with MSTest's standard `[TestClass]` /
`[TestMethod]` shape.

For per-task guidance:

- **Unit-testing view models and services**:
  [MSTest framework](https://learn.microsoft.com/dotnet/core/testing/unit-testing-mstest-intro).
- **Mocking services**: [Moq](https://github.com/devlooped/moq) or
  [NSubstitute](https://nsubstitute.github.io/) work well for
  interface-based services injected via DI.
- **UI automation and end-to-end testing**:
  [WinAppDriver](https://github.com/microsoft/WinAppDriver) drives a
  running MSIX through UI Automation; well suited for smoke tests of
  navigation, focus, and dialog flows that can't be reached from a unit
  test.
