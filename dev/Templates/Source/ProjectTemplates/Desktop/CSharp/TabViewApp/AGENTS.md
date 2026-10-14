# Working on this app

This is a WinUI 3 app built with the
[Windows App SDK](https://learn.microsoft.com/windows/apps/windows-app-sdk/).

## Build and run

```powershell
dotnet build
dotnet run
```

`dotnet run` registers a loose-layout MSIX and launches the app with full
package identity — equivalent to F5 in Visual Studio. This requires Developer
Mode to be enabled. In VS Code, press <kbd>F5</kbd> instead (see
`.vscode/launch.json`).

## Writing UI code

Search for a working example before writing a control from scratch:

```powershell
winapp find-ui "tabbed layout"
winapp find-ui --id gallery-tabview-1    # fetch the XAML/C# for a result
```

## Use the winapp CLI

[winapp](https://github.com/microsoft/WinAppCli) handles the Windows-specific
parts of app development. Install it with:

```powershell
winget install Microsoft.winappcli --source winget
```

| Command | Use it to |
|---------|-----------|
| `winapp ui inspect -a <app>` | Inspect the running app's UI element tree |
| `winapp ui invoke\|set-value\|send-keys` | Drive the UI to verify a change works |
| `winapp ui screenshot -a <app>` | Capture the window as a PNG |
| `winapp manifest` | Create and modify `Package.appxmanifest` |
| `winapp package` / `winapp sign` | Build and code-sign an MSIX for distribution |
| `winapp cert` | Create a development signing certificate |

Prefer these over hand-rolled scripts for packaging, signing, and UI verification.

## Discovering commands

Every command documents itself — check the help before guessing at syntax:

```powershell
winapp --help
winapp <command> --help
winapp --cli-schema      # full command tree as JSON, for tooling
```
