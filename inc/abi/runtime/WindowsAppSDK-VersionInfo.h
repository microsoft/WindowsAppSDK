﻿// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#ifndef __WINDOWSAPPSDK_VERSIONINFO_H__
#define __WINDOWSAPPSDK_VERSIONINFO_H__

// Release information
#define WINDOWSAPPSDK_RELEASE_MAJOR                         1
#define WINDOWSAPPSDK_RELEASE_MINOR                         8
#define WINDOWSAPPSDK_RELEASE_PATCH                         250702
#define WINDOWSAPPSDK_RELEASE_MAJORMINOR                    0x00010008

#define WINDOWSAPPSDK_RELEASE_CHANNEL                       "experimental"
#define WINDOWSAPPSDK_RELEASE_CHANNEL_W                     L"experimental"

#define WINDOWSAPPSDK_RELEASE_VERSION_TAG                   "experimental4"
#define WINDOWSAPPSDK_RELEASE_VERSION_TAG_W                 L"experimental4"

#define WINDOWSAPPSDK_RELEASE_VERSION_SHORTTAG              "e4"
#define WINDOWSAPPSDK_RELEASE_VERSION_SHORTTAG_W            L"e4"

#define WINDOWSAPPSDK_RELEASE_FORMATTED_VERSION_TAG         "-experimental4"
#define WINDOWSAPPSDK_RELEASE_FORMATTED_VERSION_TAG_W       L"-experimental4"

#define WINDOWSAPPSDK_RELEASE_FORMATTED_VERSION_SHORTTAG    "-e4"
#define WINDOWSAPPSDK_RELEASE_FORMATTED_VERSION_SHORTTAG_W  L"-e4"

// Runtime information
#define WINDOWSAPPSDK_RUNTIME_IDENTITY_PUBLISHER        "CN=Microsoft Corporation, O=Microsoft Corporation, L=Redmond, S=Washington, C=US"
#define WINDOWSAPPSDK_RUNTIME_IDENTITY_PUBLISHER_W      L"CN=Microsoft Corporation, O=Microsoft Corporation, L=Redmond, S=Washington, C=US"
#define WINDOWSAPPSDK_RUNTIME_IDENTITY_PUBLISHERID      "8wekyb3d8bbwe"
#define WINDOWSAPPSDK_RUNTIME_IDENTITY_PUBLISHERID_W    L"8wekyb3d8bbwe"

#define WINDOWSAPPSDK_RUNTIME_VERSION_MAJOR             8000u
#define WINDOWSAPPSDK_RUNTIME_VERSION_MINOR             548u
#define WINDOWSAPPSDK_RUNTIME_VERSION_BUILD             2012u
#define WINDOWSAPPSDK_RUNTIME_VERSION_REVISION          0u
#define WINDOWSAPPSDK_RUNTIME_VERSION_UINT64            0x1F40022407DC0000u
#define WINDOWSAPPSDK_RUNTIME_VERSION_DOTQUADSTRING     "8000.548.2012.0"
#define WINDOWSAPPSDK_RUNTIME_VERSION_DOTQUADSTRING_W   L"8000.548.2012.0"

