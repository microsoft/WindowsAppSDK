# Containment v2 — rollout plan

> **Status:** Rollout plan, tracking the implementation of [Runtime Compatibility Containment v2](../design/RuntimeCompatibilityContainmentV2.md).
> This document is the operational counterpart to the design doc: it records the staged PR sequence, the validation
> approach, and the role boundaries between servicing engineers and release engineers as the new model lands.

## Goals (recap)

The design proposal solves three problems with the existing per-callsite patch-version model:

1. **Servicing engineers no longer need to know the containing release version.** New
   `WINAPPSDK_CHANGE_*` macros expand to a bare change ID (no patch-version second
   argument); the catalog in `RuntimeCompatibilityOptions.cpp` is what actually
   associates change IDs to releases.
2. **Capturing change IDs at branch cut no longer churns the world.** Release engineering
   adds a single per-release group to the catalog at branch cut; no callsite edits.
3. **`RuntimeCompatibilityOptions.idl` is untouched.** No API review; only enum values
   added incrementally by the release engineer (no shape changes).
4. **The patch-version enum is owned by WinAppSDK, not by FrameworkUdk.** A new patch
   release no longer requires a coordinated edit to os.2020's public header. FrUdk's
   `Containment.h` exposes only the deprecated stub enum `WinAppSDKPatchVersionDeprecated`
   (all enumerators collapse to `WinAppSDK_Unused = UINT32(-1)`, which guarantees the
   `static_assert(patchVersion == 0, ...)` in the legacy 2-arg `IsChangeEnabled` template
   fires for any leftover `IsChangeEnabled<id, WinAppSDK_3_x>()` callsite while leaving
   the default-initialized 1-arg form unaffected); the live release-version mapping
   `enum class WinAppSDKReleaseVersion : UINT32` lives in the anonymous namespace of
   `dev/RuntimeCompatibilityOptions/RuntimeCompatibilityOptions.cpp` and is scoped to
   avoid name collisions with the FrUdk stub. The accompanying
   `WinAppSDKReleaseVersionFromValues` helper is also local to that .cpp; nothing
   outside the translation unit references either name.

## Role boundaries

