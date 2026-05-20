## Common next steps

- **Edit the manifest**: open `Package.appxmanifest` in the
  manifest designer (or as XML) to adjust capabilities, display
  name, logos, file-type associations, and protocol activation.
- **Add a project to the package**: right-click the `.wapproj` →
  *Add → Reference* and tick the projects you want included in the
  MSIX.
- **Add a WinUI item to the app project** (not the `.wapproj`):
  *Add → New Item → WinUI* gives you pages, windows, user controls,
  templated controls, content dialogs, resource dictionaries, and
  `.resw` files.
- **Update the SDK**: open *Manage NuGet Packages* on the app project,
  switch to the *Updates* tab, and update
  **Microsoft.WindowsAppSDK**.
