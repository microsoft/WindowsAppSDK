# Getting Started

# Tooling Prerequisites

Development requires the following installation:

1. Install Visual Studio 2022

   Select the following workloads:
     * .NET desktop development
     * Desktop development with C++
     * Universal Windows Platform development

   Additional components are quired. To add them via the Visual Studio Installer...
     * select `More` / `Import configuration`
     * select the file `docs\Coding-Guidelines\VisualStudio2022.vsconfig` in the repository
     * select `Review details`
     * select `Modify`
   and wait for the install to complete.

2. Run `DevCheck -CheckAll -FixAll` from an admin prompt to verify your configuration and perform
   additional installation and configuration updates (if necessary). See `One-Time Setup` for more details.

# One-Time Setup

Run the `DevCheck.cmd` from an elevated command prompt (e.g. right-click on "Command Prompt"
in the Start Menu and select `Run as Administrator`) to update your development environment. The script will:

* Verify Windows' Developer Mode is enabled.
* Verify LongPath support (and enable if necessary).
* Verify nuget.exe is available (and download if necessary).
* Verify Visual Studio is installed with the required components.
* Verify Windows 10 SDK 10.0.17763.0 is installed (and install if necessary).
* Verify Windows 11 SDK 10.0.26100.4654+ is installed (and install if necessary).
* Verify a password-protected test certificate exists and add it to the certificate store (or create if necessary). Used to sign test packages for inner-loop development and testing.
* Install the TAEF service (TE.Service). Used by TAEF to enable test functionality (e.g. RunAs).
* Verify the project's dependencies are sanctioned and using the correct version(s).

This is needed once to enable your machine to develop Windows App SDK. It may be needed again in the
future at rare intervals e.g. the test certificate usually expires a year from its issue date) or if
a dependency has an update. When in doubt you can always run `DevCheck.cmd` as it's
harmless if your configuration is current with no changes needed.

# Tada!

Now you're ready to load `WindowsAppRuntime.sln` and start development!

Some tips:

* If VS starts in a configuration of `Any CPU`, switch to a specific architecture like `x64`
  to successfully build.
* Build everything in VS via the Build menu's `Build Solution` or `Rebuild Solution`
* Right-click on individual projects in Solution Explorer to only build select projects.
  Dependencies and Build Order should be defined to build prerequisites (if necessary) for the
  selected project.
* Use msbuild.exe for command line builds (see below)

## MSBuild Tips

### Build everything from the command line via msbuild e.g.

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

### Common Build Errors

#### Problem 001: Expired Test Certificate

##### Symptoms

###### VS ErrorList:


```MSB3073 The command "signtool.exe sign ..." exited with code 1...\MakeMsix.targets...```

###### Build Output:

```
Build Output: EXEC : SignTool error : No certificates were found that met all the given criteria.
...\MakeMsix.targets...error MSB3073: The command "signtool.exe sign ..." exited with code 1.
```
##### Solution

Run `DevCheck.cmd` (from an admin prompt). This detects the expired certificate and prompts to create a new one.

## Testing Tips

* Use Test Explorer to view and run tests via the View menu's `Test Explorer`
* Right-click in Test Explorer and `Run` or `Debug` to run or debug a subset or individual tests
* Run TAEF tests from the command line e.g. assuming current directory is `BuildOutput\Debug\x64`

| Goal | Command Line |
|---|---|
| Run all tests in a DLL | `te.exe DynamicDependency_Test_Win32\DynamicDependency_Test_Win32.dll` |
| Run all tests in multiple DLLs | `te.exe DynamicDependency_Test_Win32\DynamicDependency_Test_Win32.dll AppLifecycleTests\AppLifecycleTests.dll` |
| Run some tests in a DLL | `te.exe DynamicDependency_Test_Win32\DynamicDependency_Test_Win32.dll /name=*Create*` |
| Run tests only displaying per-tests reults and errors | `te.exe DynamicDependency_Test_Win32\DynamicDependency_Test_Win32.dll /logoutput:low` |

See TAEF documentation for more details.

## Github PullRequest Tips

To trigger validation, comment "/azp run" in your Pull Request.

Main branch runs: https://dev.azure.com/ms/ProjectReunion/_build?definitionId=391

Develop branch runs an internal pipeline by the name of "TransportPackage-Foundation-PR"
You may also comment "/azp run TransportPackage-Foundation-PR" to specifically run that pipeline.
The azure-pipelines[bot] may say "Azure Pipelines could not run because the pipeline triggers exclude this branch/path."
But this is inaccurate. The pipeline will run.
