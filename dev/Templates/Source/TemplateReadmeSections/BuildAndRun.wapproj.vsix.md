## Build and run

- VS: **F5** with the `.wapproj` set as the startup project (builds both projects, deploys loose-layout MSIX, launches via AUMID).
- CLI: `msbuild MyApp.Package\MyApp.Package.wapproj /restore /p:Platform=x64 /p:Configuration=Debug`.
- `dotnet run` does **not** work on `.wapproj`. For a CLI-driven flow, switch to the single-project blank-app template.

See [MSBuild properties for packaging projects](https://learn.microsoft.com/windows/msix/desktop/desktop-to-uwp-packaging-dot-net#build-the-package-from-the-command-line) for `.wapproj` flags.
