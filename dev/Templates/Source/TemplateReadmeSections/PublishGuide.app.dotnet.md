## Publish guide

- A redistributable MSIX requires a `.wapproj` alongside this app project. The `.wapproj` owns `Package.appxmanifest`, signing, and bundle config.
- CLI flow: `winapp publish --configuration Release --platforms x64,arm64` (see [`winapp` CLI](https://github.com/microsoft/WinAppCli)).

For sideload vs. Store, certificate selection, bundle layout, and version policy, see [Package and deploy a WinUI 3 desktop app](https://learn.microsoft.com/windows/apps/package-and-deploy/).