#define WINDOWSAPPSDK_RUNTIME_PACKAGE_FRAMEWORK_PACKAGEFAMILYNAME   "Microsoft.WindowsAppRuntime.1.8-experimental4_8wekyb3d8bbwe"
#define WINDOWSAPPSDK_RUNTIME_PACKAGE_FRAMEWORK_PACKAGEFAMILYNAME_W L"Microsoft.WindowsAppRuntime.1.8-experimental4_8wekyb3d8bbwe"
#define WINDOWSAPPSDK_RUNTIME_PACKAGE_MAIN_PACKAGEFAMILYNAME        "MicrosoftCorporationII.WinAppRuntime.Main.1.8-e4_8wekyb3d8bbwe"
#define WINDOWSAPPSDK_RUNTIME_PACKAGE_MAIN_PACKAGEFAMILYNAME_W      L"MicrosoftCorporationII.WinAppRuntime.Main.1.8-e4_8wekyb3d8bbwe"
#define WINDOWSAPPSDK_RUNTIME_PACKAGE_SINGLETON_PACKAGEFAMILYNAME       "MicrosoftCorporationII.WinAppRuntime.Singleton-e4_8wekyb3d8bbwe"
#define WINDOWSAPPSDK_RUNTIME_PACKAGE_SINGLETON_PACKAGEFAMILYNAME_W     L"MicrosoftCorporationII.WinAppRuntime.Singleton-e4_8wekyb3d8bbwe"
#define WINDOWSAPPSDK_RUNTIME_PACKAGE_DDLM_X86_PACKAGEFAMILYNAME        "Microsoft.WinAppRuntime.DDLM.8000.548.2012.0-x8-e4_8wekyb3d8bbwe"
#define WINDOWSAPPSDK_RUNTIME_PACKAGE_DDLM_X86_PACKAGEFAMILYNAME_W      L"Microsoft.WinAppRuntime.DDLM.8000.548.2012.0-x8-e4_8wekyb3d8bbwe"
#define WINDOWSAPPSDK_RUNTIME_PACKAGE_DDLM_X64_PACKAGEFAMILYNAME        "Microsoft.WinAppRuntime.DDLM.8000.548.2012.0-x6-e4_8wekyb3d8bbwe"
#define WINDOWSAPPSDK_RUNTIME_PACKAGE_DDLM_X64_PACKAGEFAMILYNAME_W      L"Microsoft.WinAppRuntime.DDLM.8000.548.2012.0-x6-e4_8wekyb3d8bbwe"
#define WINDOWSAPPSDK_RUNTIME_PACKAGE_DDLM_ARM64_PACKAGEFAMILYNAME      "Microsoft.WinAppRuntime.DDLM.8000.548.2012.0-a6-e4_8wekyb3d8bbwe"
#define WINDOWSAPPSDK_RUNTIME_PACKAGE_DDLM_ARM64_PACKAGEFAMILYNAME_W    L"Microsoft.WinAppRuntime.DDLM.8000.548.2012.0-a6-e4_8wekyb3d8bbwe"

#ifdef RC_INVOKED
// Only first 31 characters are significant for ResourceCompiler macro names (anything beyond that's silently ignored)
// These definitions provide RC-compatible equivalents to the macros above. Here's the translation key:
//   * WAS == WINDOWSAPPSDK
//   * WASR == WINDOWSAPPSDK_RUNTIME
//   * FMT == FORMATTED
//   * STAG == SHORTTAG
//   * PKG == PACKAGE
//   * FAMILY == PACKAGEFAMILYNAME

// Release information
#define WAS_RELEASE_MAJOR               1
#define WAS_RELEASE_MINOR               8
#define WAS_RELEASE_PATCH               250702
#define WAS_RELEASE_MAJORMINOR          0x00010008

#define WAS_RELEASE_CHANNEL             "experimental"
#define WAS_RELEASE_CHANNEL_W           L"experimental"

#define WAS_RELEASE_VERSION_TAG         "experimental4"
#define WAS_RELEASE_VERSION_TAG_W       L"experimental4"

#define WAS_RELEASE_VERSION_STAG        "e4"
#define WAS_RELEASE_VERSION_STAG_W      L"e4"

#define WAS_RELEASE_FMT_VERSION_TAG     "-experimental4"
#define WAS_RELEASE_FMT_VERSION_TAG_W   L"-experimental4"

#define WAS_RELEASE_FMT_VERSION_STAG    "-e4"
#define WAS_RELEASE_FMT_VERSION_STAG_W  L"-e4"

// Runtime information
#define WASR_IDENTITY_PUBLISHER         "CN=Microsoft Corporation, O=Microsoft Corporation, L=Redmond, S=Washington, C=US"
#define WASR_IDENTITY_PUBLISHER_W       L"CN=Microsoft Corporation, O=Microsoft Corporation, L=Redmond, S=Washington, C=US"
#define WASR_IDENTITY_PUBLISHERID       "8wekyb3d8bbwe"
#define WASR_IDENTITY_PUBLISHERID_W     L"8wekyb3d8bbwe"

#define WASR_VERSION_MAJOR              8000
#define WASR_VERSION_MINOR              548
#define WASR_VERSION_BUILD              2012
#define WASR_VERSION_REVISION           0
#define WASR_VERSION_UINT64             0x1F40022407DC0000
#define WASR_VERSION_DOTQUADSTRING      "8000.548.2012.0"
#define WASR_VERSION_DOTQUADSTRING_W    L"8000.548.2012.0"

