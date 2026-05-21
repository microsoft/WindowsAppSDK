## Publish guide

A redistributable MSIX requires a `.wapproj` alongside this app project. The `.wapproj` owns `Package.appxmanifest`, signing, and bundle config.

1. *Add → New Project → Windows Application Packaging Project*.
2. In the `.wapproj`, *Add → Reference* and tick this app project.
3. Right-click `.wapproj` → *Publish → Create App Packages*, follow the wizard.

For more, see [Package and deploy a WinUI 3 desktop app](https://learn.microsoft.com/windows/apps/package-and-deploy/).
