- [1. Background](#1-background)
  - [1.1. Scope](#11-scope)
  - [1.2. Terminology](#12-terminology)
    - [1.2.1. Project Reunion vs Windows App SDK](#121-project-reunion-vs-windows-app-sdk)
    - [1.2.2. Version Number = MSIX](#122-version-number--msix)
    - [1.2.3. Windows App SDK's MSIX Packages](#123-windows-app-sdks-msix-packages)
    - [1.2.4. Binary Compatibility](#124-binary-compatibility)
    - [1.2.5. Source Compatibility](#125-source-compatibility)
  - [1.3. Impacted Components](#13-impacted-components)
  - [1.4. MSIX and SemVer](#14-msix-and-semver)
  - [1.5. Dynamic Dependencies](#15-dynamic-dependencies)
  - [1.6. Windows App SDK Versioning Requirements](#16-windows-app-sdk-versioning-requirements)
- [2. Decisions](#2-decisions)
  - [2.1. Decision 1: Breaking Change Boundary for Version 0.*](#21-decision-1-breaking-change-boundary-for-version-0)
  - [2.2. Decision 2: Breaking Change Boundary for Version 1.x](#22-decision-2-breaking-change-boundary-for-version-1x)
    - [2.2.1. Current practices in Microsoft-authored Framework packges.](#221-current-practices-in-microsoft-authored-framework-packges)
  - [2.3. Decision 3: Release Tags (Stable, Preview, ...)](#23-decision-3-release-tags-stable-preview-)
  - [2.4. Decision 4: Version Encoding](#24-decision-4-version-encoding)
    - [2.4.1. Windows App SDK 0.5 Notation](#241-windows-app-sdk-05-notation)
    - [2.4.2. WinUI 2.x Notation](#242-winui-2x-notation)
  - [2.5. Decision 5: Package Names](#25-decision-5-package-names)
- [3. Conclusions](#3-conclusions)

# 1. Background

This document answers the question: "How are MSIX and Dynamic Dependencies defined and implemented
to meet versioning requirements for Windows App SDK 0.8 through 1.x?"

This document defines how Windows App SDK packages are named and versioned.

## 1.1. Scope

This decision focuses on install- and run-time beyond 0.5 and,
in particular, MSIX and Dynamic Dependencies in 0.8 and 1.x.

Development- and build-time issues are out-of-scope for this decision. Windows App SDK's
requirements for dev- and build-time and how NuGet, VISX and other tech are handled do not
impact this decision.

As this spec is focused on install- and run-time it results in a stance on binary compatibility.
Source compatibility is only significant at development- and build-time so a decision on source
compatibility is out-of-scope for this decision.

## 1.2. Terminology

### 1.2.1. Project Reunion vs Windows App SDK

This document defines the MSIX versioning details for version 0.8 thru 1.x.

The project went thru a name change from "Project Reunion" in 0.8 to "Windows
App SDK" in 1.0. Artifact names are kept historically accurate. Textual prose
has been updated to use the new "Windows App SDK" name for consistency, even
when referring to earlier versions.

Similarly, examples may cite ProjectReunion but the same logic applies to 1.x despite name changes.

### 1.2.2. Version Number = MSIX

SemVer defines a version number as `MAJOR.MINOR.PATCH[-prerelease][+build]`.

MSIX defines a version number as `Major.Minor.Build.Revision`.

To avoid ambiguity this document uses MSIX's definition and terms unless stated otherwise.

### 1.2.3. Windows App SDK's MSIX Packages

Windows App SDK 0.5 has 1 MSIX package: `Microsoft.ProjectReunion.0.5` aka WARfwk (formerly PRfwk).
This contains the vast majority of Windows App SDK.

Windows App SDK 0.8 has 3 MSIX packages

* `Microsoft.WindowsAppRuntime` aka **WARfwk**
* `Microsoft.WindowsAppRuntime.Main` aka **WARmain**
* `Microsoft.WindowsAppRuntime.DDLM` aka **WARddlm**

WARmain and WARddlm supplement WARfwk to do things a Framework packge can't (e.g. Packaged COM).
See the [Dynamic Dependencies spec](https://github.com/microsoft/WindowsAppSDK/blob/main/specs/dynamicdependencies/DynamicDependencies.md)
and [Windows App SDK: MSIX Packages](https://github.com/microsoft/WindowsAppSDK/blob/main/specs/Deployment/MSIXPackage.md)
for more details.

Windows App SDK 1.0 has 4 MSIX packages

* `Microsoft.WindowsAppRuntime` aka **WARfwk**
* `MicrosoftCorporationII.WinAppRuntime.Main` aka **WARmain**
* `MicrosoftCorporationII.WinAppRuntime.Singleton` aka **WARsingleton**
* `Microsoft.WinAppRuntime.DDLM` aka **WARddlm**

WARsingleton supplements WARmain to provide a mechanism for features needing singular global
behavior across all versions of Windows App SDK. See [Windows App SDK: MSIX Packages](https://github.com/microsoft/WindowsAppSDK/blob/main/specs/Deployment/MSIXPackage.md)
for more details.

### 1.2.4. Binary Compatibility

**"Binary Compatibility"**: Existing, compiled code can rely on new version of compiled library code
without change, and expect to run without issue. Binary compatibility relies on a strong contract
between the library and caller including both the shape and behavior of the API.

If an application relies on unspecified behavior, intentionally or otherwise, binary compatibility
can be hard to maintain. Nonetheless, Windows has demonstrated that it is possible, with effort, to
maintain a high degree of binary compatibility over an extended period of time.

### 1.2.5. Source Compatibility

**"Source Compatibility"**: The version of the library can be changed, and the code will build
without issue.

In practice, perfect source compatibility is unachievable in most programming languages. E.g.
"using" statements can lead to name collisions when a library introduces new types. In contrast, a
project that does not commit to source compatibility may require significant code changes when
building with later versions, due to changes in the public surface area of the API.

## 1.3. Impacted Components

[Dynamic Dependencies](https://github.com/microsoft/WindowsAppSDK/blob/main/specs/dynamicdependencies/DynamicDependencies.md),
[ProjectReunionInstaller.exe](https://github.com/microsoft/WindowsAppSDK/issues/443) and the build
pipeline are not currently in sync. Work is required (regardless the
decision) to align on a common solution.

Demos, samples, documentation, functional testing and E2E integrated testing are impacted.

## 1.4. MSIX and SemVer

MSIX's versioning model overlaps with SemVer but isn't fully compatible. See [here](https://github.com/microsoft/WindowsAppSDK/issues/148) for more details.

## 1.5. Dynamic Dependencies

Windows App SDK's DynamicDependencies (DynDep) relies on an elegant dance with Windows' inbox
behavior to provide the expected outcome (without servicing Windows). This requires a deep
understanding of MSIX's behavior and Windows App SDK's versioning model to correctly identify and
select the appropriate Windows App SDK framework package (aka WARfwk) at runtime. More details are
available [here](https://github.com/microsoft/WindowsAppSDK/blob/main/specs/dynamicdependencies/DynamicDependencies.md).

Dynamic Dependencies support is being added to Windows, aka OS DynDep. Care has been taken to keep
WinAppSDK+OS behavior aligned to facilitate eventual use and migration from Windows App SDK's
implementation to Windows'. OS DynDep provides a richer, more efficient and reliable solution with
less developer friction than WinAppSDK DynDep. We will eventually polyfill WinAppSDK DynDep's
implementation to use OS DynDep when available and (someday) rely entirely on OS DynDep when
downlevel support is no longer relevant.

## 1.6. Windows App SDK Versioning Requirements

Windows App SDK's versioning model has been discussed in detail but not documented in one place.
This spec pulls together that disparate information into a unified whole.

The versioning meta-requirements are briefly summarized here:

* Require no Windows servicing
* Support [Semantic Versioning (SemVer)](https://semver.org/)
* Support a clear division of incompatibility (Breaking Change) across major/disruptive releases
* Support servicing across minor/less-disruptive releases
* Support critical servicing e.g. MSRC security fixes
* Support packaged and unpackaged apps
* Support multiple tags of 'release' (Stable, Preview, ...) aka Channels
* Be implementable across our key technologies including Dynamic Dependencies, NuGet, MSIX, MS Store and VSIX
* Support WinAppSDK DynDep leveraging OS DynDep (in future Windows versions) via polyfill (initially where available, eventually 100%)

These requirements need careful balance and multiple mechanisms to meet them all. This spec focuses
on install- and run-time needs, specifically MSIX and Dynamic Dependencies (DynDep) for unpackaged
apps.

The versioning solution used in 0.5 is insufficient for Windows App SDK's support for
unpackaged apps (e.g. MSIX naming patterns don't work for the DynamicDependency Lifetime Manager
(DDLM) package). See section 2. Decisions for more details. Past decisions are incorporated to the
extent possible but additions and changes are needed.

Packaged apps bring a subset of requirements vs unpackaged apps so this decision is expected to
work equally well for packaged apps.

MS Store brings similar needs and constraints as MSIX so this decision is expected to work equally
well for MS Store distribution.

# 2. Decisions

Current versioning design and practice has some areas of ambiguity or gaps for new scenarios (e.g.
unpackaged apps). These issues are noted with solutions and the recommended path forward.

Jump ahead to [3. Conclusions](#3-conclusions) to skip the alternatives considered,
detailed explanations and why the recommended solutions are chosen.

## 2.1. Decision 1: Breaking Change Boundary for Version 0.*

Per [SemVer section 4](https://semver.org/#spec-item-4)

> Major version zero (0.y.z) is for initial development. Anything MAY change at any time. The public
API SHOULD NOT be considered stable.

There's no mention if this requires or assumes any technical enforcement.

This does not guarantee incompatibility across version 0.y.z but it doesn't guarantee compatibility
either. Windows App SDK defines specific rules for Windows App SDK to address this ambiguity.

**Option A: MSIX package Name includes `Major.Minor.Build` if `Major=0`**. Servicing can be done
via changes to `.Revision` e.g. `Microsoft.ProjectReunion.0.8.0` for version 0.8.0.0.

Servicing (bugfix) increment the `.Build` value e.g. 0.8.1.0, 0.8.2.0, etc with package Name
`Microsoft.ProjectReunion.0.8.1` etc. Applications are required to rebuild to use the update at
runtime.

MSRC updates would be 0.8.0.1, 0.8.0.2, 0.8.1.1, etc. Applications always use MSRC updates on a
system matching their `Major.Minor.Build`.

**Option B: MSIX package Name includes `Major.Minor` if `Major=0`**. Servicing can be done via
changes to `.Build` and `.Revision` e.g. Project `Microsoft.ProjectReunion.0.8` for version 0.8.0.0.

Servicing (bugfix) increment the `.Build` value e.g. 0.8.1.0, 0.8.2.0, etc with package Name
`Microsoft.ProjectReunion.0.8.1` etc. Applications use the latest update on a system
matching their `Major.Minor`. No rebuild is necessary. Applications cannot block running with
servicing updates.

MSRC updates would be 0.8.0.1, 0.8.0.2, 0.8.1.1, etc. Applications always use MSRC updates on a
system matching their `Major.Minor`.

**Option C: Never make MSIX Framework packages with version `Major=0`**.

Deployment does not support SemVer section 4. Deployment doesn't treat version 0 different than any
other version. If Deployment finds multiple applicable packages satisfying a dependency it chooses
the highest version (per `VersionSupercedence`<sup>1</sup>).

<sup>1</sup> VersionSupercedence can be defeated in very narrow cases e.g. Packages installed with
[DeploymentOptions.ForceUpdateFromAnyVersion](https://docs.microsoft.com/uwp/api/Windows.Management.Deployment.DeploymentOptions?view=winrt-19041)
are always used, even if a lower version than other applicable packages. Other exotic cases exist but
the overwhelming norm without exception is 'highest version wins'.

***Recommendation:*** Option B.

This provides for rapid evolution balanced with stability for supported use.

## 2.2. Decision 2: Breaking Change Boundary for Version 1.x

SemVer defines the binary incompatibility (breaking change) boundary as the MAJOR version.

MSIX defines the binary incompatibility (breaking change) boundary as the package family. The
version number has no inherent binary incompatibility boundary but one can vary package family name
to provide an incompatibility boundary. We can include as much (or little) of the version number in
the package Name as we desire to provide a compatibility boundary.

**Option A: Incompatibility boundary is the `Major` version**

* Aligns with SemVer
* Compatible with MSIX
* Aligns with common practices and expectations across the industry (glibc, Linux kernel, many more)

Chrome and Edge are clear examples of Option A. Stable Chrome and Edge releases are currently
version 89 and 92+ are under development.

**Option B: Incompatibility boundary is the `Major.Minor` version**

* Does not align with SemVer
* Compatible with MSIX
* Aligns with some practices and expectations across the industry

**Option C: Incompatibility boundary is the `Major.Minor.Build` version**

* Does not align with SemVer
* Compatible with MSIX
* Does not align with common practices and expectations across the industry

***Recommendation:*** 
For all 1.x, option B was selected, while waiting on tooling to be able to handle the rapid development we want.

## Decision 2.1: Breaking Change for version 2.x
Starting 2.x, option A is selected. This will allow for better stability for external developers. They will 
know that as long as they are on the same Major, then things will be compatible.

### 2.2.1. Current practices in Microsoft-authored Framework packges.

There is no consistency of version in package Name amongst existing Framework packages. Per
`powershell -c "$(get-appxpackage -packagetypefilter framework).packagefamilyname|sort"` one can see
some of the more common frameworks:

* None: Microsoft.Advertising.JavaScript, Microsoft.Advertising.Xaml, Microsoft.DirectXRuntime, Microsoft.Media.PlayReadyClient, Microsoft.Services.Store.Engagement
* Minor: Microsoft.NET.CoreRuntime, Microsoft.NET.Native.Framework, Microsoft.NET.Native.Runtime, Microsoft.UI.Xaml, Microsoft.VCLibs, Microsoft.WinJS

VCLibs sometimes goes further with additional qualifiers in their Name including: .debug, .Universal, .UWPDesktop.

No version in Name implies the framework has yet to produce a breaking change, i.e. in SemVer-speak
these frameworks are still MAJOR=X and yet to produce MAJOR=X+1.

## 2.3. Decision 3: Release Tags (Stable, Preview, ...)

How do we distinguish release across channels, e.g. a 'Stable' package from a 'Preview' package?

Windows App SDK 0.5 adds a "-preview" tag to the package Name.

Windows App SDK 1.x adds a -channel# tag (e.g. "-preview1") to the package name.

Windows App SDK 2.x goes back to just a "-preview" tag on the package Name.

***Shorter Tags as needed*** "-preview" adds 8 characters to package Name. "-experimental" adds
12 characters. Package Name is restricted to 50 characters maximum.

**Option A: `-preview`**
**Option B: `-pre`**
**Option C: `-p`**

These may optionally include a trailing digit indicating the Nth release of a channel for a version
of the project.

***Recommendation:*** Option A and C (when necessary).

All tags have a long name (Option A) and a short (1-2 characters) name (Option C).

Option C is used when Option A doesn't work due to package Name length restrictions.
Currently WARddlm is the only instance using Option C.

## 2.4. Decision 4: Version Encoding

What data's encoded in the MSIX Version, and how?

The following notation is used to describe the possible options

* X = Major version
* N = Minor version
* P = Patch (per SemVer definition i.e. the 3rd field in a version)
* Y = Year
* M = Month
* D = Day
* E = Elapsed days since an epoch e.g. if Epoch=2021/01/01 then 2021/6/4=154
* B = Build number (reset to zero when Major or Minor changes)
* 0 = Zero

Single character indicates variable-length without leading zeros.
Multiple characters indicates fixed-length with leading zeroes if necessary. For example, Y=1 vs YY=01.

NOTE: MSIX version's 4th field (Revision) is reserved for security updates.

Examples are provided for the following theoretical versions...
* Windows App SDK 0.8.1, date=2021/6/4, build=123, elapsed=154
* Windows App SDK 1.2.3, date=2021/12/31, build=123, elapsed=364
* Windows App SDK 17.14.3, date=2031/10/20, build=123, elapsed=3944

|Option|Syntax|Example|Information|Comments|
| --- | :--- | :---: | :---: | :---: |
|A|X.N.P.0|0.8.1.0<br>1.2.3.0<br>17.14.3.0|Major Minor Patch||
|B|X.NYYMM.DDPPP.0|0.82106.04001.0<br>1.22112.31003<br>--error--|Major Minor Patch Date|Minor max is 6<br>Patch max is 999<br>WinUI 2.x used this encoding<br> Windows App SDK 0.5 used this encoding|
|C|XNN.PYYMM.DDBBB.0|8.12106.04123.0<br>102.32112.31123.0<br>1714.33110.20123.0|Major Minor Patch Date Build|Minor max is 99<br>Patch max is 6<br>Build max is 999|
|D|NPPP.E.B.0|8001.154.123<br>2003.364.123<br>17014.3944.123.0|Minor Patch Elapsed Build|Minor max is 64<br>Patch max is 999<br>Build max is 65535|
|E|NPP.E.B.0|801.154.123<br>203.364.123<br>1714.3944.123.0|Minor Patch Elapsed Build|Minor max is 99<br>Patch max is 99<br>Build max is 65535|

***Recommendation:*** 
For 1.x, Option D was selected.
For 2.x, Option A is selected.

Option A works is the simplest to release and understand. As long as we don't hit 999 Patches for the same Major.Minor,
then we will not run out of space in the DDLM package (more on that in 2.5)

Option B worked for WinUI 2.x and Windows App SDK 0.5 but is too limiting given it can't support
Minor versions beyond 6. It's also a complicated encoding scheme with date injected between Minor
and Patch (not readily legible).

Option C is too limiting given it can't support Patch versions beyond 6.

Option D relies on the package Name including Major version. This leaves sufficient space in the
version to encode up to 99 Minor and 99 Patch versions. Date encoding as an Epoch reduces the size
while supporting 20+ years with only 4 digits.

Option E is a variant of Option D except Patch version is restricted to 2 digits, but it's an
unnecessary simplification.

### 2.4.1. Windows App SDK 0.5 Notation

Windows App SDK 0.5 encodes MSIX versions as `M.NYYMM.DDPPP.0`

* M = Major version
* N = Minor version
* YY = Year
* MM = Month
* DD = Day
* PPP = Patch

All fields are fixed-size with leading zeroes as needed. For example, Windows App SDK 0.5.0's MSIX package has a version of `0.52103.25000.0`

* Major = 0
* Minor = 5
* Year = 21 (aka 2021)
* Month = 03
* Day = 25
* Patch = 000 (if we have a 0.5.1 release this would be `001`)

This doesn't scale going forward e.g. MSIX version is a DotQuadNumber aka `uint16[4]`. If 0.8 was
released on May'31, 2021 MSIX version would be `0.82105.31000.0`

### 2.4.2. WinUI 2.x Notation

WinUI 2.x encodes MSIX versions as `M.NYYMM.DDPPP.0` (same as Windows App SDK 0.5). This runs into
issues starting with WinUI 2.7, as identified by [WinUI version schema sometime can't applied to
MinVersion
#4008](https://github.com/microsoft/microsoft-ui-xaml/issues/4008#issuecomment-765633788).

## 2.5. Decision 5: Package Names

Windows App SDK 0.8+ has 3 MSIX packages. We have choices for package Name patterns for 0.8 and 1.x.

Assuming Breaking Change Boundary for v0.x and v1+'s decision are `Major.Minor` version we have the
following naming patterns release 0.x...

* WARfwk: `Microsoft.WindowsAppRuntime.<rmajor>.<rminor>[-tag]`
* WARmain: `Microsoft.WindowsAppRuntime.Main.<rmajor>.<rminor>[-tag]`
* WARddlm: `Microsoft.WindowsAppRuntime.DDLM.<rmajor>.<rminor>.<build>.<revision>-<shortarchitecture>[-shorttag]`

and release 1.x...

* WARfwk: `Microsoft.WindowsAppRuntime.<rmajor>.<rminor>[-tag]`
* WARmain: `MicrosoftCorporationII.WinAppRuntime.Main.<rmajor>.<rminor>[-shorttag]`
* WARsingleton: `MicrosoftCorporationII.WinAppRuntime.Singleton[-shorttag]`
* WARddlm: `Microsoft.WinAppRuntime.DDLM.<major>.<minor>.<build>.<revision>-<shortarchitecture>[-shorttag]`

and release 2.x, when Breaking Change Boundary changed to 'Major' version...

* WARfwk: `Microsoft.WindowsAppRuntime.<rmajor>[-tag##]`
* WARmain: `MicrosoftCorporationII.WinAppRuntime.Main.<rmajor>[-shorttag##]`
* WARsingleton: `MicrosoftCorporationII.WinAppRuntime.Singleton[-shorttag##]`
* WARddlm: `Microsoft.WinAppRuntime.DDLM.<rmajor>.<rminor>.<patch>.<revision>-<shortarchitecture>[-shorttag##]`

where

* rmajor = Major version number of the project release, base-10, no leading zeros (e.g. "1" for WindowsAppSDK 1.2)
* rminor  = Minor version number of the project release, base-10, no leading zeros (e.g. "2" for WindowsAppSDK 1.2)
* patch = Patch version number of the project release, base-10, no leading zeros
* major = Major version number of the release, base-10, no leading zeros
* minor  = Minor version number of the release, base-10, no leading zeros
* build = Build version number, base-10, no leading zeros
* revision = Revision version number, base-10, no leading zeros
* architecture = Allowed values: "x86", "x64", "arm64"
* shortarchitecture = Allowed values: "x8", "x6", "a6"
* tag = Allowed values: "", "preview", "experimental"
* shorttag = Allowed values: "", "p", "e"
* "##" = the current build bumber for that release type. 2 characters long. Each caharacter could be [a-z,0-9].

**NOTE:** rmajor/rminor/patch are the release version, major/minor/build/revision are the MSIX package
version (Microsoft.ProjectReunion.0.8-preview had a release version of 0.8
but an MSIX package version of 8000.146.628.0). Starting 2.0, these will now be the same numbers. The exception to that is
Singleton, since there is one package covering all releases. That package can't "go back" to Major=2, so we will add a
8000 to the Major for that package.

Since we will now match the release version with the MSIX, it is worth explaining how that is going to increment.
* Major will increase when a stable or preview release contains Breaking Changes from the previous Stable release. This will happen 
no more than once per year.
* Minor will increase when a stable release contains new Functionality from the previous Stable release. This will happen no more than once 
per month.
* Every potential released build (stable, preview, experimental) will increase the Patch, unless the Major or Minor is increased.
No 2 builds will share the same Major.Minor.Patch version.
If we notice an issue after building a canditate (stable, preview, or experimental), we will choose not to release it, at which 
point the patch will bump again.
This means that there will be times when there is a patch number that will not be released at all.
* Note: We see experimental releases as "containing" the closest stable + some experimental stuff, rather than "previewing" what is coming. We 
do not bump the Major/Minor for experimental things because the new/breaking things will at least sometimes not be in the next stable release, 
and may even be removed before the next experimental release. 
* Preview releases are optional if we feel the need to have a preview of nearly stable things without anything currently marked experimental.
This will only happen on the next Major release before making an official stable release. When we do have a Preview build, all Previews and 
Experimental releases will be X.0.0-<pre or Exp><Num> until we release the first Stable release.

A simplified example is this:
* 2.0.0 is the first stable release.
* 2.0.1-experimental is the first experimental. (contains 2.0.0 + some exp APIs, and some bug fixes)
* 2.0.2 is the 2nd stable release. (bug fixes moved into 2)
* 2.0.3-experimental is the 2nd experimental. (contains 2.0.1 + some exp APIs, and some more bug fixes)
* 2.0.4-experimental is the 3rd experimental. (contains 2.0.1 + some Breaking Changes, some exp APIs, and some more bug fixes)
* 2.1.0 is the 3rd stable release (some of the exp APIs went stable, and some bug fixes)
* 2.1.1-experimental is the 4th experimental. (contains 2.1.0 + some Breaking Changes, and some more bug fixes)
* 3.0.0-preview1 is the preview 3 public release
* 3.0.0-experimental1 (contains 3.0.0-preview1 + some new APIs not in the preview build)
* 3.0.0-experimental2 (contains 3.0.0-preview1 + even more new APIs not in the preview build)
* 3.0.0-preview2 (one of the experimental APIs went public, but still not ready to release)
* 3.0.0-experimental3 (contains 3.0.0-preview2 + the experimental API and some bug fixes)
* 3.0.0 is the first 3 stable release
* 3.0.1-experimental (contains 3.0.0 + the new APIs from 3.0.0-experimental1)
* 3.0.3 is the 2nd stable release(we made 3.0.2, noticed issues, fixed and rebuilt)

Version's fields have values 0-65535.

WARddlm requires architecture in its package Name to support concurrent use of different
architectures of a framework. See the [Dynamic Dependencies spec](https://github.com/microsoft/WindowsAppSDK/blob/main/specs/dynamicdependencies/DynamicDependencies.md)
for more details.

This leads to package Name length issues even for common cases:

|Package|Average|AverageLength|
| --- | :--- | :---: |
|WARfwk |Microsoft.WindowsAppRuntime.2-preview00|39|
|WARmain|Microsoft.WindowsAppRuntime.Main.2-preview00|44|
|WARsingleton|Microsoft.WindowsAppRuntime.Singleton-preview00|47|
|WARddlm|Microsoft.WinAppRuntime.DDLM.1.15.12345.24680-arm64-preview00|**<span style="color:red">61</span>**|

|Package|Min|MinLength|
| --- | :--- | :---: |
|WARfwk |Microsoft.WindowsAppRuntime.2-preview00|39|
|WARmain|Microsoft.WindowsAppRuntime.Main.1-preview00|44|
|WARsingleton|Microsoft.WindowsAppRuntime.Singleton-preview00|47|
|WARddlm|Microsoft.WinAppRuntime.DDLM.1.0.0.0-arm64-preview00|**<span style="color:red">52</span>**|

|Package|Max|MaxLength|
| --- | :--- | :---: |
|WARfwk |Microsoft.WindowsAppRuntime.65535-preview00|43|
|WARmain|Microsoft.WindowsAppRuntime.Main.65535-preview00|48|
|WARsingleton|Microsoft.WindowsAppRuntime.Singleton-preview00|47|
|WARddlm|Microsoft.WinAppRuntime.DDLM.65535.65535.65535.65535-arm64-preview00|**<span style="color:red">68</span>**|

Possible options we can use to shorten package Name:

* Change the Name constant/prefix to a shorter string e.g. change "Microsoft.WindowsAppRuntime.Main" to "Microsoft.WinAppRuntime.Main", etc
* Dictate max values e.g. Major=0-99
* Encode values as base-16
* Replace -channel with a shorter string e.g. replace "-preview" with "-pre", "-p", "p"
* Encode the channel name in the delimiter between name+version e.g. Microsoft.WinAppRuntime.DDLM<span style="color:red; font-size:xx-large"><b>.preview01</b></span>.1.0.0.0-arm64
* Encode tag in the delimiter between version+architecture e.g. Microsoft.WinAppRuntime.DDLM.1.0.0.0<span style="color:red"><b>p1</b></span>arm64 using P01 for Preview1, E01=Experimental1, ...
* Name WARddlm differently from WARfwk and WARmain e.g. use "-p01" for WARddlm regardless if WARfwk and WARmain use "-preview01"

WARddlm is needed until Dynamic Dependencies is 100% based on OS DynDep.

Best case (!) WARddlm exists until the minimum supported Windows release is Cobalt.

***Recommendation:*** The general package naming syntax is
`Microsoft.ProjectReunion[.SubName]-<rmajor>[-tag]`. WARddlm and WARsingleton are
exceptions to the rule (see below).

Windows App SDK 2.0 will use package Names of...

* WARfwk: `Microsoft.WindowsAppRuntime.<rmajor>[-tag]`
* WARmain: `Microsoft.WindowsAppRuntime.Main.<rmajor>[-tag]`
* WARsingleton: `Microsoft.WindowsAppRuntime.Singleton[-tag]`
* WARddlm: `Microsoft.WinAppRuntime.DDLM.<major>.<minor>.<patch>.<revision>-<shortarchitecture>[-shorttag]`

Using Decision 5: Version Encoding = Option D (M.N.P.0) WARddlm's maximum package Name length is
`Microsoft.WinAppRuntime.DDLM.12345.12345.12345.12345-arm64-p01` = 62 characters. This can be reduced
with the following rules:

* Major version <= 999
* Minor version <= 999
* Patch number <= 999
* Revision (security update) <= 99
* Architecture = 2 characters (x8=x86, x6=x64, a6=arm64)

In the unlikely event that Minor or Patch reach these limits, then the Major (for the Minor)
or Minor (for the Patch) will bump for all packages in order to keep these restrictions. If\When we reach Major version 1000, then
the Major version will be the Actual Major %1000. This works, since the Major is also included in the name.

This produces a worst case for WARddlm in Windows App SDK 99.888.777.66 ARM64 Preview 3 to the following identifiers:

* Package Name = `Microsoft.WinAppRuntime.DDLM.999.888.777.66-a6-p03` = 50 characters
* PackageFullName = `"Microsoft.WinAppRuntime.DDLM.999.888.777.66-a6-p03_999.888.7777.66_arm64__8wekyb3d8bbwe"`
* PackageFamilyName = `"Microsoft.WinAppRuntime.DDLM.999.888.777.66-a6-p03_8wekyb3d8bbwe"`
* PACKAGE_VERSION struct = `999.888.777.66`
* PACKAGE_VERSION uint64 = `0x03E7037803090042`

# 3. Conclusions

**Decision 1:** Windows App SDK version 0.* encodes `Major.Minor` into MSIX package Names starting with version 0.8.0.0.

**Decision 2:** Windows App SDK version 1.* encodes `Major.Minor` into MSIX package Names.

**Decision 2.1:** Windows App SDK version 2.* encodes `Major` into MSIX package Names.

**Decision 3:** Windows App SDK supports an optional 'tag' to indicate a non-Stable channel.
A 'tag' comes in long and short (1-2 character) forms e.g. `-preview` and `-p`,
or `-preview1` and `-p1` (the digit suffix is optional).

**Decision 4:** Windows App SDK encodes version as `<major>.<minor>.<patch>.<securityupdate>`
i.e. format encoding `M.N.P.0`. See
[2.4. Decision 4: Version Encoding](#24-decision-4-version-encoding) for more details.

**Decision 5:** MSIX package Names use the format
`Microsoft.WindowsAppRuntime[.SubName]-<rmajor>[-tag]`. WARddlm is an exception due to Name
length constraints. The specific packages Names in Windows App SDK 2.0:

* WARfwk: `Microsoft.WindowsAppRuntime.<rmajor>[-tag]`
* WARmain: `MicrosoftCorporationII.WinAppRuntime.Main.<rmajor>[-shorttag]`
* WARsingleton: `MicrosoftCorporationII.WinAppRuntime.Singleton[-shorttag]`
* WARddlm: `Microsoft.WinAppRuntime.DDLM.<major>.<minor>.<build>.<revision>-<shortarchitecture>[-shorttag]`

See [2.5. Decision 5: Package Names](#25-decision-5-package-names) for more details.
