## Publish guide

This two-project shape **is** the redistributable-MSIX shape — the
`.wapproj` already owns `Package.appxmanifest`, signing, and bundle
configuration.

In Visual Studio, right-click the `.wapproj` → *Publish → Create App
Packages*, and follow the wizard to pick sideload vs. Store,
certificate, target platforms, and bundle layout.

For the underlying mechanics (sideload vs. Store, certificate selection,
bundle layout, version policy), see
[Package and deploy a WinUI 3 desktop app](https://learn.microsoft.com/windows/apps/package-and-deploy/).