#define WASR_PKG_FRAMEWORK_FAMILY       "Microsoft.WindowsAppRuntime.1.8-experimental4_8wekyb3d8bbwe"
#define WASR_PKG_FRAMEWORK_FAMILY_W     L"Microsoft.WindowsAppRuntime.1.8-experimental4_8wekyb3d8bbwe"
#define WASR_PKG_MAIN_FAMILY            "MicrosoftCorporationII.WinAppRuntime.Main.1.8-e4_8wekyb3d8bbwe"
#define WASR_PKG_MAIN_FAMILY_W          L"MicrosoftCorporationII.WinAppRuntime.Main.1.8-e4_8wekyb3d8bbwe"
#define WASR_PKG_SINGLETON_FAMILY       "MicrosoftCorporationII.WinAppRuntime.Singleton-e4_8wekyb3d8bbwe"
#define WASR_PKG_SINGLETON_FAMILY_W     L"MicrosoftCorporationII.WinAppRuntime.Singleton-e4_8wekyb3d8bbwe"
#define WASR_PKG_DDLM_X86_FAMILY        "Microsoft.WinAppRuntime.DDLM.8000.548.2012.0-x8-e4_8wekyb3d8bbwe"
#define WASR_PKG_DDLM_X86_FAMILY_W      L"Microsoft.WinAppRuntime.DDLM.8000.548.2012.0-x8-e4_8wekyb3d8bbwe"
#define WASR_PKG_DDLM_X64_FAMILY        "Microsoft.WinAppRuntime.DDLM.8000.548.2012.0-x6-e4_8wekyb3d8bbwe"
#define WASR_PKG_DDLM_X64_FAMILY_W      L"Microsoft.WinAppRuntime.DDLM.8000.548.2012.0-x6-e4_8wekyb3d8bbwe"
#define WASR_PKG_DDLM_ARM64_FAMILY      "Microsoft.WinAppRuntime.DDLM.8000.548.2012.0-a6-e4_8wekyb3d8bbwe"
#define WASR_PKG_DDLM_ARM64_FAMILY_W    L"Microsoft.WinAppRuntime.DDLM.8000.548.2012.0-a6-e4_8wekyb3d8bbwe"
#endif

#ifdef __cplusplus
#include <stdint.h>
namespace Microsoft::WindowsAppSDK
{
    /// Build-time constants for the Windows App SDK release
    namespace Release
    {
        /// The major version of the Windows App SDK release.
        constexpr uint16_t Major = 1;

        /// The minor version of the Windows App SDK release.
        constexpr uint16_t Minor = 8;

        /// The patch version of the Windows App SDK release.
        constexpr uint16_t Patch = 702;

        /// The major and minor version of the Windows App SDK release, encoded as a uint32_t (0xMMMMNNNN where M=major, N=minor).
        constexpr uint32_t MajorMinor = 0x00010008;

        /// The Windows App SDK release's channel; for example, "preview", or empty string for stable.
        constexpr PCWSTR Channel = L"experimental";

        /// The Windows App SDK release's version tag; for example, "preview2", or empty string for stable.
        constexpr PCWSTR VersionTag = L"experimental4";

        /// The Windows App SDK release's short-form version tag; for example, "p2", or empty string for stable.
        constexpr PCWSTR VersionShortTag = L"e4";

        /// The Windows App SDK release's version tag, formatted for concatenation when constructing identifiers; for example, "-preview2", or empty string for stable.
        constexpr PCWSTR FormattedVersionTag = L"-experimental4";

        /// The Windows App SDK release's short-form version tag, formatted for concatenation when constructing identifiers; for example, "-p2", or empty string for stable.
        constexpr PCWSTR FormattedVersionShortTag = L"-e4";
    }

    /// Build-time constants for the Windows App SDK runtime
    namespace Runtime
    {
        namespace Identity
        {
            /// The Windows App SDK runtime's package identity's Publisher.
            constexpr PCWSTR Publisher = L"CN=Microsoft Corporation, O=Microsoft Corporation, L=Redmond, S=Washington, C=US";

            /// The Windows App SDK runtime's package identity's PublisherId.
            constexpr PCWSTR PublisherId = L"8wekyb3d8bbwe";
        }

        namespace Version
        {
            /// The major version of the Windows App SDK runtime; for example, 1000.
            constexpr uint16_t Major = 8000;

            /// The minor version of the Windows App SDK runtime; for example, 446.
            constexpr uint16_t Minor = 548;

            /// The build version of the Windows App SDK runtime; for example, 804.
            constexpr uint16_t Build = 2012;

