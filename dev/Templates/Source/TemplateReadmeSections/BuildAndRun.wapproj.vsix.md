## Build and run

- Visual Studio: press **F5** with the `.wapproj` set as the startup project. VS builds both projects, deploys the loose-layout MSIX, and launches via AUMID activation.
- Developer PowerShell: `msbuild MyApp.Package\MyApp.Package.wapproj /restore /p:Platform=x64 /p:Configuration=Debug`.
- `dotnet run` does **not** work on `.wapproj`. For a CLI-driven flow, use the single-project blank app template instead.

For `.wapproj` flags (`AppxPackageDir`, `UapAppxPackageBuildMode`, `AppxBundlePlatforms`, …), see [MSBuild properties for packaging projects](https://learn.microsoft.com/windows/msix/desktop/desktop-to-uwp-packaging-dot-net#build-the-package-from-the-command-line).