| Role | Repo / file | What they do | What they never touch |
| --- | --- | --- | --- |
| **Servicing engineer** | os.2020 `onecoreuap\windows\FrameworkUdk\inc\public\Containment.h` (defines the bare ID) + the component source file (wraps the new behavior) | Adds one `#define WINAPPSDK_CHANGE_FOO id` macro (no patch-version arg); wraps the new behavior in `if (WinAppSdk::Containment::IsChangeEnabled<WINAPPSDK_CHANGE_FOO>())` | `RuntimeCompatibilityOptions.idl`, `RuntimeCompatibilityOptions.h`, `RuntimeCompatibilityOptions.cpp`, the catalog, the patch-version enum. Never names a release branch. |
| **Release engineer** | WindowsAppSDK `dev\RuntimeCompatibilityOptions\*` and `Microsoft.Windows.ApplicationModel.WindowsAppRuntime.RuntimeCompatibilityChange` IDL enum | At branch cut, adds a new `WinAppSDK_X_Y_Z` enumerator to the anonymous-namespace `enum class WinAppSDKReleaseVersion` inside `RuntimeCompatibilityOptions.cpp` (only if the catalog needs it), adds a `s_changes_X_Y_Z[]` array + corresponding `MakeGroup(...)` entry in `s_catalogGroupsProd[]`, and adds the corresponding IDL enum values | `Containment.h` (servicing engineer's territory; FrUdk stub enum never needs new enumerators again) |
| **App developer** | Their `.csproj` / `.vcxproj` | Sets `WindowsAppSDKRuntimePatchLevel1` / `WindowsAppSDKRuntimePatchLevel2` / `WindowsAppSDKDisabledChanges` as needed | Anything in the SDK source |

## Staged PR sequence

The work lands as four atomic changes, each safe to deploy independently.

| # | Repo | Scope | What happens if any one piece is missed |
| --- | --- | --- | --- |
| 1 | WindowsAppSDK | **Foundation.** Catalog plumbing + `Apply` pre-prune + `std::sort` of the disabled list + new `ContainmentTestInitialize` test-only DLL export + the `CompatibilityTests.dll` test catalog + WASDK-owned scoped `enum class WinAppSDKReleaseVersion` + `WinAppSDKReleaseVersionFromValues` helper, both confined to the anonymous namespace of `dev/RuntimeCompatibilityOptions/RuntimeCompatibilityOptions.cpp` (no header export, no other TU references). `Apply` builds a local `runtimePatchLevel`, walks the catalog against it, and mirrors the result into `WinAppSDKRuntimeConfiguration::patchVersion` via an opaque `UINT32` cast (preserves the `SetConfiguration` identity-divergence check). `RuntimeCompatibilityOptions.h`, `CompatibilityTests.cpp`, and `CompatibilityTests.vcxproj` are untouched by PR 1 — the scoped enum is a private .cpp detail. | Nothing visible to apps. Catalog is empty on `main`; the only behavior change is that `Apply` now produces a sorted disabled list. The existing FrUdk worker (still linear scan) continues to behave correctly. Legacy `IsChangeEnabled<id, real-version>` callsites are unchanged. |
| 2 | os.2020 (FrUdk) | **Worker perf + enum deprecation.** `Containment_GetChangeEnabled` switches from linear scan to `std::binary_search` (relying on PR 1's sort guarantee). `Containment.h` renames `WinAppSDKPatchVersion` to `WinAppSDKPatchVersionDeprecated`, adds `WinAppSDK_Unused = UINT32(-1)`, collapses all `WinAppSDK_3_*` enumerators to `WinAppSDK_Unused`, and removes `WinAppSDK_Latest`, `WinAppSDK_Security`, and `WinAppSDKPatchVersionFromValues`. The `static_assert(patchVersion == 0, ...)` deprecation message is unchanged; setting `WinAppSDK_Unused` to `UINT32(-1)` (rather than `0`) deliberately tips the static_assert for any leftover 2-arg `IsChangeEnabled<id, WinAppSDK_3_x>()` callsite while leaving the default-initialized 1-arg form alone. os.2020-internal 2-arg callsites migrate to the 1-arg form. Single atomic commit. | os.2020 build break (the `static_assert` fires on any leftover 2-arg callsite naming any non-zero enumerator, and undefined-identifier errors fire on any callsite naming `WinAppSDK_Latest` / `WinAppSDK_Security` / removed `WinAppSDK_M_m_p` constants). Hence the migration ships in the same commit. |
| 3 | WindowsAppSDK | **FrUdk bump (`main`).** Bumps `Microsoft.FrameworkUdk` in `eng\Version.Details.xml` to pull in PR 2. `main`'s WASDK code is already prepared by PR 1 (private scoped enum in the .cpp, no public test-side surface), so the only churn is the version bump itself. No production WASDK callsites on `main` use the 2-arg form. | WASDK `main` build break (same `static_assert` / undefined identifier) on the bumped header without PR 1 in place. |
| 4 | WindowsAppSDK | **Cherry-pick to `release/2.0-stable`.** Brings the PR 1 foundation (catalog plumbing + private scoped enum, with the enum populated for the 2.x patch versions the 2.0 catalog references). The populated `s_catalogGroupsProd[]` on `2.0-stable` already encodes the `ApplicationData.GetForUnpackaged()` (`61684930`) and `MRT module-specific PRI discovery` (`62382643`) IDs under the `WinAppSDK_2_1_5` group, so callsites that switch from 2-arg to 1-arg `IsChangeEnabled` retain identical runtime behavior. The 2-arg `, WinAppSDK_2_1_5` second argument is left in place in `dev\ApplicationData\M.W.S.ApplicationData.cpp` and `dev\MRTCore\…\Helper.cpp` until the 2.0 train picks up the FrUdk PR 2 bump (whose `IsChangeEnabled` template adds a `WinAppSDKPatchVersionDeprecated patchVersion = {}` default; pre-bump FrUdk has no such default, so a bare 1-arg call fails to compile). | None — this PR is behavior-preserving on its own. |
| 4b | WindowsAppSDK (follow-up) | **2.0 FrUdk bump + macro migration.** Bumps `Microsoft.FrameworkUdk` on `release/2.0-stable` to pull in PR 2, and in the same commit drops `, WinAppSDK_2_1_5` from the two macros above. The catalog from PR 4 already covers both IDs, so the 1-arg `IsChangeEnabled<id>()` call still returns the same result; the `static_assert(patchVersion == 0)` from PR 2 keeps the file honest in the future. | The FrUdk bump alone would otherwise break the build (undefined identifier on `WinAppSDK_2_1_5` from the macro expansions). |

### Why this beats the original four-phase sequence

Earlier revisions of this plan staged a three-phase rollout that added a new 1-arg
`IsChangeEnabled<id>()` template to FrameworkUdk alongside the existing 2-arg one, with a
deprecation pragma on the 2-arg form. The `0`-patch-version sentinel design (see
[Runtime Compatibility Containment v2](../design/RuntimeCompatibilityContainmentV2.md))
eliminates the new template entirely: new macros expand to bare change IDs and the
existing 2-arg template defaults `patchVersion = 0`; the worker's per-callsite patch
check has been removed entirely (in favor of pre-pruning in `Apply`), and the
disabled-list check alone decides. That collapses "add new template + migrate
callsites" into "add catalog + sort + pre-prune in Apply" with no public FrUdk API
shape change. PR 2's `static_assert` is purely a quality-gate to keep future macros
honest; it has nothing to do with ABI.

A second simplification adopted later: the patch-version enum itself moves from FrUdk
into WinAppSDK, and is *not* exported from a header — it lives only in the anonymous
namespace of `RuntimeCompatibilityOptions.cpp`. FrUdk's `WinAppSDKPatchVersionDeprecated`
stub is frozen — it never needs another enumerator. New `WinAppSDK_X_Y_Z` constants
are added only to WASDK's private `enum class WinAppSDKReleaseVersion`, and only when
the catalog actually needs them. This eliminates the cross-repo enum-edit coordination
that the previous shape required for every patch release, and avoids the name-collision
risk that would arise if WASDK re-exported the same enumerator names that FrUdk's
unscoped legacy enum still carries.

## Validation status (as of this PR)

End-to-end test pass in both worktrees:

- **`main`** worktree (catalog empty): 6/6 `CompatibilityTests` pass — `CanSetRuntimeCompatibilityOptions`,
  `VerifyNoMatchingPatchLevelBehavior`, `VerifyConflictingPatchLevelBehavior`, `VerifyDisabledChanges`,
  `VerifyCatalogPrePrunesByPatchLevel`, `VerifyCatalogAndExplicitDisabledChangesCombine`.
- **`release/2.0-stable`** worktree (catalog populated with 8 production IDs across the
  `WinAppSDK_2_1_0` and `WinAppSDK_2_1_5` groups): 6/6 pass.

### Test catalog (foundation PR)

`CompatibilityTests` exercises catalog pre-pruning through a synthetic two-group test catalog
swapped in by `ContainmentTestInitialize(true)`:

* `s_enabled_changes_test = { 1, 2, 3 }` at `WinAppSDKPatchVersion::WinAppSDK_Latest - 1`.
  `releaseVersion` is **not** greater than the runtime's effective patch level under the
  default `WinAppSDKRuntimeConfiguration` (`Apply` resolves an unspecified patch level to
  `WinAppSDKPatchVersion::WinAppSDK_Latest`), so Apply prunes the group **out** of
  `disabledChanges`. These IDs remain **enabled** at runtime.
* `s_disabled_changes_test = { 0, 99999999 }` at `WinAppSDKPatchVersion::WinAppSDK_Latest + 1`.
  `releaseVersion` **is** greater than the effective patch level, so Apply preserves the
  group **in** `disabledChanges`. These IDs are **disabled** at runtime.

The synthetic IDs (`0`, `1`, `2`, `3`, `99999999`) span the value range so that `std::sort`
in Apply and `std::binary_search` in the FrUdk worker are exercised at both ends.
`VerifyCatalogPrePrunesByPatchLevel` asserts both branches.
`VerifyCatalogAndExplicitDisabledChangesCombine` covers the union of explicit
`DisabledChanges` and the catalog-pruned list. Tests use the 1-arg `IsChangeEnabled<id>()`
form because the worker no longer compares per-callsite patch versions.

### Notable engineering details

* **`Apply()` patch-level guard.** Both `PatchLevel1` / `PatchLevel2` branches are guarded
  with `(Major != 0 || Minor != 0 || Patch != 0)` so a default-initialized
  `WindowsAppRuntimeVersion {0,0,0}` does not collapse `runtimePatchLevel` to `0` in
  dev builds (where `WINDOWSAPPSDK_RELEASE_MAJOR / MINOR = 0 / 0`). Without this guard
  every dev-build test that does not explicitly set a patch level would behave as if the
  app had pinned to `0.0.0`, defeating the catalog tests.
* **`config.patchVersion` is an opaque pass-through.** `Apply` computes the effective
  patch as a WASDK-owned `WinAppSDKPatchVersion runtimePatchLevel`, walks the catalog
  against it, then mirrors the resolved value into the ABI-locked
  `WinAppSDKRuntimeConfiguration::patchVersion` field via
  `static_cast<WinAppSDKPatchVersionDeprecated>(static_cast<UINT32>(runtimePatchLevel))`.
  FrUdk's `Containment_GetChangeEnabled` no longer reads the field, but
  `Containment_SetConfiguration` still uses it as part of the identity check that
  detects attempts to apply a divergent configuration twice from the same process.
* **Scoped WASDK enum to prevent name collision.** Both FrUdk's
  `WinAppSDKPatchVersionDeprecated` and WASDK's `WinAppSDKPatchVersion` would otherwise
  define `WinAppSDK_3_0_0` etc. in the same TU. WASDK's `enum class` qualification
  (`WinAppSDKPatchVersion::WinAppSDK_3_0_0`) keeps them disjoint while preserving the
  natural reading at the catalog call sites.
* **`ContainmentTestInitialize` is resolved via `GetModuleHandleW` / `GetProcAddress`,
  not via a static import.** `RuntimeCompatibilityOptions::Apply` runs in the
  framework-package copy of `Microsoft.WindowsAppRuntime.dll` loaded by the bootstrap.
  The catalog globals live in that same module instance, so the test must call
  `ContainmentTestInitialize` on that DLL handle — a static import would resolve to a
  test-folder copy with its own (production) catalog and the catalog swap would have no
  observable effect.
* **Delay-load on `Microsoft.WindowsAppRuntime.dll`.** Linking the test against
  `Microsoft.WindowsAppRuntime.lib` brings in an implicit static import for
  `ContainmentTestInitialize`. `<DelayLoadDLLs>Microsoft.WindowsAppRuntime.dll</DelayLoadDLLs>`
  plus `delayimp.lib` defers that resolution until the bootstrap has loaded the
  framework-package copy. The benign `LNK4199 ... no imports found` warning emitted today
  is the desired state and confirms the cleanup; the directive is left in place as
  defensive cover against future regressions.

## Open follow-ups

* Telemetry on `Apply` — log every catalog-disabled and explicitly-disabled change ID so
  the customer-impact distribution becomes observable. Tracked in `// TODO: Telemetry!` in
  `RuntimeCompatibilityOptions.cpp`.
