# Experimental APIs

Windows App SDK provides some support for authoring Experimental code, that is, code which is
present in the _Experimental_ release channel, but not in the _Preview_ or _Stable_ release
channels. For more background on release channels, see:

-   [Final Decision: Release channels and cadences #937](https://github.com/microsoft/WindowsAppSDK/discussions/637)
-   [Git Checkin-to-main Policy](GitCheckinToMainPolicy.md)

# How to develop an experimental feature

The implementation of experimental features in Windows App SDK makes heavy use of
[TerminalVelocity](TerminalVelocity.md) to control how code is present/enabled or stripped/disabled
in different release channels. See the TerminalVelocity document for detailed information on how to
implement an experimental feature using a specific technology (e.g. C++, IDL, WinRT).

Your should ensure that your feature's state is disabled in Preview and Stable release channels, and
enabled in the Experimental release channel.

# Stripping experimental APIs from WinRT metadata (.winmd)

Following the [TerminalVelocity](TerminalVelocity.md) instructions will build intermediate winmds
with experimental APIs that are tagged with
[FeatureAttribute](https://docs.microsoft.com/en-us/uwp/api/windows.foundation.metadata.featureattribute).
Stored in the attribute is a
[FeatureStage](https://docs.microsoft.com/en-us/uwp/api/windows.foundation.metadata.featurestage)
enumeration with the value `AlwaysDisabled` for the Preview and Stable release channel, and
`DisabledByDefault` for the Experimental release channel. These winmds are suitable for local unit
testing, but not for public consumption or generating public projections.

Therefore, these winmds need to go through an additional step to transform them before using them to
generating public projections. This step removes APIs tagged with `AlwaysDisabled`
FeatureAttributes, and will transform `DisabledByDefault` FeatureAttributes into
[ExperimentalAttribute](https://docs.microsoft.com/en-us/uwp/api/windows.foundation.metadata.experimentalattribute).

The mdmerge tool (available in the Windows SDK) does this when supplied with the switches
`-transformExperimental:transform` and `-createPublicMetadata`. Other switches that mdmerge needs
beside `/i` (input) and `/o` (output) are:

-   `-metadata_dir` for each set of referenced external metadata (such as SDKs or NuGet package
    dependencies)
-   `-partial` which is required when transforming input winmds with external references (aka
    /metadata_dir)
-   (optional) `-n` which specifies the namespace depth used in the output merged winmds. Omitting
    this would cause `Microsoft.Windows.Widgets.winmd` and `Microsoft.Windows.Gadgets.winmd` to be
    merged into `Microsoft.winmd`, which is typically not desired. Supply a high value, like `-n:9`
    to prevent this "over-merging" and keep each namespace in a distinct winmd file.

## Integrating mdmerge into your build with help from C++/WinRT

The preferred way to do this with low friction is to add a custom target to your build, and use
C++/WinRT in your project (via NuGet) which does the heavy lifting of calculating the set of
reference winmds (aka `-metadata_dir`) rather than hard-coding an SDK path.

This is the approach used in WindowsAppRuntime_DLL.vcxproj in this repo, with this custom target:

```xml
  <Target Name="MakeStrippedMetadata" AfterTargets="CppWinRTMergeProjectWinMDInputs" BeforeTargets="ClCompile">
    <PropertyGroup>
      <_MdMergeParameters>-v @(CppWinRTMdMergeMetadataDirectories->'-metadata_dir "%(RelativeDir)."', ' ')</_MdMergeParameters>
      <_MdMergeParameters>$(_MdMergeParameters) -o "$(OutDir)StrippedWinMD" @(CppWinRTMdMergeInputs->'-i "%(Identity)"', ' ') -partial -n:9 -createPublicMetadata -transformExperimental:transform</_MdMergeParameters>
    </PropertyGroup>
    <Exec Command="$(MdMergePath)mdmerge $(_MdMergeParameters)" />
  </Target>
```

This target runs after `CppWinRTMergeProjectWinMDInputs` (which merges and namespace-splits the
input winmds produced from your IDL files), but before compilation. It uses
`CppWinRTMdMergeMetadataDirectories` to populate `-metadata_dir` and `CppWinRTMdMergeInputs` to
populate `-i`. Finally, it uses `-n:9` to split the output winmds by namespace, and sends the output
(`-o`) to a subfolder named StrippedWinMD.

When it is time to consume winmds for generating public projections (e.g. C#/WinRT) and to copy
winmds for publishing to NuGet, be sure to use the stripped winmds, not the intermediate winmds.

# Rationale and rejected approaches

## Use [experimental] directly in IDL, with channel-based stripping

This has the benefit of clarity in the IDL file, because `[experimental]` states a clearer intent than `[feature(Feature_MyFeature)]`.
However, this would have one major drawback, and one inconvenience:
1. The state of the WinRT API stripping would no longer be tied to the state of the implementation. This would increase the risk
of accidentally having a disabled implementation behind a visible API, or having a live implementation hidden by a stripped API.
2. Stripping of the WinRT API would no longer be controlled by TerminalVelocity, but would be controlled inside
the MSBuild of the project, which would neccessitate plumbing that pipeline build parameter into the build.

## Use [experimental] directly in IDL, with conditional compilation

One could achieve a similar approach by tagging an API directly with `[experimental]` in the IDL, and adding `#if defined(...)`
preprocessor guards to conditionally compile the API.

This adds error-prone clutter to the IDL. Additionally, this conditional compilation would break the ability to compile unit tests
without also infecting them with conditional compilation.