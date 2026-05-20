## Library design guide

For a class library, the API surface *is* the product — every public
type and member is a long-term commitment. Treating internal types as
the default and promoting them to public only when needed keeps that
surface small and intentional.

It is recommended to enable nullable reference types (`<Nullable>enable</Nullable>`),
turn warnings into errors for public-API issues, and run an analyzer like
[Microsoft.CodeAnalysis.PublicApiAnalyzers](https://github.com/dotnet/roslyn-analyzers/blob/main/src/PublicApiAnalyzers/PublicApiAnalyzers.Help.md)
so unintentional surface changes show up at compile time rather than at
the next consumer upgrade.

For per-task guidance:

- **Custom XAML controls**: derive from `Control` and ship a default
  `Themes/Generic.xaml` —
  [Custom controls](https://learn.microsoft.com/windows/apps/design/controls/custom-controls).
  For composing existing controls, prefer `UserControl`.
- **Dependency properties and events**:
  [Dependency properties overview](https://learn.microsoft.com/windows/apps/develop/platform/dependency-properties-overview).
- **Theme and high-contrast resources**: ship
  `Themes/Generic.xaml` with `Default`, `Light`, and `HighContrast`
  resource dictionaries so consumers get correct theming for free.
- **Distribution**:
  [Create a NuGet package with the dotnet CLI](https://learn.microsoft.com/nuget/create-packages/creating-a-package-dotnet-cli)
  (covers `dotnet pack`, `PackageId`, `PackageVersion`,
  `PackageReleaseNotes`, and `dotnet nuget push`).
