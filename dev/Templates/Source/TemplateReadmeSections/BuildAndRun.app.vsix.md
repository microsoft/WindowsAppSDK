## Build and run

Press **F5** in Visual Studio (or *Debug → Start Debugging*) to build,
deploy a loose-layout MSIX, and launch the app via AUMID activation —
no `Add-AppxPackage`, `MakeAppx`, or `SignTool` step is needed.

From a Developer PowerShell or Developer Command Prompt:

```powershell
msbuild /restore /p:Configuration=Debug /p:Platform=x64
```

For the full set of MSBuild properties controlling packaging
(`AppxPackageDir`, `UapAppxPackageBuildMode`, `AppxBundlePlatforms`,
etc.), see
[MSBuild properties for packaging projects](https://learn.microsoft.com/windows/msix/desktop/desktop-to-uwp-packaging-dot-net#build-the-package-from-the-command-line).
