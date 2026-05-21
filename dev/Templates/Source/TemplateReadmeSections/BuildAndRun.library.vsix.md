## Build

- Visual Studio: *Build → Build Solution* (`Ctrl+Shift+B`).
- Developer PowerShell: `msbuild /restore /p:Configuration=Debug /p:Platform=x64`.
- No Start-Debugging target: a class library has no entry point. Reference it from a WinUI 3 app or unit test project in the same solution.

For more, see [MSBuild command-line reference](https://learn.microsoft.com/visualstudio/msbuild/msbuild-command-line-reference).
