# DynamicDependencies.ManualTest

**NOTE:** This is for dev inner-loop testing if/when changes are made to Dynamic Dependencies and/or
the Bootstrapper. This is not a manual test for release verification.

* FeatureArea: Dynamic Dependencies
* ADO Area Path: OS\WDX\DXP\APT-Application Platform and Tools\App Deployment
* Contact: appdeployment@microsoft.com

## Special needs

N/A

## Test Steps

### Build

WindowsAppRuntime.sln builds a multiverse of `HelloWorld` variants.

```
[C:\source\repos\projectreunionInternal]tree /S2 test\DynamicDependencies\ManualTest

C:\source\repos\projectreunionInternal\test\DynamicDependencies\ManualTest\
[C:\source\repos\projectreunionInternal\test\DynamicDependencies]tree /S2

C:\source\repos\projectreunionInternal\test\DynamicDependencies
+--GetCurrentPackageInfo
\--ManualTest
   +--HelloWorld
   |  +--C
   |  +--CPP
   |  \--CS
   \--HelloWorldAdvanced
      +--C
      +--CPP
      \--CS
```

### Test

1. Install WinAppSDK e.g. run WindowsAppRuntimeInstaller.exe from https://learn.microsoft.com/en-us/windows/apps/windows-app-sdk/downloads
2. Run test exes e.g. `HelloWorldAdvancedCPP.exe 1.7 experimental1`
2a. Run tests for success cases
2b. Run tests for expected failure cases

#### Example runs

```
[C:] BuildOutput\Debug\x64\HelloWorldAdvancedCPP\HelloWorldAdvancedCPP.exe 1.0
MddBootstrapInitialize(0x00010000, "", 0.0.0.0)...
Hello World!

[C:] BuildOutput\Debug\x64\HelloWorldAdvancedCPP\HelloWorldAdvancedCPP.exe 1.1
MddBootstrapInitialize(0x00010001, "", 0.0.0.0)...
Error 0x80070491 in MddBootstrapInitialize(0x00010001, "", 0.0.0.0)

[C:] BuildOutput\Debug\x64\HelloWorldAdvancedCPP\HelloWorldAdvancedCPP.exe 5.9
MddBootstrapInitialize(0x00050009, "", 0.0.0.0)...
Error 0x80070491 in MddBootstrapInitialize(0x00050009, "", 0.0.0.0)
```

#### List installed WinAppSDK packages

Verify no Windows App SDK runtime packages are registered for the user:

```
powershell -c "$(get-appxpackage micro*win*apprun*).packagefullname | sort"
```

Undesired packages can be removed via the command line:

```
powershell -c "$(get-appxpackage micro*win*apprun*).packagefullname | remove-appxpackage"
powershell -c "$(get-appxpackage micro*win*apprun*).packagefullname"
```

NOTE:  If packages are provisioned they also need to be deprovisioned `remove-appxprovisionedpackage` at an admin command prompt. To enumerate provisioned WinAppSDK packages:

```
powershell -c "get-appxprovisionedpackage -Online | where-object { $_.PackageName -Like "micro*win*app*run*" }
```

#### Run tests - Success Expected

##### HelloWorldAdvanced

HelloWorld tests use the version specified on the command line. They require command line parameters
(run without parameters for help). Specify the target version on the command line by changing the value for R:

```
SET D=BuildOutput\Debug\x64
SET HWA=HelloWorldAdvancedC HelloWorldAdvancedCPP HelloWorldAdvancedCS
SET R=0x00010001 "" 1000.516.2156.0
FOR %f IN (%HWA%) DO %D%\%f\%f.exe %R%
```

The commands should succeed e.g. the output when run for 1.1.0-stable

```
Bootstrap.Initialize(00010001, "", 1000.516.2156.0)...
Hello World!
```

#### Run tests - Failure Expected

These tests use HelloWorldAdvanced to force failure conditions to verify they fail in the expected ways.

##### HelloWorldAdvanced

The following tests fail to find the runtime and are expected to fail in very specific ways.

By default a message box is displayed about not finding a suitable runtime and then the program terminates.

NOTE: Vary the target version information (R) to verify the various permutations of failure conditions.
These examples assume 1.1.0-stable is installed.

```
SET D=BuildOutput\Debug\x64
SET HWA=HelloWorldAdvancedC HelloWorldAdvancedCPP HelloWorldAdvancedCS
SET R=0
FOR %f IN (%HWA%) DO %D%\%f\%f.exe %R%

SET R=0x00010001 "hello"
FOR %f IN (%HWA%) DO %D%\%f\%f.exe %R%

SET R=0x00010001 "" 65535.65535.65535.65535
FOR %f IN (%HWA%) DO %D%\%f\%f.exe %R%
```

### About the manual tests

HelloWorldAdvanced is parses optional cmdline parameters. Run with no parameters for help.

The CS variants are written in C#. As these .NET executables load the CLR and
`Microsoft.WindowsAppRuntime.Bootstrap.Net.dll` to call the native API in
`Microsoft.WindowsAppRuntime.Bootstrap.dll` it's just a slower more-annoying-to-debug &lt;g&gt;
way to manually test the Bootstrap API.

The CPP variants are written in C++, making HelloWorldAdvancedCPP.exe
the most interesting helloworld app in the world :-)

### Pass Criteria

See "Run tests - Success Expected" and "Run tests - Failure Expected".
