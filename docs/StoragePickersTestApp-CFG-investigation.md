# StoragePickersTestApp: Control Flow Guard build failure

## Failing build and source

[Build 157600955](https://microsoft.visualstudio.com/ProjectReunion/_build/results?buildId=157600955&view=results)
ran `TransportPackage-Foundation-PR (OneBranch)`, definition 188465, revision 19.
Its build number was `3.0.0-ci.experimental92`.

The build used merge commit `799e43891f367a90e9307fe394c303d90becad71`, not the
current main-branch version of the test project. That merge combined main commit
`13160d542e410f826b524ffa6bdbb7700db9fb40` with source commit
`128e930056922578a4c68ef219ee4baf58cdb634`.

Commit
[`242843a8af0579873924aaa64787adc4d862d632`](https://github.com/microsoft/WindowsAppSDK/commit/242843a8af0579873924aaa64787adc4d862d632)
removed `<ControlFlowGuard>Guard</ControlFlowGuard>` from
[StoragePickersTestApp.vcxproj](../test/TestApps/StoragePickersTestApp/StoragePickersTestApp.vcxproj).
It also removed several unrelated warning and optimization settings. The
investigation branch originally started from main commit `99024437`, which still
contained the CFG setting. The failing source was imported into the investigation
branch before applying a fix, so validation does not accidentally test an
unaffected version of this project.

## Observed failure

All four failing jobs reached `Guardian: Post Analysis`. Each reported BinSkim
**BA2008 (EnableControlFlowGuard)** for `StoragePickersTestApp.exe`.

| Stage | Guardian log ID | Affected architecture |
| --- | --- | --- |
| `Build_x86` | 981 | Win32 |
| `Build_x64` | 1071 | x64 |
| `Build_arm64` | 1050 | ARM64 |
| `PREfast_x64` | 1106 | x64 |

Each job reported the executable twice: once in `BuildOutput` and once in its
staged `out` copy. These are not separate compiler failures.

The x64 build log (958) confirms that the test application's compiler commands
and final linker command omitted `/guard:cf`. The linker already used
`/DYNAMICBASE`, so address-space randomization was not the missing setting.

BA2024 (EnableSpectreMitigations) was also reported for this executable, but as a
warning. It was not the error that caused these jobs to fail.

## Root cause

The test app deliberately isolates itself from the repository's build defaults
using local [Directory.Build.props](../test/TestApps/StoragePickersTestApp/Directory.Build.props)
and [Directory.Build.targets](../test/TestApps/StoragePickersTestApp/Directory.Build.targets).
This is necessary when consuming the shipped Windows App SDK NuGet package.
Consequently, the common CFG setting in
[WindowsAppSDK.Build.Cpp.props](../WindowsAppSDK.Build.Cpp.props) cannot compensate
for removing the test app's explicit setting.

MSVC's `ComputeLinkSwitches` target derives `LinkControlFlowGuard` from
`ClCompile` items with `ControlFlowGuard=Guard`. Removing that metadata therefore
removes CFG from both compilation and linking. This is a project configuration
regression, not a Guardian failure or a missing standalone linker option.

## Minimal correction

Restore the following metadata in the test project's existing unconditional
`ItemDefinitionGroup` / `ClCompile` element:

```xml
<ControlFlowGuard>Guard</ControlFlowGuard>
```

The unconditional setting covers Debug and Release on Win32, x64, and ARM64.
Keep `RandomizedBaseAddress=true`. No BinSkim suppression, scan exclusion, or
pipeline policy change is required. The other removed optimization settings
are not part of this correction.

## Verification status

The original failure, source regression, and missing compiler/linker switches
have been verified. Corrected-build validation is not yet complete.
