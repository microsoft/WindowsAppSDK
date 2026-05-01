# Windows App SDK Projection Headers

This branch carries the AbiWinRT projection headers produced for a
specific public release of the Windows App SDK. Consuming applications
that need the C-style ABI projections — and only those projections —
can shallow-clone or download this branch without dragging in the rest
of the WindowsAppSDK source.

The branch is an **orphan** branch: it has no parents and contains
only the `inc/` tree (these projection headers, this README, and the
script that produced them).

<!-- BEGIN AUTO-GENERATED COMPONENT LIST -->
Current projection packages, for [Microsoft.WindowsAppSDK v2.0.1](https://www.nuget.org/packages/Microsoft.WindowsAppSDK/2.0.1):

* [Microsoft.WindowsAppSDK.Base v2.0.3](https://www.nuget.org/packages/Microsoft.WindowsAppSDK.Base/2.0.3)
* [Microsoft.WindowsAppSDK.Foundation v2.0.20](https://www.nuget.org/packages/Microsoft.WindowsAppSDK.Foundation/2.0.20)
* [Microsoft.WindowsAppSDK.InteractiveExperiences v2.0.12](https://www.nuget.org/packages/Microsoft.WindowsAppSDK.InteractiveExperiences/2.0.12)
* [Microsoft.WindowsAppSDK.WinUI v2.0.12](https://www.nuget.org/packages/Microsoft.WindowsAppSDK.WinUI/2.0.12)
* [Microsoft.WindowsAppSDK.DWrite v2.0.26041403](https://www.nuget.org/packages/Microsoft.WindowsAppSDK.DWrite/2.0.26041403)
* [Microsoft.WindowsAppSDK.Widgets v2.0.4](https://www.nuget.org/packages/Microsoft.WindowsAppSDK.Widgets/2.0.4)
* [Microsoft.WindowsAppSDK.AI v2.0.185](https://www.nuget.org/packages/Microsoft.WindowsAppSDK.AI/2.0.185)
* [Microsoft.WindowsAppSDK.ML v2.0.300](https://www.nuget.org/packages/Microsoft.WindowsAppSDK.ML/2.0.300)
* [Microsoft.WindowsAppSDK.Runtime v2.0.1](https://www.nuget.org/packages/Microsoft.WindowsAppSDK.Runtime/2.0.1)
<!-- END AUTO-GENERATED COMPONENT LIST -->

## Producing a new release

To cut headers for a new public Windows App SDK release, run
[`make_projection.ps1`](./make_projection.ps1) from any clone of
the WindowsAppSDK repository:

```pwsh
pwsh ./inc/make_projection.ps1 -Version <umbrella-nuget-version>
```

For example, to produce headers matching
`Microsoft.WindowsAppSDK 2.0.1`:

```pwsh
pwsh ./inc/make_projection.ps1 -Version 2.0.1
```

The script will:

1. Download `Microsoft.Windows.AbiWinRT` and the
   `Microsoft.WindowsAppSDK` metapackage at the requested version.
2. Read the metapackage's `.nuspec` to discover the pinned versions
   of every component package, then download each one.
3. Run `abi.exe` over each component's WinMD metadata, copying any
   companion `include/` payload alongside.
4. Regenerate the auto-generated component-version section in this
   README.
5. Create a fresh orphan branch named `release/<Version>` containing
   only the regenerated `inc/` tree, and commit it.

The resulting branch is **left local**. Review the commit, then push
manually:

```pwsh
git push origin release/<Version>
```

### Parameters

| Parameter              | Required | Description                                                                  |
| ---------------------- | :------: | ---------------------------------------------------------------------------- |
| `-Version`             |   yes    | Umbrella `Microsoft.WindowsAppSDK` nuget version, e.g. `2.0.1`.              |
| `-WorkingDirectory`    |    no    | Scratch dir for nuget installs. Default: `$env:TEMP\wasdk_inc_<Version>`. Must be outside the repository. |
| `-NoCommit`            |    no    | Generate the staged `inc/` tree but skip all git operations.                  |
| `-Force`               |    no    | Replace an existing local `release/<Version>` branch.                         |
| `-KeepWorkingDirectory`|    no    | Don't delete the scratch directory on exit (useful for debugging).            |
| `-SkipTest`            |    no    | Skip the automatic projection-header smoke test (see `inc/test/`).            |

### Prerequisites

* PowerShell 5.1 or PowerShell 7+
* `git` on `PATH`
* `nuget.exe` on `PATH`
* A clean working tree (no uncommitted changes)

A Windows Platform SDK is recommended on the box, e.g.:

```pwsh
winget install Microsoft.WindowsSDK.10.0.26100
```

## Bootstrapping

The very first orphan release branch (`release/2.0.1`) is produced by
running the script from a regular WindowsAppSDK working branch where
this script and README already exist under `inc/`. Subsequent releases
can be produced by running the script from any prior orphan release
branch — the script and README ride along on every new orphan branch
it creates.
