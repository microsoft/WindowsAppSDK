## Library design guide

- Default types to `internal`; promote to `public` only when needed — the public surface is a long-term commitment.
- Enable nullable reference types (`<Nullable>enable</Nullable>`); treat public-API warnings as errors with [Microsoft.CodeAnalysis.PublicApiAnalyzers](https://github.com/dotnet/roslyn-analyzers/blob/main/src/PublicApiAnalyzers/PublicApiAnalyzers.Help.md).
- Custom XAML controls: derive from `Control` and ship `Themes/Generic.xaml` with `Default` / `Light` / `HighContrast` resource dictionaries. For composing existing controls, prefer `UserControl`.
- For dependency properties and events, see [Dependency properties overview](https://learn.microsoft.com/windows/apps/develop/platform/dependency-properties-overview).

For distribution, see [Create a NuGet package with the dotnet CLI](https://learn.microsoft.com/nuget/create-packages/creating-a-package-dotnet-cli).
