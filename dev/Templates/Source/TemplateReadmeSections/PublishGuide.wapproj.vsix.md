## Publish guide

This two-project shape **is** the redistributable-MSIX shape — the `.wapproj` already owns `Package.appxmanifest`, signing, and bundle config.

- Right-click `.wapproj` → *Publish → Create App Packages*, follow the wizard (sideload vs. Store, certificate, target platforms, bundle layout).

For more, see [Package and deploy a WinUI 3 desktop app](https://learn.microsoft.com/windows/apps/package-and-deploy/).
