## Build

Build the project from Visual Studio with *Build → Build Solution*
(`Ctrl+Shift+B`), or from a Developer PowerShell:

```powershell
msbuild /restore /p:Configuration=Debug /p:Platform=x64
```

There is no Start-Debugging target for a class library — it has no entry
point. To exercise it, reference it from a WinUI 3 desktop app project or
a WinUI 3 unit test project in the same solution.
