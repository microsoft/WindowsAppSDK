- [1. Background](#1-background)
- [2. Examples](#2-examples)
  - [2.1. Examples - C++](#21-examples---c)
  - [2.2. Examples - C](#22-examples---c)
- [3. API Details](#3-api-details)
  - [3.1. WindowsAppSDK-VersionInfo.h](#31-windowsappsdk-versioninfoh)
  - [3.2. WindowsAppSDK-VersionInfo.cs](#32-windowsappsdk-versioninfocs)
  - [3.3. WindowsAppSDK-VersionInfo.json](#33-windowsappsdk-versioninfojson)
  - [3.4. WindowsAppSDK-VersionInfo.xml](#34-windowsappsdk-versioninfoxml)

# 1. Background

Windows App SDK supports deployment as a set of MSIX packages for use at runtime, but some
operations and APIs require build information about the release. This spec defines public symbols
provided so developers can easily use Windows App SDK APIs at runtime referencing the version of
Windows App SDK they use at build-time.

For example,  `MddBootstrapInitialize(majorMinorRelease, versionTag, minVersion)` requires...

* Major.Minor version of the release
* Version tag (if any)
* Minimum required version of MSIX packages

If a developer builds an unpackaged app with Windows App SDK 1.0 Experimental1 with MSIX package
version of 0.218.840.0, they first must initialize Bootstrap API with this information. This is
accomplished with the call

```c++
const uint32_t c_majorMinorRelease{ (1u << 16) | 0 };
auto c_versionTag{ "experimental1" };
const PACKAGE_VERSION c_minVersion{ (0LLU << 48) | (218LLU << 32) | (840LLU << 16) | 0 };
THROW_IF_FAILED(MddBootstrapInitialize(c_majorMinorRelease, c_versionTag, minVersion));
```

And each time the WinAppSDK used by the build is updated this must be changed to match. This spec
allows developers to use constants provided by WinAppSDK ensuring the application's runtime use of
WinAppSDK's build information always matches the WinAppSDK used at build-time (without manual
developer intervention):

```c++
const uint32_t c_majorMinorRelease{ WINDOWSAPPSDK_RELEASE_MAJOR_MINOR };
auto c_versionTag{ WINDOWSAPPSDK_RELEASE_VERSION_TAG_W };
const PACKAGE_VERSION c_minVersion{ WINDOWSAPPSDK_RUNTIME_VERSION_UINT64 };
THROW_IF_FAILED(MddBootstrapInitialize(c_majorMinorRelease, c_versionTag, minVersion));
```

These symbols are provided in multiple formats for use by code and toolchains at build-time:

* C/C++ (comptible with C, C++, and Resource compilers)
* C#
* JSON
* XML

# 2. Examples

## 2.1. Examples - C++

```c++
#include <WindowsAppSDK-VersionInfo.h>

int main()
{
    const uint32_t c_majorMinorRelease{ WINDOWSAPPSDK_RELEASE_MAJOR_MINOR };
    auto c_versionTag{ WINDOWSAPPSDK_RELEASE_VERSION_TAG_W };
    const PACKAGE_VERSION c_minVersion{ WINDOWSAPPSDK_RUNTIME_VERSION_UINT64 };
    RETURN_IF_FAILED(MddBootstrapInitialize(c_majorMinorRelease, c_versionTag, minVersion));
    ...
```

## 2.2. Examples - C#

```c#
using Microsoft.Windows.ApplicationModel.DynamicDependency;

namespace MyNamespace
{
    class MyClass
    {
        static void Main()
        {
            // Initialize access to Windows App SDK
            var majorMinorRelease = Microsoft.WindowsAppSDK.Release.MajorMinor;
            var versionTag = Microsoft.WindowsAppSDK.Release.VersionTag;
            Microsoft.WindowsAppSDK.PackageVersion minVersion{ Microsoft.WindowsAppSDK.Runtime.Version.UInt64 };
            Bootstrap.Initialize(majorMinorRelease, versionTag, minVersion));
            ...
```

# 3. API Details

## 3.1. WindowsAppSDK-VersionInfo.h

```c
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#ifndef __WINDOWSAPPSDK_VERSIONINFO_H__
#define __WINDOWSAPPSDK_VERSIONINFO_H__

#define WINDOWSAPPSDK_RELEASE_MAJOR                1
#define WINDOWSAPPSDK_RELEASE_MINOR                0
#define WINDOWSAPPSDK_RELEASE_PATCH                0
#define WINDOWSAPPSDK_RELEASE_MAJORMINOR           0x00010000

#define WINDOWSAPPSDK_RELEASE_CHANNEL              "experimental"
#define WINDOWSAPPSDK_RELEASE_CHANNEL_W            L"experimental"

#define WINDOWSAPPSDK_RELEASE_VERSION_TAG          "experimental1"
#define WINDOWSAPPSDK_RELEASE_VERSION_TAG_W        L"experimental1"

#define WINDOWSAPPSDK_RELEASE_VERSION_SHORTTAG     "e1"
#define WINDOWSAPPSDK_RELEASE_VERSION_SHORTTAG_W   L"e1"

#define WINDOWSAPPSDK_RUNTIME_PUBLISHER            "CN=Microsoft Corporation, O=Microsoft Corporation, L=Redmond, S=Washington, C=US"
#define WINDOWSAPPSDK_RUNTIME_PUBLISHER_W          L"CN=Microsoft Corporation, O=Microsoft Corporation, L=Redmond, S=Washington, C=US"
#define WINDOWSAPPSDK_RUNTIME_PUBLISHERID          "8wekyb3d8bbwe"
#define WINDOWSAPPSDK_RUNTIME_PUBLISHERID_W        L"8wekyb3d8bbwe"

#define WINDOWSAPPSDK_RUNTIME_VERSION_MAJOR             0
#define WINDOWSAPPSDK_RUNTIME_VERSION_MINOR             242
#define WINDOWSAPPSDK_RUNTIME_VERSION_BUILD             1826
#define WINDOWSAPPSDK_RUNTIME_VERSION_REVISION          0
#define WINDOWSAPPSDK_RUNTIME_VERSION_UINT64            0x000000F207220000
#define WINDOWSAPPSDK_RUNTIME_VERSION_DOTQUADSTRING     "0.242.1826.0"
#define WINDOWSAPPSDK_RUNTIME_VERSION_DOTQUADSTRING_W   L"0.242.1826.0"

#endif // __WINDOWSAPPSDKVERSIONINFO_H__
```

## 3.2. WindowsAppSDK-VersionInfo.cs

```c#
// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

namespace Microsoft.WindowsAppSDK
{
    public class Release
    {
        public const ushort Major = 1;
        public const ushort Minor = 0;
        public const ushort Patch = 0;
        public const uint MajorMinor = 0x00010000;

        public const string Channel = "experimental";

        public const string VersionTag = "experimental1";

        public const string VersionShortTag = "e1";
    }

    namespace Runtime
    {
        public const string Publisher = "CN=Microsoft Corporation, O=Microsoft Corporation, L=Redmond, S=Washington, C=US";
        public const string PublisherId = "8wekyb3d8bbwe";

        public class Version
        {
            public const ushort Major = 0;
            public const ushort Minor = 242;
            public const ushort Build = 1826;
            public const ushort Revision = 0;
            public const ulong UInt64 = 0x000000F207220000;
            public const string DotQuadString = "0.242.1826.0";
        }
    }
}
```

## 3.3. WindowsAppSDK-VersionInfo.json

```json
{
    "Release" : {
        "Major" : 1,
        "Minor" : 0,
        "Patch" : 0,
        "MajorMinor" : {
            "UInt32" : 65536,
            "HexUInt32" : "0x00010000"
        },
        "Channel" : "experimental1",
        "VersionTag" : "experimental1",
        "VersionShortTag" : "e1"
    },
    "Runtime" : {
        "Publisher" : "CN=Microsoft Corporation, O=Microsoft Corporation, L=Redmond, S=Washington, C=US",
        "PublisherId" : "8wekyb3d8bbwe",
        "Version" : {
            "DotQuadNumber" : "0.242.1826.0",
            "UInt16" : 1039501754368,
            "HexUInt16" : "0x000000F207220000",
            "String" : "0.242.1826.0"
        }
    }
}
```

## 3.4. WindowsAppSDK-VersionInfo.xml

```xml
<WindowsAppSDK>
    <Release>
        <Major>1</Major>
        <Minor>0</Minor>
        <Patch>0</Patch>
        <MajorMinor>
            <UInt32>65536</UInt32>
            <HexUInt32>00010000</HexUInt32>
        </MajorMinor>
        <Channel>experimental</Channel>
        <VersionTag>experimental1</VersionTag>
        <VersionShortTag>e1</VersionShortTag>
    </Release>
    <Runtime>
        <Publisher>CN=Microsoft Corporation, O=Microsoft Corporation, L=Redmond, S=Washington, C=US</Publisher>
        <PublisherId>8wekyb3d8bbwe</Publisher>
        <Version>
            <DotQuadNumber>0.242.1826.0</DotQuadNumber>
            <UInt16>1039501754368</UInt16>
            <HexUInt16>0x000000F207220000</HexUInt16>
            <String>0.242.1826.0</String>
        </Version>
    </Runtime>
</WindowsAppSDK>
```
