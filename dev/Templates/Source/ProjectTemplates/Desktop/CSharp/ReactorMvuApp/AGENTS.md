# Working on this app

This is a WinUI 3 app built with
[Microsoft.UI.Reactor](https://github.com/microsoft/microsoft-ui-reactor) and the
[Windows App SDK](https://learn.microsoft.com/windows/apps/windows-app-sdk/).
The UI is declared in **pure C# — there is no XAML in this project**, so don't
add `.xaml` files or convert components to XAML.

## Use the WinApp CLI

The [WinApp CLI](https://github.com/microsoft/WinAppCli) handles the
Windows-specific parts of app development. Install it with:

```powershell
winget install Microsoft.winappcli --source winget
```

A sample of the commands it provides:

| Command | Use it to |
|---------|-----------|
| `winapp run` | Build and launch the app with full MSIX package identity |
| `winapp find-ui "<query>" --source reactor` | Find a working Reactor code example before writing a component from scratch |
| `winapp ui inspect -a <app>` | Inspect the running app's UI element tree |
| `winapp ui invoke\|set-value\|send-keys` | Drive the UI to verify a change works |
| `winapp ui screenshot -a <app>` | Capture the window as a PNG |
| `winapp manifest` | Create and modify `Package.appxmanifest` |
| `winapp package` / `winapp sign` | Build and code-sign an MSIX for distribution |
| `winapp cert` | Create a development signing certificate |

Prefer these over hand-rolled scripts for packaging, signing, and UI verification.

## Discovering commands

The list above is only a sample. Every command documents itself — check the
help before guessing at syntax:

```powershell
winapp --help
winapp <command> --help
winapp --cli-schema      # full command tree as JSON, for tooling
```
