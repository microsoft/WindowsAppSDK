## Build and run

- `dotnet build` — compile.
- `dotnet run` — registers a loose-layout MSIX with AUMID activation and launches. No `Add-AppxPackage` / `MakeAppx` / `SignTool` needed.
- If you hit `REGDB_E_CLASSNOTREG` after editing `Package.appxmanifest`: `winapp unregister`, then `dotnet run`.

See [`Microsoft.Windows.SDK.BuildTools.WinApp`](https://www.nuget.org/packages/Microsoft.Windows.SDK.BuildTools.WinApp) for `WinAppRun*` MSBuild properties.
