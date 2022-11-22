# TerminalVelocity

TerminalVelocity provides a means to efficiently define code to be present in some channels but not others.
This enables Windows App SDK to include experimental code in main that's available in builds for
the Experimental channel but efficiently NOOP'd when and not-functional (if even present) in
Preview and Stable builds.

TerminalVelocity is similar to Windows' Velocity feature providing a means to NOOP code, but usable
by Windows App SDK (opensource, MIT License, etc).

TODO: @DefaultRyan insert-link-here to the Experimental/Stripping documentation. This document is
solely about how TerminalVelocity works and used by developers to implement 'bone-deep'
(implementation) stripping from Preview+Stable channels. It needs to be incorporated-into /
referenced-by the broader experimental/stripping documentation when available.

# Developer Guidance: How to use TerminalVelocity

TerminalVelocity uses an XML definition file to produce code artifacts that can be used to check if
a feature is enabled or disabled and act accordingly. The code artifacts vary depending on the
language.

## C++

Follow these steps:

1. Create `dev\common\TerminalVelocityFeatures-<feature>.xml`
2. Run the TerminalVelocity generator create `dev\common\TerminalVelocityFeatures-<feature>.h`
3. Add a task to call `Generate-TerminalVelocityFeatures.ps1` to the build pipeline `build\AzurePipelinesTemplates\WindowsAppSDK-SetupBuildEnvironment-Steps.yml`
4. Add TerminalVelocity checks to NOOP your feature
5. Checkin!

### Step 1. Create Feature Definition XML

TerminalVelocity uses an XML file as input defining feature(s) to express and their properties.
We'll use the DeploymentAPI as an example, per `dev\Common\TerminalVelocityFeatures-DeploymentAPI.xml`

```
01 <?xml version="1.0"?>
02 <features xmlns="http://microsoft.com/windowsappsdk/TerminalVelocity/20210729/TerminalVelocityFeatures.xsd">
03
04 <!-- Copyright (c) Microsoft Corporation. All rights reserved.
05      Licensed under the MIT License. See LICENSE in the project root for license information.
06 -->
07
08     <!-- See docs/TerminalVelocity.md for more info.  -->
09
10     <!-- Enabled variants -->
11     <feature>
12         <name>Feature_DeploymentAPI</name>
13         <description>DeploymentAPI for the WindowsAppRuntime</description>
14         <state>AlwaysEnabled</state>
15         <alwaysDisabledChannelTokens>
16             <channelToken>Preview</channelToken>
17             <channelToken>Stable</channelToken>
18         </alwaysDisabledChannelTokens>
19     </feature>
20 </features>
```

Line 11-19 defines a feature. A definition file can contain multiple features. Define as many as needed.

Line 12 is the feature's name. Feature name should begin with `Feature_`. This will appear in the
generated code and your calls to check the feature

Line 13 is descriptive prose about the feature.

Line 14 is the default state of the feature. Allowed values are [ `AlwaysEnabled`, `AlwaysDisabled` ].

Line 15 is an optional override to disable the feature for specified channels. An equivalent
`<alwaysEnabledChannelTokens>` is also supported, for features defined as `<state>AlwaysDisabled</state>`.

Lines 16-17 override the default `<state>` for specific channels.

This file defines one feature, `Feature_DeploymentAPI`, which is enabled except in the Preview and
Stable channels. Thus it's enabled in the Experimental channel (and thus CI, nightly and other
builds).

## Step 2. Generate Header File

Run the TerminalVelocity generator to create a header file for your feature definition file. This file will be checked in for use during inner-loop development.

For example:

```
tools\TerminalVelocity\Generate-TerminalVelocityFeatures.cmd -Path dev\common\TerminalVelocityFeatures-DeploymentAPI.xml -Namespace Microsoft.Windows.DeploymentAPI -Output dev\common\TerminalVelocityFeatures-DeploymentAPI.h
```

Generate-TerminalVelocityFeatures.cmd runs the generator. The following parameters are supported:

