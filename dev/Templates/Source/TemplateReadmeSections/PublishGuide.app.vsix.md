## Publish guide

A redistributable MSIX requires a `.wapproj` alongside this app project (it owns `Package.appxmanifest`, signing, and bundle config).

- *Add → New Project → Windows Application Packaging Project*, then *Add → Reference* this app project.
- Right-click `.wapproj` → *Publish → Create App Packages*.

See [Package and deploy a WinUI 3 desktop app](https://learn.microsoft.com/windows/apps/package-and-deploy/).
