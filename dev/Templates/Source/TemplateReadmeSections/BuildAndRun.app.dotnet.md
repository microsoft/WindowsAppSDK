## Build and run

- `dotnet build` — compile.
- `dotnet run` — registers a loose-layout MSIX, gives the app package identity, and launches via AUMID activation. No `Add-AppxPackage` / `MakeAppx` / `SignTool` step needed.
- If the loose-layout registration drifts after editing `Package.appxmanifest` (symptom: `REGDB_E_CLASSNOTREG`), run `winapp unregister` then `dotnet run`.

For the full set of `WinAppRun*` MSBuild properties, see [`Microsoft.Windows.SDK.BuildTools.WinApp`](https://www.nuget.org/packages/Microsoft.Windows.SDK.BuildTools.WinApp).
