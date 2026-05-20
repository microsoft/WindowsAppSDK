## Build and run

```powershell
dotnet build
dotnet run
```

`dotnet run` is the equivalent of F5 in Visual Studio: it registers a
loose-layout MSIX, gives the app package identity, and launches it via
AUMID activation. No `Add-AppxPackage`, `MakeAppx`, or `SignTool` step is
needed.

The packaged-launch integration comes from
[`Microsoft.Windows.SDK.BuildTools.WinApp`](https://www.nuget.org/packages/Microsoft.Windows.SDK.BuildTools.WinApp).
See its package page for the full set of `WinAppRun*` MSBuild properties
(opt-out, console alias, no-launch, debug output, launch args).

If the loose-layout registration drifts after editing
`Package.appxmanifest` (a common symptom is `REGDB_E_CLASSNOTREG` at
startup), running `winapp unregister` followed by `dotnet run` refreshes
it.
