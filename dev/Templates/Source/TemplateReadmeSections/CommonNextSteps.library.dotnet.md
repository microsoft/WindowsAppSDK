## Common next steps

- **Add an item**: `dotnet new winui-usercontrol`,
  `winui-templatedcontrol`, `winui-resourcedictionary`, or
  `winui-resw`. `dotnet new list winui` shows every available
  template.
- **Consume the library**: from another WinUI 3 project,
  `dotnet add reference ../path/to/this.csproj` (or `dotnet pack` and
  reference the produced `.nupkg`).
- **Update the SDK**: `dotnet add package Microsoft.WindowsAppSDK`.
