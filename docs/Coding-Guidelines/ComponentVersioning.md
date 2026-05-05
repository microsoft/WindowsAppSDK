# Component Versioning Across Channels

> **Status:** Interim policy. Active until the WindowsAppSDK monobuild
> ([`OS/WinAppSDK`](https://microsoft.visualstudio.com/OS/_git/WinAppSDK)
> branch `release/main`) cuts over and the unified
> `WindowsAppSDKVersionPinned` versioning scheme is in production for every
> channel.
>
> **Audience:** WindowsAppSDK component owners (Foundation, WinUI, DCPP,
> DWriteCore, AIFabric, windows-ml, Widgets, WindowsAppSDKClosed) and the
> Aggregator and release-engineering teams.

This guideline supplements the SemVer scheme described in
[`specs/Deployment/WindowsAppSDKVersioning.md`](../../specs/Deployment/WindowsAppSDKVersioning.md).
That spec covers Major / Minor / Patch semantics for the public WindowsAppSDK
release. This document covers the additional rules required to keep the
*aggregate* WindowsAppSDK NuGet metapackage upgradable while the underlying
component packages are still produced in independent repos.

---

## 1. The invariant

> **An aggregate WindowsAppSDK upgrade must never contain a component package
> downgrade.**

Every component package version contained in version *N+1* of the
WindowsAppSDK metapackage must be greater than or equal to the version of
that same component contained in version *N*, on every channel a customer
might transition through (Experimental → Preview → Stable, and any pair-wise
combination thereof).

NuGet enforces this strictly: a `<PackageReference>` upgrade that would
reduce *any* transitive package's version is treated as a downgrade, emits
NU1605, and — for C++ projects — typically requires the customer to manually
uninstall and reinstall packages. That experience is unacceptable as a
recurring outcome.

---

## 2. Why this is hard today

WindowsAppSDK is currently assembled from ~10 component repos. Each
component computes its own package version, most often via
[Nerdbank.GitVersioning](https://github.com/dotnet/Nerdbank.GitVersioning)
("nbgv") which derives the patch number from git height on the *current*
branch. The Aggregator pulls the latest published transport package from
each component and re-emits the WindowsAppSDK metapackage.

Three properties combine into a race condition:

1. **Per-branch counters.** Experimental and stable/servicing branches
   advance independently. Their patch counters are not coordinated.
2. **Independent build cadences.** Component teams ship to their channels on
   their own schedules; Aggregator pulls "the latest of each".
3. **Interleaved aggregate releases.** Experimental and stable WindowsAppSDK
   metapackages are produced close in time, sometimes the same day.

The failure mode that pushed this guideline:

> WinML's `release/2.0-stable` branch emits `2.0.<patch>` and the
> experimental branch emits `2.0.<patch>-experimental`. Both branches keep
> advancing, so experimental's patch number leapfrogged stable's:
> `2.0.325-experimental` is *higher* than `2.0.300` under NuGet SemVer.
> Customers (especially C++ projects) saw the stable upgrade as a
> *downgrade* in Visual Studio, with the associated warnings and restore
> failures.

The same shape of bug shows up any time component A is built later than
component B on the experimental channel and earlier than B on the stable
channel — even if every individual team is acting reasonably.

---

## 3. Approaches we explicitly rejected

These were considered and rejected in the *Addressing semver concerns for
contributor teams* meeting:

- **Bump Minor on every stable release.** Misrepresents SemVer (Minor is
  reserved for new functionality from the previous Stable release; see
  [`WindowsAppSDKVersioning.md`](../../specs/Deployment/WindowsAppSDKVersioning.md)),
  and *guarantees* a downgrade when a customer moves Experimental → Stable
  if Experimental was already on the higher Minor.
- **Let Experimental sit on a higher Minor than Stable.** Guarantees a
  downgrade on every Experimental → Stable channel transition.
- **Encode channel into any SemVer field.** Version numbers describe API
  shape, not release channel. Channel is conveyed by the SemVer pre-release
  tag (e.g. `-experimental2`, `-preview1`); the numeric fields must remain
  truthful.

---

## 4. Short-term policy (until monobuild cutover)

Until the unified versioning scheme in section 5 is in production,
**component teams are responsible for guaranteeing monotonic component
package versions across every channel they ship into.** The system does not
enforce this yet; developers must.

### 4.1 Rules for component owners

1. **No automated per-branch counter without a coordinated baseline.** If
   you use nbgv, GitHub-counter actions, or any other scheme that derives a
   version from per-branch state, you **must** ensure the resulting numbers
   are monotonically increasing across all of your channels. The simplest
   reliable mechanism is a fixed-height baseline on stable branches:

   ```jsonc
   // version.json on a stable/release branch
   {
     "version": "2.0",
     "versionHeightOffset": 1000  // baseline bump applied at branch creation
   }
   ```

   This is the pattern used on earlier release branches ("trivial to
   annotate `version.json` to add a fixed height baseline") and the pattern
   shipped for WinML in
   [PR #15417125 *Fix 2.0 nerdbank versioning*](https://microsoft.visualstudio.com/OS/_git/WinAppSDK/pullrequest/15417125)
   to recover from the `2.0.325-experimental` > `2.0.300` collision.

2. **Stable on a given Minor is always "newer" than Experimental on that
   Minor.** Choose your offset large enough that no foreseeable experimental
   git-height advance can cross it. (The team has used `+1000` historically
   on a per-component basis; the central monobuild scheme uses `+8000` on
   the Singleton package's Major to maintain monotonicity across the
   1.x → 2.x transition — same idea, applied centrally.)

3. **Manual overrides are expected.** If your tooling cannot guarantee
   monotonicity for a given release, it is acceptable — and expected — to
   set the version by hand or to disable the automated tool for that
   release. WinUI and Foundation are already operated this way today.

4. **Pre-release pre-flight check.** Before tagging a release, verify your
   component's next version is strictly greater than the last published
   version on **every** channel you target (NuGet feed query against the
   latest stable, latest preview, and latest experimental of your package).

### 4.2 Rules for the Aggregator team

1. **Pre-publish downgrade check.** Before publishing a new aggregate
   metapackage, compare each component's pinned version to the same
   component's version in the most recent published metapackage on the
   target channel **and** the adjacent channels customers are likely to
   transition from. Block publish on any downgrade.
2. **Hold the line on policy.** Do not work around a component downgrade by
   re-pinning to an older transport package. Push the violation back to the
   component team to resolve at source.

### 4.3 Rules for release management

- **Stable / servicing RC builds always precede experimental RC builds**
  when both are scheduled on the same day (or close together). Component
  owners may rely on that sequencing as a hard guarantee when computing
  their component versions: if their component participates in both an
  experimental and a stable/servicing aggregate release in the same
  window, the stable/servicing build will be the *earlier* one, so any
  per-channel counter advances applied for the experimental build cannot
  retroactively cause the stable build to ship a lower component version.

---

## 5. Long-term: the `WindowsAppSDKVersionPinned` unified scheme

The monobuild on
[`OS/WinAppSDK` `release/main`](https://microsoft.visualstudio.com/OS/_git/WinAppSDK?version=GBrelease/main)
removes the race condition by construction. Authoritative references:

- [`CopilotBrain/Docs/Mono-Build-Pipeline-Migration.md` §9 *Version Management*](https://microsoft.visualstudio.com/OS/_git/WinAppSDK?path=/CopilotBrain/Docs/Mono-Build-Pipeline-Migration.md&version=GBrelease/main&_a=preview&anchor=9.-version-management)
  (the unified versioning strategy, including the
  `WindowsAppSDKVersionPinned` mechanism)
- [`Build/WindowsAppSDK/AzurePipelinesTemplates/WindowsAppSDK-Versions.yml`](https://microsoft.visualstudio.com/OS/_git/WinAppSDK?path=/Build/WindowsAppSDK/AzurePipelinesTemplates/WindowsAppSDK-Versions.yml&version=GBrelease/main)
- [`Src/Components/WindowsAppSDKAggregator/docs/Coding-Guidelines/Dependencies.md`](https://microsoft.visualstudio.com/OS/_git/WinAppSDK?path=/Src/Components/WindowsAppSDKAggregator/docs/Coding-Guidelines/Dependencies.md&version=GBrelease/main)

### 5.1 One version, stamped centrally

Every monobuild pipeline run computes a single `$(WindowsAppSDKVersion)` at
the top from:

- `MajorVersion` and `MinorVersion` in
  `Src/Components/WindowsAppSDKConfig`,
- `AggregatePatchVersion` from the
  `WinAppSDK-<Major>-Versions` Variable Group (reset when
  `AggregateMinorVersion` changes), and
- a channel-specific revision counter — `ExperimentalRevision`,
  `PreviewRevision`, or `PRNightlyRevision` — selected by the build's
  `BuildType` and `PrOrNightly` parameters.

That one version is stamped on every component the build produces. No
component computes its own version from local git state.

### 5.2 The pinning mechanism

The monorepo-root `Directory.Packages.props` is the
"MasterSourceOfTruth(TM)" for package versions. Internal packages are
declared with a `ValueOrDefault` expression so they float `2.*` by default
and pin to an exact version when the pipeline asks them to:

```xml
<PackageVersion Include="Microsoft.WindowsAppSDK.Foundation.TransportPackage"
                Version="$([MSBuild]::ValueOrDefault('$(WindowsAppSDKVersionPinned)', '2.*'))" />
<PackageVersion Include="Microsoft.WindowsAppSDK.Base"
                Version="$([MSBuild]::ValueOrDefault('$(WindowsAppSDKVersionPinned)', '2.*'))" />
<!-- ...one entry per internal transport package... -->
```

| Pipeline type   | `WindowsAppSDKVersionPinned`                | Internal packages resolve as |
| --------------- | ------------------------------------------- | ---------------------------- |
| CI / PR / local | *unset*                                     | `2.*` (latest from feed)     |
| Official        | `/p:WindowsAppSDKVersionPinned=$(WindowsAppSDKVersion)` | exact version from this run |
| Nightly         | `/p:WindowsAppSDKVersionPinned=$(WindowsAppSDKVersion)` | exact version from this run |

Nothing rewrites `Directory.Packages.props` on disk; MSBuild evaluates
`$(WindowsAppSDKVersionPinned)` at restore time. Inter-stage resolution
within the pipeline pulls each transport package from a local artifact
directory at exactly that pinned version.

### 5.3 Why this kills the race condition

Every component is stamped with the same version at the same instant by the
aggregator. Per-branch counters in component repos can no longer leapfrog
across channels because component repos no longer compute the version that
ships. Channel ordering becomes a property of `AggregatePatchVersion` and
the channel revision counter — both centrally maintained — instead of a
property of where each component's branch happened to be at build time.

The `Singleton` package's existing `Major + 8000` offset (used to keep
monotonicity across the 1.x → 2.x transition) is the same mechanical idea
as the per-component baseline bumps in §4.1, applied once, centrally.

### 5.4 Floating release symbols for runtime compatibility checks

Component code that needs to gate behavior on "the WindowsAppSDK release
this change shipped in" — for example, runtime compatibility shims,
`TerminalVelocity`-style change-ID checks, or feature-availability
guards — has historically required the contributor to *anticipate* the
exact version their change would land in (for example, hardcoding
`2.1.0` into a check at the time the PR is authored). That anticipation
is fragile: the actual release version is determined by the aggregator at
build time, not by the contributor at PR time.

After the monobuild cutover, the recommended pattern is to declare a
**floating release symbol** alongside the change-ID and let the monobuild
resolve it to a concrete version at build time:

```cpp
// Contributor authors this — no version anticipated, just a milestone alias.
#define WINAPPSDK_CHANGEID_12345678 12345678, WinAppSDK_2_Servicing
```

The monobuild then defines the milestone alias (for example,
`WinAppSDK_2_Servicing`) at the top of the build to resolve to the
concrete release version that build is producing — for example,
`2.1.0` — and propagates that definition to every component being
compiled. Build-time resolution looks like:

| Build context                         | `WinAppSDK_2_Servicing` resolves to |
| ------------------------------------- | ----------------------------------- |
| Aggregator official build for 2.1.0   | `2.1.0`                             |
| Aggregator official build for 2.1.1   | `2.1.1`                             |
| Pre-release / dev / nightly           | the in-flight version for that run  |

**Why this matters for cross-channel monotonicity.** Contributors no
longer need to predict which aggregate version their change will appear
in, which means change-ID gating no longer races against the aggregator's
version assignment. The version a change lights up in is a property of
the build that contains it — exactly like the package version stamping in
§5.1 — so the same "central stamping" guarantee that eliminates the
component-package-downgrade race in §5.3 also eliminates the
contributor-anticipated-version mismatch for runtime compatibility checks.

A small set of well-known milestone aliases (e.g. `WinAppSDK_2_Servicing`,
`WinAppSDK_2_Next`, `WinAppSDK_2_Experimental`) is preferred over
ad-hoc literals so the aggregator has a closed set of symbols to define.
The exact catalog of aliases will be defined alongside the monobuild
rollout.

---

## 6. Decisions captured

From the *Addressing semver concerns for contributor teams* meeting and the
WinAppSDK DevOps thread *WinML stable vs experimental version ordering*
(parent message
[`1776980671194`](https://teams.microsoft.com/l/message/19:eb09f4ee918e4093a728d6f23360a3f9@thread.tacv2/1776980671194?tenantId=72f988bf-86f1-41af-91ab-2d7cd011db47&groupId=ee35a9bc-e7bf-4b45-ae2d-cd4de9c11b95&parentMessageId=1776980671194&teamName=WinAppSDK&channelName=WinAppSDK%20DevOps),
Apr 23 2026):

- ✅ Do not encode release channel semantics into SemVer numeric fields.
- ✅ Component versions must monotonically increase across all channels.
- ✅ Manual coordination is required until monobuild.
- ✅ When experimental and stable/servicing aggregate RC builds are
  scheduled close together, **stable/servicing always builds first** so
  component owners have a predictable sequencing to plan against.
- ✅ The `WindowsAppSDKVersionPinned` monobuild scheme is the definitive
  long-term solution.

---

## 7. Action items and ownership

| Owner                         | Action                                                                                                       |
| ----------------------------- | ------------------------------------------------------------------------------------------------------------ |
| Component teams               | Implement and document the §4.1 monotonic-versioning rules for your component; baseline-bump release branches at creation. |
| Component versioning lead     | Own the cross-component versioning story; communicate this guideline to all component teams.                 |
| Aggregator team               | Implement the §4.2 pre-publish downgrade check.                                                              |
| Release management            | Enforce the §4.3 sequencing rule: stable/servicing aggregate RC builds always precede experimental RC builds when scheduled close together. |
| Monobuild team                | Land `WindowsAppSDKVersionPinned` in production; deprecate this interim guideline once the cutover is complete. |

---

## 8. References

- [`specs/Deployment/WindowsAppSDKVersioning.md`](../../specs/Deployment/WindowsAppSDKVersioning.md) — Major/Minor/Patch policy.
- [`specs/Deployment/MSIXPackageVersioning.md`](../../specs/Deployment/MSIXPackageVersioning.md) — MSIX package versioning.
- [`specs/VersionInfo/VersionInfo.md`](../../specs/VersionInfo/VersionInfo.md) — runtime version-info APIs.
- [PR #15417125 *Fix 2.0 nerdbank versioning*](https://microsoft.visualstudio.com/OS/_git/WinAppSDK/pullrequest/15417125) — WinML baseline-bump implementation.
- Monobuild docs on `OS/WinAppSDK` `release/main`:
  - [`CopilotBrain/Docs/Mono-Build-Pipeline-Migration.md` §9 *Version Management*](https://microsoft.visualstudio.com/OS/_git/WinAppSDK?path=/CopilotBrain/Docs/Mono-Build-Pipeline-Migration.md&version=GBrelease/main&_a=preview&anchor=9.-version-management)
  - [`Build/WindowsAppSDK/AzurePipelinesTemplates/WindowsAppSDK-Versions.yml`](https://microsoft.visualstudio.com/OS/_git/WinAppSDK?path=/Build/WindowsAppSDK/AzurePipelinesTemplates/WindowsAppSDK-Versions.yml&version=GBrelease/main)
  - [`Src/Components/WindowsAppSDKAggregator/docs/Coding-Guidelines/Dependencies.md`](https://microsoft.visualstudio.com/OS/_git/WinAppSDK?path=/Src/Components/WindowsAppSDKAggregator/docs/Coding-Guidelines/Dependencies.md&version=GBrelease/main)
  - [`CopilotBrain/Docs/WASDK-Branching-Patterns-and-Release-Flows.md`](https://microsoft.visualstudio.com/OS/_git/WinAppSDK?path=/CopilotBrain/Docs/WASDK-Branching-Patterns-and-Release-Flows.md&version=GBrelease/main)
  - [`CopilotBrain/Docs/Maestro-Anti-Patterns-Pitfalls.md`](https://microsoft.visualstudio.com/OS/_git/WinAppSDK?path=/CopilotBrain/Docs/Maestro-Anti-Patterns-Pitfalls.md&version=GBrelease/main)
