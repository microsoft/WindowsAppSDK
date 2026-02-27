# Getting Started with Windows App SDK in Visual Studio Code

This guide covers how to create and build Windows App SDK projects using
Visual Studio Code (or VS Code-based editors like Cursor) instead of
Visual Studio.

## Prerequisites

1. **Windows 10 version 1809 or later** (build 17763+)
2. **Visual Studio Build Tools 2022** (or full Visual Studio 2022)
   - Even when using VS Code as your editor, you need the MSVC build tools
     and Windows SDK installed. Install them from
     [Visual Studio Downloads](https://visualstudio.microsoft.com/downloads/)
     under "Tools for Visual Studio" > "Build Tools for Visual Studio 2022".
   - In the installer, select:
     - "Desktop development with C++" workload (for C++ projects)
     - ".NET desktop development" workload (for C# projects)
     - Windows 10/11 SDK
3. **Visual Studio Code** with recommended extensions:
   - [C# Dev Kit](https://marketplace.visualstudio.com/items?itemName=ms-dotnettools.csdevkit) (for C# projects)
   - [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools) (for C++ projects)

## Creating a C# WinUI 3 Project

### Using the command line

```bash
# Install the WinUI 3 project templates
dotnet new install Microsoft.WindowsAppSDK.Templates

# Create a new WinUI 3 project
dotnet new winui3 -n MyApp
cd MyApp
```

### Adding the Windows App SDK NuGet package manually

If you are starting from an existing project:

```bash
dotnet add package Microsoft.WindowsAppSDK
dotnet add package Microsoft.Windows.SDK.BuildTools
```

### Building and running

```bash
# Restore dependencies
dotnet restore

# Build the project
dotnet build

# Run the application
dotnet run
```

Or use VS Code's integrated terminal and the C# Dev Kit's build/debug support.

## Creating a C++ WinUI 3 Project

C++ WinUI 3 projects use MSBuild `.vcxproj` files. You can create them via
the Visual Studio Build Tools command line and edit in VS Code:

```bash
# Build using MSBuild from Developer Command Prompt
msbuild MyApp.vcxproj /p:Configuration=Release /p:Platform=x64
```

To get IntelliSense working in VS Code, configure your `c_cpp_properties.json`
to include the Windows SDK and WinAppSDK NuGet package paths.

## Working with Electron + Windows App SDK

If you are using Electron and want to access Windows App SDK APIs:

1. Use a **native Node.js addon** (N-API/node-addon-api) that links against
   the Windows App SDK libraries.
2. Add the Windows App SDK NuGet package to your native addon's build
   configuration.
3. Call WinRT APIs from the native addon using C++/WinRT.

Example `binding.gyp` snippet for node-gyp:

```json
{
  "targets": [{
    "target_name": "winrt_bridge",
    "sources": ["src/bridge.cpp"],
    "include_dirs": [
      "<path-to-cppwinrt-headers>",
      "<path-to-windowsappsdk-headers>"
    ],
    "libraries": [
      "WindowsApp.lib"
    ]
  }]
}
```

## Debugging in VS Code

### C# Projects

The C# Dev Kit extension provides built-in debugging. Add a `launch.json`:

```json
{
  "version": "0.2.0",
  "configurations": [
    {
      "name": "Launch WinUI App",
      "type": "coreclr",
      "request": "launch",
      "program": "${workspaceFolder}/bin/Debug/net8.0-windows10.0.19041.0/MyApp.exe",
      "cwd": "${workspaceFolder}"
    }
  ]
}
```

### C++ Projects

Use the C/C++ extension's debugger with a `launch.json` targeting your built
executable.

## Known Limitations

- **XAML Designer**: The visual XAML designer is only available in Visual Studio.
  When using VS Code, you edit XAML files as text.
- **XAML Hot Reload**: Not available in VS Code. You must rebuild to see
  XAML changes.
- **Project Templates**: Limited template support compared to Visual Studio's
  template wizard.
- **Package Identity**: Creating MSIX packages is easier through Visual Studio
  or the command-line `makeappx` tool. VS Code does not have integrated MSIX
  packaging support.
