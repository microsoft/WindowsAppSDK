// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

// NOTE: This is a representative copy as shipped by the final product. Actual values are gibberish not relevant

#ifndef __WINDOWSAPPSDK_VERSIONINFO_H__
#define __WINDOWSAPPSDK_VERSIONINFO_H__

// Release information
#define WINDOWSAPPSDK_RELEASE_MAJOR                1
#define WINDOWSAPPSDK_RELEASE_MINOR                4
#define WINDOWSAPPSDK_RELEASE_PATCH                0
#define WINDOWSAPPSDK_RELEASE_MAJORMINOR           0x00010001

#define WINDOWSAPPSDK_RELEASE_CHANNEL              "preview"
#define WINDOWSAPPSDK_RELEASE_CHANNEL_W            L"preview"

#define WINDOWSAPPSDK_RELEASE_VERSION_TAG          "preview1"
#define WINDOWSAPPSDK_RELEASE_VERSION_TAG_W        L"preview1"

#define WINDOWSAPPSDK_RELEASE_VERSION_SHORTTAG     "p1"
#define WINDOWSAPPSDK_RELEASE_VERSION_SHORTTAG_W   L"p1"

// Runtime information
#define WINDOWSAPPSDK_RUNTIME_IDENTITY_PUBLISHER        "CN=Microsoft Corporation, O=Microsoft Corporation, L=Redmond, S=Washington, C=US"
#define WINDOWSAPPSDK_RUNTIME_IDENTITY_PUBLISHER_W      L"CN=Microsoft Corporation, O=Microsoft Corporation, L=Redmond, S=Washington, C=US"
#define WINDOWSAPPSDK_RUNTIME_IDENTITY_PUBLISHERID      "8wekyb3d8bbwe"
#define WINDOWSAPPSDK_RUNTIME_IDENTITY_PUBLISHERID_W    L"8wekyb3d8bbwe"

#define WINDOWSAPPSDK_RUNTIME_VERSION_MAJOR             1000
#define WINDOWSAPPSDK_RUNTIME_VERSION_MINOR             446
#define WINDOWSAPPSDK_RUNTIME_VERSION_BUILD             804
#define WINDOWSAPPSDK_RUNTIME_VERSION_REVISION          0
#define WINDOWSAPPSDK_RUNTIME_VERSION_UINT64            0x03E801BE03240000
#define WINDOWSAPPSDK_RUNTIME_VERSION_DOTQUADSTRING     "1000.446.804.0"
#define WINDOWSAPPSDK_RUNTIME_VERSION_DOTQUADSTRING_W   L"1000.446.804.0"

#define WINDOWSAPPSDK_RUNTIME_PACKAGE_FRAMEWORK_PACKAGEFAMILYNAME   "Microsoft.WindowsAppRuntime.1.1-preview1_8wekyb3d8bbwe"
#define WINDOWSAPPSDK_RUNTIME_PACKAGE_FRAMEWORK_PACKAGEFAMILYNAME_W "Microsoft.WindowsAppRuntime.1.1-preview1_8wekyb3d8bbwe"
#define WINDOWSAPPSDK_RUNTIME_PACKAGE_MAIN_PACKAGEFAMILYNAME        "MicrosoftCorporationII.WinAppRuntime.Main.1.1-p1_8wekyb3d8bbwe"
#define WINDOWSAPPSDK_RUNTIME_PACKAGE_MAIN_PACKAGEFAMILYNAME_W      L"MicrosoftCorporationII.WinAppRuntime.Main.1.1-p1_8wekyb3d8bbwe"
#define WINDOWSAPPSDK_RUNTIME_PACKAGE_SINGLETON_PACKAGEFAMILYNAME   "MicrosoftCorporationII.WinAppRuntime.Singleton-p1_8wekyb3d8bbwe"
#define WINDOWSAPPSDK_RUNTIME_PACKAGE_SINGLETON_PACKAGEFAMILYNAME_W L"MicrosoftCorporationII.WinAppRuntime.Singleton-p1_8wekyb3d8bbwe"

#if defined(__cplusplus)
namespace Microsoft::WindowsAppSDK
{
    namespace Release
    {
        constexpr uint16_t Major = 1;
        constexpr uint16_t Minor = 1;
        constexpr uint16_t Patch = 0;
        constexpr uint32_t MajorMinor = 0x00010001;

        constexpr PCWSTR Channel = L"preview";

        constexpr PCWSTR VersionTag = L"preview1";

        constexpr PCWSTR VersionShortTag = L"p1";
    }

    namespace Runtime
    {
        namespace Identity
        {
            constexpr PCWSTR Publisher = L"CN=Microsoft Corporation, O=Microsoft Corporation, L=Redmond, S=Washington, C=US";
            constexpr PCWSTR PublisherId = L"8wekyb3d8bbwe";
        }

        namespace Version
        {
            constexpr uint16_t Major = 1000;
            constexpr uint16_t Minor = 446;
            constexpr uint16_t Build = 804;
            constexpr uint16_t Revision = 0;
            constexpr uint64_t UInt64 = 0x03E801BE03240000;
            constexpr PCWSTR DotQuadString = L"1000.446.804.0";
        }

        namespace Packages
        {
            namespace Framework
            {
                constexpr PCWSTR PackageFamilyName = L"Microsoft.WindowsAppRuntime.1.1-preview1_8wekyb3d8bbwe";
            }
            namespace Main
            {
                constexpr PCWSTR PackageFamilyName = L"MicrosoftCorporationII.WinAppRuntime.Main.1.1-p1_8wekyb3d8bbwe";
            }
            namespace Singleton
            {
                constexpr PCWSTR PackageFamilyName = L"MicrosoftCorporationII.WinAppRuntime.Singleton-p1_8wekyb3d8bbwe";
            }
        }
    }
}
#endif // defined(__cplusplus)

#endif // __WINDOWSAPPSDK_VERSIONINFO_H__
