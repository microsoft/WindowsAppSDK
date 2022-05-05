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

***Recommendation:*** Option B.

Option B provides a stronger degree of compatibility and risk management than Option A (Major
version) while still affording a reasonable way for developers to adopt updates.

Windows App SDK aspires to adopt Option A (Major version) but more tooling and infrastructure is
desired before making that level of guarantee. Option B provides a good balance of rapid
development and compatibility assurance.

Option A can (and will) be adopted in a future release (no sooner than 2.0) once tooling and
infrastructure are ready to embrace it.

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

***Do we need a shorter tag?*** "-preview1" adds 9 characters to package Name. "-experiental1" adds
13 characters. Package Name is restricted to 50 characters maximum.

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

***Recommendation:*** Option D with Epoch=January 1, 2021.

Option A works for a simple release strategy but doesn't work when there's regular
(e.g. daily) builds.

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
* WARddlm: `Microsoft.WindowsAppRuntime.DDLM.<major>.<minor>.<build>.<revision>-<shortarchitecture>[-shorttag]`

and release 1.x...

* WARfwk: `Microsoft.WindowsAppRuntime.<rmajor>.<rminor>[-tag]`
* WARmain: `MicrosoftCorporationII.WinAppRuntime.Main.<rmajor>.<rminor>[-shorttag]`
* WARsingleton: `MicrosoftCorporationII.WinAppRuntime.Singleton[-shorttag]`
* WARddlm: `Microsoft.WinAppRuntime.DDLM.<major>.<minor>.<build>.<revision>-<shortarchitecture>[-shorttag]`

where

* rmajor = Major version number of the project release, base-10, no leading zeros (e.g. "1" for WindowsAppSDK 1.2)
* rminor  = Minor version number of the project release, base-10, no leading zeros (e.g. "2" for WindowsAppSDK 1.2)
* major = Major version number of the release, base-10, no leading zeros
* minor  = Minor version number of the release, base-10, no leading zeros
* build = Build version number, base-10, no leading zeros
* revision = Revision version number, base-10, no leading zeros
* architecture = Allowed values: "x86", "x64", "arm64"
* shortarchitecture = Allowed values: "x8", "x6", "a6"
* tag = Allowed values: "", "preview[#]", "experimental[#]"
* shorttag = Allowed values: "", "p[#]", "e[#]"

**NOTE:** rmajor/rminor are the release version, major/minor/build/revision are the MSIX package
version (Microsoft.ProjectReunion.0.8-preview had a release version of 0.8
but an MSIX package version of 8000.146.628.0).

Version's fields have values 0-65535.

