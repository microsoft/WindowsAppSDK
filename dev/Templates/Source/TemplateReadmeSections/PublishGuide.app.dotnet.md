## Publish guide

Producing a redistributable MSIX requires a `.wapproj` (Windows
Application Packaging Project) alongside this app project. The
`.wapproj` owns the `Package.appxmanifest`, signing, and bundle
configuration.

The [`winapp` CLI](https://github.com/microsoft/WinAppCli) provides a
CLI-friendly path for the same set of operations Visual Studio's
*Publish → Create App Packages* wizard performs:

```powershell
winapp publish --configuration Release --platforms x64,arm64
```

For the underlying mechanics (sideload vs. Store, certificate
selection, bundle layout, version policy), see
[Package and deploy a WinUI 3 desktop app](https://learn.microsoft.com/windows/apps/package-and-deploy/).
