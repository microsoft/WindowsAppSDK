# Foundation pipeline investigation: CFG and publisher cache paths

The original build failure was caused by removing Control Flow Guard from the
isolated StoragePickersTestApp project. Fixing that blocker exposed a separate
publisher-cache path regression in the same source change. Both corrections are
verified by the successful full [build 158111841](https://microsoft.visualstudio.com/ProjectReunion/_build/results?buildId=158111841&view=results).

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

## Controlled local verification

The reproduced project was evaluated before and after restoring only the CFG
metadata. The installed MSBuild / Visual C++ targets evaluated the actual
project, and `ComputeLinkSwitches` was invoked with an inspection-only link
input. No compiler or linker was executed by this inspection.

| Configuration | Platform | Guarded compiler inputs before / after | Link CFG before / after |
| --- | --- | --- | --- |
| Debug | Win32 | 0/5 -> 5/5 | unset -> `true` |
| Debug | x64 | 0/5 -> 5/5 | unset -> `true` |
| Debug | ARM64 | 0/5 -> 5/5 | unset -> `true` |
| Release | Win32 | 0/5 -> 5/5 | unset -> `true` |
| Release | x64 | 0/5 -> 5/5 | unset -> `true` |
| Release | ARM64 | 0/5 -> 5/5 | unset -> `true` |

This establishes that the one-line restoration supplies both compiler metadata
and the automatically derived linker setting for all six configurations.
The local machine has Visual Studio 2026 targets, not the original build's
complete VS 2022 / v143 environment and restored packages. This inspection is
therefore not a substitute for rebuilding and scanning the actual executable.

## First verification: CFG correction

[Build 158107847](https://microsoft.visualstudio.com/ProjectReunion/_build/results?buildId=158107847&view=results)
(`3.0.0-ci.experimental95`) ran the exact correction commit
`1a11a66a9de818db6910cfa2860525a997130285`. It used the original pipeline
definition and revision with `runStaticAnalysis=true`, `BuildSampleApps=false`,
`TestSampleApps=false`, and `TestOnArm64=false`.

The StoragePickersTestApp directory differs from the original failing source by
only the restored CFG line. No BinSkim or Guardian policy was modified. External governed
template references are floating and advanced between the two runs, so the
compiler commands and scanned artifacts were also checked directly rather than
relying only on an overall pipeline status.

### Actual compiler and linker commands

The original x64 build log (958) and corrected x64 build log (957) both use MSVC
**14.44.35207**.

| Executable build commands | Original | Corrected |
| --- | --- | --- |
| Compiler commands containing `/guard:cf` | 0 of 5 | 5 of 5 |
| Linker commands containing `/guard:cf` | 0 of 2 | 2 of 2 |
| Linker commands containing `/DYNAMICBASE` | 2 of 2 | 2 of 2 |

Both the intermediate WinMD link and final executable link now receive CFG
automatically. No standalone linker override was added.

### Actual BinSkim artifacts

The corrected x86, x64, ARM64, and PREFast x64 stages succeeded. Their BinSkim
**4.4.9** SARIF reports were downloaded and checked for the actual
`StoragePickersTestApp.exe`, not just an empty error list:

| Stage | Scanned executable copies | BA2008 findings | Existing BA2024 findings |
| --- | --- | --- | --- |
| `Build_x86` | 2 | 0 | 2 |
| `Build_x64` | 2 | 0 | 2 |
| `Build_arm64` | 2 | 0 | 2 |
| `PREfast_x64` | 2 | 0 | 2 |

For each architecture, the `BuildOutput` and `out` executables have identical
SHA-256 hashes, and both have scan observations. The remaining BA2024 warnings
also confirm that these binaries were included in the scan.

All four original failing `Guardian: Post Analysis` tasks succeeded, with zero
errors (logs 1068, 1095, 1015, and 1694 respectively). The eight original BA2008
findings are eliminated without suppressions.

## Downstream regression exposed by the successful build

The successful native stages allowed the runtime tests to execute. The first
verification run then exposed a second regression from the same original
ApplicationData optimization: the existing
`PublisherCacheFolderAndPath_Main` test failed on modern Windows x64 and x86
configurations. The build is therefore not claimed as an overall success.
After retaining the completed security-gate evidence and the five failing test
cases, this superseded run was canceled. Its overall result is `canceled`, not
`succeeded`; the replacement run kept the full test matrix enabled.

For the folder name `Does.Not.Exist`, `GetPublisherCacheFolder` returned no folder,
but `GetPublisherCachePath` returned a nonempty publisher-cache path. The test
correctly expected an empty string. The failure is in
[ApplicationDataTests.cpp](../test/ApplicationData/ApplicationDataTests.cpp), not
in `StoragePickersTestApp`.

The optimization replaced the previous folder-based implementation with
`ApplicationData_GetPublisherCachePath`. The native helper did not preserve the
same missing-folder behavior. This violates the equivalence documented in
[ApplicationData.idl](../dev/ApplicationData/ApplicationData.idl) and the
[ApplicationData specification](../specs/applicationdata/ApplicationData.md).

The focused correction in
[M.W.S.ApplicationData.cpp](../dev/ApplicationData/M.W.S.ApplicationData.cpp)
reuses the existing `StorageFolderToPath(GetPublisherCacheFolder(folderName))`
path. This preserves missing-folder and framework-package behavior and continues
to propagate other errors through the existing folder API. The other path
optimizations are unchanged; no test expectation is relaxed.

## Final verification: both corrections

[Build 158111841](https://microsoft.visualstudio.com/ProjectReunion/_build/results?buildId=158111841&view=results)
(`3.0.0-ci.experimental96`) completed **succeeded** at
`2026-09-20T11:05:19Z`, using commit
`2c79640247baa0f81ff894a28eca36cc555a18bc`.

It used definition 188465, revision 19, with the original parameters, including
`runStaticAnalysis=true`. No test, scan, suppression, or pipeline condition was
weakened. Fourteen stages succeeded. Only `UpdateFoundationLibrary` was skipped
under the existing pipeline conditions.

### Final binary analysis

All four original failure gates succeeded with zero errors. The final commit's
BinSkim 4.4.9 SARIF reports were independently downloaded and checked again:

| Stage | Guardian log ID | Scanned copies | BA2008 findings |
| --- | --- | --- | --- |
| `Build_x86` | 1062 | 2 | 0 |
| `Build_x64` | 1089 | 2 | 0 |
| `Build_arm64` | 1032 | 2 | 0 |
| `PREfast_x64` | 1925 | 2 | 0 |

Each pair consists of the real `BuildOutput` and `out` executable, with matching
SHA-256 hashes and scan observations. Existing BA2024 warnings remain outside
the scope of these corrections.

### Final runtime tests

All published test results were read with pagination, rather than relying only
on a green stage indicator:

| Metric | Result |
| --- | --- |
| OS/architecture test matrices | 12 |
| Total test results | 13,788 |
| Passed | 10,889 |
| Skipped / not applicable | 2,899 |
| Failed / incomplete | 0 |

Every previously failing `PublisherCacheFolderAndPath_Main` case was matched by
matrix and test name and verified as **Passed**, not skipped:

| Architecture | OS matrix | Before | After |
| --- | --- | --- | --- |
| x86 | Windows 11 Professional 25H2, zh-CN | Failed | Passed |
| x64 | Windows 11 Enterprise MultiSession 24H2 | Failed | Passed |
| x64 | Windows Server 2025 DataCenter | Failed | Passed |
| x64 | Windows 11 Enterprise 24H2 | Failed | Passed |
| x64 | Windows 11 Enterprise 25H2 | Failed | Passed |

The corresponding framework-package cases also passed. The original test
assertions are unchanged. The Win10 checked-OS matrix completed successfully in
this final run as well.

## Investigation checkpoints

| Commit | Result |
| --- | --- |
| `dec432ea` | Imported the failing source and recorded the CFG diagnosis |
| `1a11a66a` | Restored the single CFG setting and verified all six MSBuild configurations |
| `e9d75d21` | Recorded actual compiler/linker switches and binary scan evidence |
| `2c796402` | Restored publisher-cache availability semantics; full pipeline verified |

The final report-only update does not change the product code, tests, or pipeline
configuration that was validated at `2c796402`.
