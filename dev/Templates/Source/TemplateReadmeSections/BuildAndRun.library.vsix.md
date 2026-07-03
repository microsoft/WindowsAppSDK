## Build

- VS: *Build → Build Solution* (`Ctrl+Shift+B`).
- CLI: `msbuild /restore /p:Configuration=Debug /p:Platform=x64`.
- No Start-Debugging target: class libraries have no entry point. Reference from an app or unit-test project in the same solution.

See [MSBuild command-line reference](https://learn.microsoft.com/visualstudio/msbuild/msbuild-command-line-reference).