* **-Path &lt;file&gt;** -- definition file as input to the generator. Required.
* **-Channel &lt;channel&gt;** -- channel being built. Allowed values: [`Experimental`, `Preview`, `Stable`, `WindowsInbox`]. Optional, default=`Experimental`.
* **-Language &lt;language&gt;** -- language for generated code. Allowed values: [`C++`, `C#`]. Optional, default=`C++`.
* **-Namespace &lt;namespace&gt;** -- namespace for generated symbols. The parameter can specify multiple namespaces delimited by `.` or `::` (the generator emits the right syntax for the target language regardless of the parameter's notation). Optional.
* **-Output &lt;filename&gt;** -- file to write the generated output. Optional, default=stdout.

For help run

```
tools\TerminalVelocity\Generate-TerminalVelocityFeatures.cmd -?
```

## Step 3. Add Build Task

Add a build task to run the TerminalVelocity with the build's properties. For example:

```
  - task: powershell@2
    displayName: 'Create DeploymentAPI TerminalVelocity features'
    inputs:
      targetType: filePath
      filePath: tools\TerminalVelocity\Generate-TerminalVelocityFeatures.ps1
      arguments: -Path $(Build.SourcesDirectory)\dev\common\TerminalVelocityFeatures-DeploymentAPI.xml -Channel ${{ parameters.channel }} -Language C++ -Namespace Microsoft.Windows.ApplicationModel.WindowsAppSDK -Output $(Build.SourcesDirectory)\dev\common\TerminalVelocityFeatures-DeploymentAPI.h
      workingDirectory: '$(Build.SourcesDirectory)'
```

## Step 4. Add TerminalVelocity Checks

Implementations that need to vary behavior across channels can conditionally alter behavior
depending on the generated feature checks. For example:

```
#include <TerminalVelocityFeatures-DeploymentAPI.h>

winrt::Microsoft::Windows::ApplicationModel::WindowsAppSDK::DeploymentStatus DeploymentManager::GetStatus()
{
    THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::ApplicationModel::WindowsAppSDK::Feature_DeploymentAPI::IsEnabled());
    ...
}
```

### Tests

TAEF tests can easily skip exercising channel conditional features by checking the feature in their Setup fixture and, if disabled, logging `TestResults::Skipped` and returning. This causes TAEF to skip execution of the reset of the Setup fixture and all test methods with a non-failing status. For example:

```
#include <TerminalVelocityFeatures-DeploymentAPI.h>


TEST_CLASS_SETUP(Setup)
{
    if (!::Microsoft::Windows::ApplicationModel::WindowsAppSDK::Feature_DeploymentAPI::IsEnabled())
    {
        Log::Result(TestResults::Skipped, L"Deployment API Features are not enabled.");
        return true;
    }
    ...
}
```

## WinRT IDL

Follow the same steps as for C++ with the following additions:

1. Tag APIs in IDL
2. Transform winmds

This will ensure that your experimental APIs will be tagged with the `[experimental]` attribute in
the Experimental release channel, and will be removed from the Stable and Preview release channels.

### Step 1. Tag APIs in IDL

After you've created your XML and generated your header, you need to include the header in your IDL
and put the feature attribute on your APIs. For example:

```cs
#include <TerminalVelocityFeature-DeploymentAPI.h>

namespace Microsoft.Windows.ApplicationModel
{
  [feature(Feature_DeploymentAPI)]
  runtimeclass DeploymentManager
  {
    ...
  }
}
```

### Step 2. Transform WinMDs

This feature attribute be transformed to the experimental attribute in the Experimental release
channel, and APIs with this feature attribute need to be removed in Stable and Preview release
channels. See [Experimental APIs](Experimental.md) for details on how to invoke mdmerge to
accomplish this. If your IDL is authored and implemented in the WindowsAppRuntime_DLL, this step is
already being done for you (see target "MakeStrippedMetadata" in WindowsAppRuntime_DLL.vcxproj).

# FAQ

## Why 'TerminalVelocity'?

Because it's derived from Velocity-style work initially implemented by
[Windows Terminal](https://github.com/Microsoft/Terminal) :-)
