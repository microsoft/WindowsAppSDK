## Library design guide

- Custom XAML controls: derive from `Control` and ship `Themes/Generic.xaml` (`Default` / `Light` / `HighContrast` resource dictionaries). For composing existing controls, use `UserControl`.

External guides:

- [Dependency properties overview](https://learn.microsoft.com/windows/apps/develop/platform/dependency-properties-overview)
- [Microsoft.CodeAnalysis.PublicApiAnalyzers](https://github.com/dotnet/roslyn-analyzers/blob/main/src/PublicApiAnalyzers/PublicApiAnalyzers.Help.md) — lock the public API surface
- [Create a NuGet package with the dotnet CLI](https://learn.microsoft.com/nuget/create-packages/creating-a-package-dotnet-cli)