WARddlm requires architecture in its package Name to support concurrent use of different
architectures of a framework. See the [Dynamic Dependencies spec](https://github.com/microsoft/WindowsAppSDK/blob/main/specs/dynamicdependencies/DynamicDependencies.md)
for more details.

This leads to package Name length issues even for common cases:

|Package|Average|AverageLength|
| --- | :--- | :---: |
|WARfwk |Microsoft.WindowsAppRuntime.1.15-preview1|41|
|WARmain|Microsoft.WindowsAppRuntime.Main.1.15-preview1|46|
|WARsingleton|Microsoft.WindowsAppRuntime.Singleton-preview1|46|
|WARddlm|Microsoft.WinAppRuntime.DDLM.1.15.12345.24680-arm64-preview1|**<span style="color:red">64</span>**|

|Package|Min|MinLength|
| --- | :--- | :---: |
|WARfwk |Microsoft.WindowsAppRuntime.1.0-preview1|40|
|WARmain|Microsoft.WindowsAppRuntime.Main.1.0-preview1|45|
|WARsingleton|Microsoft.WindowsAppRuntime.Singleton-preview1|46|
|WARddlm|Microsoft.WinAppRuntime.DDLM.1.0.0.0-arm64-preview1|**<span style="color:red">52</span>**|

|Package|Max|MaxLength|
| --- | :--- | :---: |
|WARfwk |Microsoft.WindowsAppRuntime.65535.65535-preview1|48|
|WARmain|Microsoft.WindowsAppRuntime.Main.65535.65535-preview1|53|
|WARsingleton|Microsoft.WindowsAppRuntime.Singleton-preview1|46|
|WARddlm|Microsoft.WinAppRuntime.DDLM.65535.65535.65535.65535-arm64-preview1|**<span style="color:red">71</span>**|

Possible options we can use to shorten package Name:

* Change the Name constant/prefix to a shorter string e.g. change "Microsoft.WindowsAppRuntime.Main" to "Microsoft.WinAppRuntime.Main", etc
* Dictate max values e.g. Major=0-99
* Encode values as base-16
* Replace -channel with a shorter string e.g. replace "-preview" with "-pre", "-p", "p"
* Encode the channel name in the delimiter between name+version e.g. Microsoft.WinAppRuntime.DDLM<span style="color:red; font-size:xx-large"><b>.preview1</b></span>.1.0.0.0-arm64
* Encode tag in the delimiter between version+architecture e.g. Microsoft.WinAppRuntime.DDLM.1.0.0.0<span style="color:red"><b>p1</b></span>arm64 using P1 for Preview1, E1=Experimental1, ...
* Name WARddlm differently from WARfwk and WARmain e.g. use "-p1" for WARddlm regardless if WARfwk and WARmain use "-preview1"
* ???

WARddlm is needed until Dynamic Dependencies is 100% based on OS DynDep.

Best case (!) WARddlm exists until the minimum supported Windows release is Cobalt.

***Recommendation:*** The general package naming syntax is
`Microsoft.ProjectReunion[.SubName]-<rmajor>.<rminor>[-tag]`. WARddlm and WARsingleton are
exceptions to the rule (see below).

Windows App SDK 0.8 will use package Names of...

* WARfwk: `Microsoft.WindowsAppRuntime.<rmajor>.<rminor>[-tag]`
* WARmain: `Microsoft.WindowsAppRuntime.Main.<rmajor>.<rminor>[-tag]`
* WARsingleton: `Microsoft.WindowsAppRuntime.Singleton[-tag]`
* WARddlm: `Microsoft.WinAppRuntime.DDLM.<major>.<minor>.<build>.<revision>-<shortarchitecture>[-shorttag]`

Using Decision 5: Version Encoding = Option D (NPPP.E.B.0) WARddlm's maximum package Name length is
`Microsoft.WinAppRuntime.DDLM.1714.3944.123.24680-arm64-p3` = 58 characters. This can be reduced
with the following rules:

* Major version <= 99
* Minor version <= 999
* Build number <= 9999
* Revision (security update) <= 99
* Architecture = 2 characters (x8=x86, x6=x64, a6=arm64)

This produces a worst case for WARddlm in Windows App SDK 99.888.7777.66 ARM64 Preview 3 to the following identifiers:

* Package Name = `Microsoft.WinAppRuntime.DDLM.99.888.7777.66-a6-p3` = 49 characters
* PackageFullName = `"Microsoft.WinAppRuntime.DDLM.99.888.7777.66-a6-p3_99.888.7777.66_arm64__8wekyb3d8bbwe"`
* PackageFamilyName = `"Microsoft.WinAppRuntime.DDLM.99.888.7777.66-a6-p3_8wekyb3d8bbwe"`
* PACKAGE_VERSION struct = `99.888.7777.66`
* PACKAGE_VERSION uint64 = `0x006303781E610042`

# 3. Conclusions

**Decision 1:** Windows App SDK version 0.* encodes `Major.Minor` into MSIX package Names starting with version 0.8.0.0.

**Decision 2:** Windows App SDK version 1.* encodes `Major.Minor` into MSIX package Names.

**Decision 3:** Windows App SDK supports an optional 'tag' to indicate a non-Stable channel.
A 'tag' comes in long and short (1-2 character) forms e.g. `-preview` and `-p`,
or `-preview1` and `-p1` (the digit suffix is optional).

**Decision 4:** Windows App SDK encodes version as `<minor><patch>.<epoch>.<build>.<securityupdate>`
i.e. format encoding `NPPP.E.B.0`. See
[2.4. Decision 4: Version Encoding](#24-decision-4-version-encoding) for more details.

**Decision 5:** MSIX package Names use the format
`Microsoft.WindowsAppRuntime[.SubName]-<rmajor>.<rminor>[-tag]`. WARddlm is an exception due to Name
length constraints. The specific packages Names in Windows App SDK 1.0:

* WARfwk: `Microsoft.WindowsAppRuntime.<rmajor>.<rminor>[-tag]`
* WARmain: `MicrosoftCorporationII.WinAppRuntime.Main.<rmajor>.<rminor>[-shorttag]`
* WARsingleton: `MicrosoftCorporationII.WinAppRuntime.Singleton[-shorttag]`
* WARddlm: `Microsoft.WinAppRuntime.DDLM.<major>.<minor>.<build>.<revision>-<shortarchitecture>[-shorttag]`

See [2.5. Decision 5: Package Names](#25-decision-5-package-names) for more details.
