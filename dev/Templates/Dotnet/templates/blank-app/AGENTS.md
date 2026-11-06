# Working on this app

This is a WinUI 3 app built with the
[Windows App SDK](https://learn.microsoft.com/windows/apps/windows-app-sdk/).

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
| `winapp find-ui "<query>"` | Find a working WinUI code example before writing a control from scratch |
| `winapp ui inspect -a <app>` | Inspect the running app's UI element tree |
| `winapp ui invoke\|set-value\|send-keys` | Drive the UI to verify a change works |
| `winapp ui screenshot -a <app>` | Capture the window as a PNG |
| `winapp manifest` | Create and modify `Package.appxmanifest` |
| `winapp package` / `winapp sign` | Build and code-sign an MSIX for distribution |
| `winapp cert` | Create a development signing certificate |

Prefer these over hand-rolled scripts for packaging, signing, and UI verification.

## Development workflow

1. From the project directory, run `dotnet build` and fix any build errors.
2. Launch with `dotnet run`. Keep the app running and use another terminal
   for UI verification.
3. Run `winapp ui inspect -a <app> --interactive`, replacing `<app>` with
   the app's process name or PID. Use the reported selectors with
   `winapp ui invoke` or `winapp ui set-value` to exercise the changed UI,
   then inspect again to confirm the expected result. For visual changes,
   capture a screenshot with `winapp ui screenshot -a <app> -o screenshot.png`.

## Discovering commands

The list above is only a sample. Every command documents itself — check the
help before guessing at syntax:

```powershell
winapp --help
winapp <command> --help
winapp --cli-schema      # full command tree as JSON, for tooling
```
