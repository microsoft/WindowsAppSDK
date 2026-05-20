## Publish guide

Producing a redistributable MSIX requires a `.wapproj` (Windows
Application Packaging Project) alongside this app project. The
`.wapproj` owns the `Package.appxmanifest`, signing, and bundle
configuration.

In Visual Studio:

1. *Add → New Project → Windows Application Packaging Project*.
2. In the `.wapproj`, *Add → Reference* and tick this app project.
3. Right-click the `.wapproj` → *Publish → Create App Packages*, and
   follow the wizard to pick sideload vs. Store, certificate, target
   platforms, and bundle layout.

For the underlying mechanics, see
[Package and deploy a WinUI 3 desktop app](https://learn.microsoft.com/windows/apps/package-and-deploy/).
