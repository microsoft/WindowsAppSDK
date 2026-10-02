// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __MICROSFT_WINDOWSAPPRUNTIME_VERSIONINFO_H
#define __MICROSFT_WINDOWSAPPRUNTIME_VERSIONINFO_H

/// Determine if Windows App SDK in use by the current process is deployed Self-Contained (vs deployed as MSIX packages)
///
/// @param packageFamilyName framework's package family name.
STDAPI WindowsAppRuntime_VersionInfo_MSIX_Framework_PackageFamilyName_Get(
    PCWSTR* packageFamilyName) noexcept;

/// Determine if Windows App SDK in use by the current process is deployed Self-Contained (vs deployed as MSIX packages)
///
/// @param packageFamilyName main's package family name.
STDAPI WindowsAppRuntime_VersionInfo_MSIX_Main_PackageFamilyName_Get(
    PCWSTR* packageFamilyName) noexcept;

/// Initialize SelfContained's test support. This will constrain package enumeration
/// and matching for test purposes.
///
/// @param frameworkPackageFamilyName only match framework packages with this family name.
///                                   If nullptr test support is disabled.
/// @param mainPackageFamilyName only match main packages with this family name.
///                              If nullptr test support is disabled.
///
/// @note Not for product use. This is for test purposes only to verify the implementation.
STDAPI WindowsAppRuntime_VersionInfo_TestInitialize(
    PCWSTR frameworkPackageFamilyName,
    PCWSTR mainPackageFamilyName) noexcept;

#if defined(__cplusplus)
namespace WindowsAppRuntime::VersionInfo
{
namespace Framework
{
/// Return the Windows App SDK framework's package family name.
inline std::wstring GetPackageFamilyName()
{
    PCWSTR packageFamilyName{};
    THROW_IF_FAILED(WindowsAppRuntime_VersionInfo_MSIX_Framework_PackageFamilyName_Get(&packageFamilyName));
    return std::wstring{ packageFamilyName };
}
}

namespace Main
{
/// Return the Windows App SDK main's package family name.
inline std::wstring GetPackageFamilyName()
{
    PCWSTR packageFamilyName{};
    THROW_IF_FAILED(WindowsAppRuntime_VersionInfo_MSIX_Main_PackageFamilyName_Get(&packageFamilyName));
    return std::wstring{ packageFamilyName };
}
}

/// Initialize VersionInfo's test support. This will constrain package enumeration
/// and matching for test purposes.
///
/// @param frameworkPackageFamilyName only match framework packages with this family name
/// @param mainPackageFamilyName only match main packages with this family name
///
/// @note Not for product use. This is for test purposes only to verify the implementation.
inline void TestInitialize(
    _In_ PCWSTR frameworkPackageFamilyName,
    _In_ PCWSTR mainPackageFamilyName)
{
    THROW_IF_FAILED(WindowsAppRuntime_VersionInfo_TestInitialize(frameworkPackageFamilyName, mainPackageFamilyName));
}

/// Initialize VersionInfo's test support. This will constrain package enumeration
/// and matching for test purposes.
///
/// @param frameworkPackageFamilyName only match framework packages with this family name
///
/// @note Not for product use. This is for test purposes only to verify the implementation.
inline void TestInitialize(
    _In_ PCWSTR frameworkPackageFamilyName)
{
    THROW_IF_FAILED(WindowsAppRuntime_VersionInfo_TestInitialize(frameworkPackageFamilyName, nullptr));
}

/// Shutdown VersionInfo's test support.
///
/// @note Not for product use. This is for test purposes only to verify the implementation.
inline void TestShutdown()
{
    WindowsAppRuntime_VersionInfo_TestInitialize(nullptr, nullptr);
}
}

namespace Microsoft::WindowsAppSDK
{
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

    /// Return the version information
    /// @note the return value is never null.
    const VersionInfo* GetVersionInfo();
}
#endif // defined(__cplusplus)

#endif // __MICROSFT_WINDOWSAPPRUNTIME_VERSIONINFO_H
