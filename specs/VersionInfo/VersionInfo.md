# VersionInfo API

# Background

When using Windows App SDK via its framework-dependent runtime (aka MSIX packages) a developer
specifies at build-time a dependency _criteria_ which can match a range of possible packages. This
is resolved at runtime to a package meeting the criteria but it's not easy to determine the specific
package in use.

This API shrinkwraps these complexities providing an easy and reliable mechanism to determine the
specific runtime in use.

# Description

Developers using the Windows App SDK runtime as MSIX packages (aka framework-dependent) specify a
criteria to resolve at runtime. The mechanism and syntax depends if the app is packaged or
unpackaged.

Packaged apps declare a dependency in their `appxmanifest.xml e.g. for a dependency on WinAppSDK
1.1.0

```xml
  <Dependencies>
    <PackageDependency
        Name="Microsoft.WindowsAppRuntime.1.1"
        Publisher="CN=Microsoft Corporation, O=Microsoft Corporation, L=Redmond, S=Washington, C=US"
        MinVersion="1000.516.2156.0" />
  </Dependencies>
```

Unpackaged apps use the [Bootstrapper API](https://docs.microsoft.com/en-us/windows/windows-app-sdk/api/win32/_bootstrap/) specifying their dependency via parameters e.g. for a dependency on WinAppSDK 1.1.0 [using C](https://docs.microsoft.com/windows/windows-app-sdk/api/win32/mddbootstrap/nf-mddbootstrap-mddbootstrapinitialize)

```c
#include <WindowsAppSDK-VersionInfo.h>
#include <MddBootstrap.h>
// ...

HRESULT hr = MddBootstrapInitialize(WINDOWSAPPSDK_RELEASE_MAJORMINOR, WINDOWSAPPSDK_RELEASE_VERSION_TAG_W, WINDOWSAPPSDK_RUNTIME_VERSION_UINT64);
if (FAILED(hr))
{
    wprintf(L"Error 0x%X in Bootstrap initialization\n", hr);
}
```

where `WINDOWSAPPSDK_RELEASE_MAJORMINOR`, `WINDOWSAPPSDK_RELEASE_VERSION_TAG_W` and
`WINDOWSAPPSDK_RUNTIME_VERSION_UINT64` are build-time constants from `WindowsAppSDK-VersionInfo.h`
i.e.

```c
MddBootstrapInitialize(WINDOWSAPPSDK_RELEASE_MAJORMINOR, WINDOWSAPPSDK_RELEASE_VERSION_TAG_W, WINDOWSAPPSDK_RUNTIME_VERSION_UINT64)
```

for 1.1.0 is equivalent to

```c
MddBootstrapInitialize(0x00010001, L"", 0x03E80204086C0000u)
```

Developers using the Bootstrapper auto-initializer link a global constructor into their executable
which calls the Bootstrapper API with this build-time information.

All these options share a common property: the developer specifies the WinAppSDK release, channel
and a _minimum_ acceptable package version. This resolves to a specific package at runtime that
satisfies the dependency which is >= MinVersion (not ==MinVersion).

One can indirectly determine the actual runtime version in use by retrieving the package graph via
[GetCurrentPackageInfo()](https://docs.microsoft.com/windows/win32/api/appmodel/nf-appmodel-getcurrentpackageinfo)
and walking the result looking for a framework package in the runtime's family. This is cumbersome
(even more so for C# given the need for P/Invoke and the shape of the API for C# callers), can pose
performance overhead (searching across a deep copy of the package graph) and is potentially
ambiguous (e.g. advanced scenarios using Dynamic Dependencies can have multiple runtimes in the
package graph).

This can be shrinkwrapped via an easy to use API where we (WinAppSDK) incur the burden of
implementation complexity, using a design to directly and efficiently yield the correct answer.

This provides a simple but reliable and performant solution for applications, as well as class
libraries and other components using WinAppSDK.

# Examples

An example using the runtime version information API to display the actual version in use at runtime:

```c#
using System;
using System.Windows.Forms;
using Microsoft.Windows.ApplicationModel.WindowsAppRuntime;

public class MyInfo
{
    public static void About()
    {
        var build_release = Microsoft.WindowsAppSDK.Release;
        var build_version = Microsoft.WindowsAppSDK.Runtime.Version;
        var release = ReleaseInfo.Current();
        var runtime = RuntimeInfo.Current();
        var message = $"Built with Windows App SDK ${build_release.Major}.${build_release.Minor}.${build_release.Patch}${build_release.FormattedVersionTag}\n"
                      $"Minimum Windows App Runtime version ${build_version.Major}.${build_version.Minor}.${build_version.Build}.${build_version.Revision}\n"
                      "\n" +
                      $"Running with Windows App SDK ${release.Major}.${release.Minor}.${release.Patch}${release.FormattedVersionTag}\n" +
                      $"Windows App Runtime version ${runtime.version.Major}.${runtime.version.Minor}.${runtime.version.Build}.${runtime.version.Revision}";
        MessageBox.Show(message, "About MyApp", MessageBoxButtons.OK, MessageBoxIcon.Information);
    }
}
```

# Remarks

Version information is compiled into `Microsoft.WindowsAppRuntime.Insights.Resource.dll` as the
product is assembled (i.e. when the version is defined). The VersionInfo API retrieves this
information via an internal API.

# 6. API Details

```c# (but really MIDL3)
namespace Microsoft.Windows.ApplicationModel.WindowsAppRuntime
{
    [contractversion(1)]
    apicontract VersionInfoContract{};

    /// Version information for the Windows App SDK release.
    [contract(VersionInfoContract, 1)]
    static runtimeclass ReleaseInfo
    {
        /// The major version of the Windows App SDK release.
        static UInt16 Major{ get; };

        /// The minor version of the Windows App SDK release.
        static UInt16 Minor{ get; };

        /// The patch version of the Windows App SDK release.
        static UInt16 Patch{ get; };

        /// The Windows App SDK release's version tag; for example, "preview2", or empty string for stable.
        static String VersionTag{ get; };

        /// The version of the Windows App SDK runtime; for example, "1.1-preview2" or "1.2.3".
        static String AsString{ get; };
    };

    /// Version information for the Windows App SDK runtime.
    [contract(VersionInfoContract, 1)]
    static runtimeclass RuntimeInfo
    {
        /// The version of the Windows App SDK runtime; for example, { Major=1000, Minor=446, Build=804, Revision=0 }
        static Windows.ApplicationModel.PackageVersion Version{ get; };

        /// The version of the Windows App SDK runtime; for example, "1000.446.804.0"
        static String AsString{ get; };
    };
}
```

`WindowsAppSDK-VersionInfo.h` (C/C++) and `Microsoft.WindowsAppRuntime.Release.Net` (.NET assembly)
provide constants of what Windows App SDK is used at build-time. The VersionInfo API provides the
equivalent information but the values are the version actually in use at runtime.

# Appendix

## Alternative Design: VERSIONINFO Resource

An alternative design using a [VERSIONINFO resource](https://docs.microsoft.com/windows/win32/menurc/versioninfo-resource) was considered but discarded as a weaker alternative to the VersionInfo API for multiple reasons including...

* Resource APIs aren't necessarily convenient or accessible to all languages (unlike a WinRT API)
* Data contracts offer poor flexibility for future evolution (unlike an API)
* Data is more complex than VERSIONINFO supports (unlike the VersionInfo API)
