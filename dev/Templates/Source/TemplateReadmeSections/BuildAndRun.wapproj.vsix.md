## Build and run

The recommended flow is **F5 in Visual Studio** with the `.wapproj` set
as the startup project. Visual Studio builds both projects, deploys the
loose-layout MSIX, and launches the app via AUMID activation.

From a Developer PowerShell or Developer Command Prompt, build the
`.wapproj` to produce the MSIX:

```powershell
msbuild MyApp.Package\MyApp.Package.wapproj /restore /p:Platform=x64 /p:Configuration=Debug
```

`dotnet run` is **not** the right entry point for the two-project shape —
`dotnet` does not understand `.wapproj`. If you want a CLI-driven
`dotnet run` experience, use the single-project blank app template
(*Add → New Project → WinUI 3 Desktop App*) instead.

For more on `.wapproj` flags (`AppxPackageDir`, `UapAppxPackageBuildMode`,
`AppxBundlePlatforms`, etc.), see
[MSBuild properties for packaging projects](https://learn.microsoft.com/windows/msix/desktop/desktop-to-uwp-packaging-dot-net#build-the-package-from-the-command-line).
