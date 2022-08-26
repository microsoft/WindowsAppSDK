# Getting Started

# Tooling Prerequisites

Development requires the following installed tools...

1. Windows 10 SDK 10.0.17763.0 (RS5)
   a. Browse to https://go.microsoft.com/fwlink/p/?LinkID=2033908
   b. Save the offered download `winsdksetup.exe`
   c. Run winsdksetup.exe

**NOTE:** Visual Studio 2022 doesn't include this SDK but will use it if installed on the machine.

2. Visual Studio 2022 with...
   a. Workloads
      * .NET desktop development
      * Desktop development with C++
      * Universal Windows Platform development
   b. Individual components
      * .NET 6.0 Runtime (LTS)
      * .NET SDK
      * Git for Windows
      * ??? GitHub extension for Visual Studio
      * NuGet package manager
      * NuGet targets and build tasks
      * C# and Visual Basic Roslyn compilers
      * C++ Universal Windows Platform support for v143 build tools (ARM64)
      * MSBuild
      * MSVC v143 - VS 2022 C++ ARM64 build tools (Latest)
      * MSVC v143 - VS 2022 C++ x64/x86 build tools (Latest)
      * Windows Universal CRT SDK
      * .NET profiling tools
      * C++ profiling tools
      * C# and Visual Basic
      * C++ core features
      * C++/WinRT
      * Visual Studio SDK
      * Windows 10 SDK (10.0.17763.0)
      * Windows 10 SDK (10.0.18362.0)
      * Windows 10 SDK (10.0.19041.0)
      * Windows 10 SDK (10.0.20348.0)
      * Windows 10 SDK (10.0.22000.0)
      * Windows 10 SDK (10.0.22621.0)
      * Windows Universal C Runtime

**NOTE:** You can tell the Visual Studio Installer to do the heavy lifting for you
via `More` / `Import configuration` and select `docs\Coding-Guidelines\VisualStudio2022.vsconfig`.

3. Run NuGet Restore
   a. Download nuget.exe version >= 6.2.1 from https://www.nuget.org/downloads
      e.g. https://dist.nuget.org/win-x86-commandline/v6.2.1/nuget.exe
   b. Open a command prompt
   c. CD to the project root e.g. `cd c:\source\repos\windowsappsdk`
   d. Run `nuget.exe restore`

# One-Time Setup

Run the `tools\DevCheck.cmd` from an elevated command prompt (e.g. right-click on "Command Prompt"
in the Start Menu and select `Run as Administrator`) to update your development environment. The script:

* Adds test certificate to the certificate store. Used to sign test packages for inner-loop development and testing
* Installs the TAEF servce (TE.Service). Used by TAEF to enable test functionality (e.g. RunAs).

This is needed once to enable your machine to develop Windows App SDK. It may be needed again in the
future at rare intervals e.g. the test certificate usually expires a year from its issue date) or if
the TAEF dependency has an update. When in doubt you can always run `tools\DevCheck.cmd` as it's
harmless if your configuration is current with no changes needed.

# Tada!

Now you're ready to load `WindowsAppSDK.sln` and start development!

Some tips:

* Build everything in VS via the Build menu's `Build Solution` or `Rebuild Solution`
* Right-click on individual projects in Solution Explorer to only build select projects.
  Dependencies and Build Order should be defined to build prerequisites (if necessary) for the
  selected project.
* Use msbuild.exe for command line builds (see below)

## MSBuild Tips

Build everything from the command line via msbuild e.g.

| Goal | Command Line |
|---|---|
| Clean Solution, Debug/x64 | `msbuild WindowsAppSDK.sln -t:Clean -p:Configuration=Debug -p:Platform=X64` |
| Build solution, Debug/x64 | `msbuild WindowsAppSDK.sln -t:Build -p:Configuration=Debug -p:Platform=X64` |
| Rebuild Solution, Debug/x64 | `msbuild WindowsAppSDK.sln -t:Rebuild -p:Configuration=Debug -p:Platform=X64` |
| Build solution, create binary log | `msbuild WindowsAppSDK.sln -t:Rebuild -p:Configuration=Debug -p:Platform=X64 -bl` |
| Build solution, detailed summary of execution | `msbuild WindowsAppSDK.sln -t:Rebuild -p:Configuration=Debug -p:Platform=X64 -ds` |

See MSBuild documentation for more details.

Troubleshoot build problems by enabling binary logging (e.g. `msbuild...-bl`) and use
[MSBuild Binary and Structured Log Viewer](https://msbuildlog.com/) to review the log.

## Testing Tips

* Use Test Explorer to view and run tests via the View menu's `Test Explorer`
* Right-click in Test Explorer and `Run` or `Debug` to run or debug a subset or individual tests
* Run TAEF tests from the command line e.g. assuming current directory is `BuildOutput\Debug\x64`

| Goal | Command Line |
|---|---|
| Run all tests in a DLL | `te.exe WindowsAppRuntime_BootstrapDLL\Microsoft.WindowsAppRuntime.Bootstrap.dll` |
| Run all tests in multiple DLLs | `te.exe WindowsAppRuntime_BootstrapDLL\Microsoft.WindowsAppRuntime.Bootstrap.dll WindowsAppRuntime_DLL\Microsoft.WindowsAppRuntime.dll` |
| Run some tests in a DLL | `te.exe WindowsAppRuntime_BootstrapDLL\Microsoft.WindowsAppRuntime.Bootstrap.dll /name=*Create*` |
| Run tests only displaying per-tests reults and errors | `te.exe WindowsAppRuntime_BootstrapDLL\Microsoft.WindowsAppRuntime.Bootstrap.dll /logoutput:low` |

See TAEF documentation for more details.