            /// The revision version of the Windows App SDK runtime; for example, 0.
            constexpr uint16_t Revision = 0;

            /// The version of the Windows App SDK runtime, as a uint64l for example, 0x03E801BE03240000.
            constexpr uint64_t UInt64 = 0x1F40022407DC0000;

            /// The version of the Windows App SDK runtime, as a string (const wchar_t*); for example, "1000.446.804.0".
            constexpr PCWSTR DotQuadString = L"8000.548.2012.0";
        }

        namespace Packages
        {
            namespace Framework
            {
                /// The Windows App SDK runtime's Framework package's family name.
                constexpr PCWSTR PackageFamilyName = L"Microsoft.WindowsAppRuntime.1.8-experimental4_8wekyb3d8bbwe";
            }
            namespace Main
            {
                /// The Windows App SDK runtime's Main package's family name.
                constexpr PCWSTR PackageFamilyName = L"MicrosoftCorporationII.WinAppRuntime.Main.1.8-e4_8wekyb3d8bbwe";
            }
            namespace Singleton
            {
                /// The Windows App SDK runtime's Singleton package's family name.
                constexpr PCWSTR PackageFamilyName = L"MicrosoftCorporationII.WinAppRuntime.Singleton-e4_8wekyb3d8bbwe";
            }
            namespace DDLM
            {
                namespace X86
                {
                    /// The Windows App SDK runtime's Dynamic Dependency Lifetime Manager (DDLM) package's family name, for x86.
                    constexpr PCWSTR PackageFamilyName = L"Microsoft.WinAppRuntime.DDLM.8000.548.2012.0-x8-e4_8wekyb3d8bbwe";
                }
                namespace X64
                {
                    /// The Windows App SDK runtime's Dynamic Dependency Lifetime Manager (DDLM) package's family name, for x64.
                    constexpr PCWSTR PackageFamilyName = L"Microsoft.WinAppRuntime.DDLM.8000.548.2012.0-x6-e4_8wekyb3d8bbwe";
                }
                namespace Arm64
                {
                    /// The Windows App SDK runtime's Dynamic Dependency Lifetime Manager (DDLM) package's family name, for arm64.
                    constexpr PCWSTR PackageFamilyName = L"Microsoft.WinAppRuntime.DDLM.8000.548.2012.0-a6-e4_8wekyb3d8bbwe";
                }
            }
        }
    }

    /// Run-time query'able version information for the Windows App SDK.
    struct VersionInfo
    {
        /// Run-time query'able version information for the Windows App SDK release
        struct Release
        {
            /// The major version of the Windows App SDK release.
            uint16_t Major;

            /// The minor version of the Windows App SDK release.
            uint16_t Minor;

            /// The patch version of the Windows App SDK release.
            uint16_t Patch;

            /// The major and minor version of the Windows App SDK release, encoded as a uint32_t (0xMMMMNNNN where M=major, N=minor).
            uint32_t MajorMinor;

            /// The Windows App SDK release's channel; for example, "preview", or empty string for stable.
            PCWSTR Channel;

            /// The Windows App SDK release's version tag; for example, "preview2", or empty string for stable.
            PCWSTR VersionTag;

            /// The Windows App SDK release's short-form version tag; for example, "p2", or empty string for stable.
            PCWSTR VersionShortTag;
        } Release;

        /// Run-time query'able version information for the Windows App SDK runtime
        struct Runtime
        {
            struct Identity
            {
                /// The Windows App SDK runtime's package identity's Publisher.
                PCWSTR Publisher;

                /// The Windows App SDK runtime's package identity's PublisherId.
                PCWSTR PublisherId;
            } Identity;

            struct Version
            {
                /// The major version of the Windows App SDK runtime; for example, 1000.
                uint16_t Major;

                /// The minor version of the Windows App SDK runtime; for example, 446.
                uint16_t Minor;

                /// The build version of the Windows App SDK runtime; for example, 804.
                uint16_t Build;

                /// The revision version of the Windows App SDK runtime; for example, 0.
                uint16_t Revision;

                /// The version of the Windows App SDK runtime, as a uint64l for example, 0x03E801BE03240000.
                uint64_t UInt64;

                /// The version of the Windows App SDK runtime, as a string (const wchar_t*); for example, "1000.446.804.0".
                PCWSTR DotQuadString;
            } Version;
        } Runtime;
    };
}
#endif // __cplusplus

#endif // _WINDOWSAPPSDK_VERSIONINFO_H__
