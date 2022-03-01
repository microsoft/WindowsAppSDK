// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#if !defined(MDDBOOTSTRAP_H)
#define MDDBOOTSTRAP_H

#include <appmodel.h>

/// Initialize the calling process to use Windows App Runtime framework package.
///
/// Find a Windows App Runtime framework package meeting the criteria and make it available
/// for use by the current process. If multiple packages meet the criteria the best
/// candidate is selected.
///
/// @param majorMinorVersion the major and minor version to use, e..g 0x00010002 for Major.Minor=1.2
/// @param versionTag the version pre-release identifier, or NULL if none.
/// @param minVersion the minimum version to use
STDAPI MddBootstrapInitialize(
    UINT32 majorMinorVersion,
    PCWSTR versionTag,
    PACKAGE_VERSION minVersion) noexcept;

/// Undo the changes made by MddBoostrapInitialize().
///
/// @warning Packages made available via MddBootstrapInitialize() and
///          the Dynamic Dependencies API should not be used after this call.
STDAPI_(void) MddBootstrapShutdown() noexcept;

// C++ friendly APIs
#if defined(__cplusplus)
#if defined(WINDOWSAPPSDK_RELEASE_MAJORMINOR) && defined(WINDOWSAPPSDK_RELEASE_VERSION_TAG_W) && defined(WINDOWSAPPSDK_RUNTIME_VERSION_UINT64)
namespace Microsoft::Windows::ApplicationModel
{
class PackageVersion : public PACKAGE_VERSION
{
public:
    PackageVersion()
    {
        Version = 0;
    }

    // Create an instance with the value `major.minor.build.revision`.
    PackageVersion(uint16_t major, uint16_t minor = 0, uint16_t build = 0, uint16_t revision = 0) :
        PACKAGE_VERSION()
    {
        Major = major;
        Minor = minor;
        Build = build;
        Revision = revision;
    }

    // Create an instance from a version as a uint64.
    PackageVersion(uint64_t version)
    {
        Version = version;
    }

    // Return the version as a uint64.
    uint64_t ToVersion() const
    {
        return Version;
    }

#if defined(_XSTRING_) && defined(_STRSAFE_H_INCLUDED_) && defined(WI_VERIFY)
    // Return the string as a formatted value "major.minor.build.revision".
    std::wstring ToString() const
    {
        return ToString(Major, Minor, Build, Revision);
    }

    static std::wstring ToString(uint16_t major, uint16_t minor, uint16_t build, uint16_t revision)
    {
        wchar_t formattedVersion[5 + 1 + 5 + 1 + 5 + 1 + 5 + 1]{};  // "12345.12345.12345.12345" + null-terminator
        WI_VERIFY(SUCCEEDED(StringCchPrintfW(formattedVersion, ARRAYSIZE(formattedVersion), L"%hu.%hu.%hu.%hu", major, minor, build, revision)));
        return std::wstring(formattedVersion);
    }
#endif
};

namespace DynamicDependency::Bootstrap
{
    // Automate Boostrap shutdown when leaving scope
    using unique_mddbootstrapshutdown_call = wil::unique_call<decltype(&::MddBootstrapShutdown), ::MddBootstrapShutdown>;

    /// Call MddBootstrapInitialize and fail-fasts if it fails; returns an RAII objecct that reverts
    ///
    /// Initialize the calling process to use Windows App SDK's framework package.
    ///
    /// Find a Windows App SDK framework package meeting the criteria and make it available
    /// for use by the current process. If multiple packages meet the criteria the best
    /// candidate is selected.
    ///
    /// @param majorMinorVersion major and minor version of Windows App SDK's framework package, encoded as `0xMMMMNNNN` where M=Major, N=Minor (e.g. 1.2 == 0x00010002).
    /// @param versionTag version tag (if any), e.g. "preview1".
    /// @param minVersion the minimum version to use
    /// @see Initialize(uint32_t, PCWSTR, PackageVersion)
    /// @see Initialize_nothrow(uint32_t, PCWSTR, PackageVersion)
    /// @see Shutdown()
    WI_NODISCARD inline unique_mddbootstrapshutdown_call Initialize_failfast(uint32_t majorMinorVersion = WINDOWSAPPSDK_RELEASE_MAJORMINOR,
                                                                             PCWSTR versionTag = WINDOWSAPPSDK_RELEASE_VERSION_TAG_W,
                                                                             PackageVersion minVersion = WINDOWSAPPSDK_RUNTIME_VERSION_UINT64)
    {
        FAIL_FAST_IF_FAILED(::MddBootstrapInitialize(majorMinorVersion, versionTag, minVersion));
        return unique_mddbootstrapshutdown_call();
    }

#if defined(WIL_ENABLE_EXCEPTIONS)
    /// Call MddBootstrapInitialize and throws an exception if it fails; returns an RAII objecct that reverts
    ///
    /// Initialize the calling process to use Windows App SDK's framework package.
    ///
    /// Find a Windows App SDK framework package meeting the criteria and make it available
    /// for use by the current process. If multiple packages meet the criteria the best
    /// candidate is selected.
    ///
    /// @param majorMinorVersion major and minor version of Windows App SDK's framework package, encoded as `0xMMMMNNNN` where M=Major, N=Minor (e.g. 1.2 == 0x00010002).
    /// @param versionTag version tag (if any), e.g. "preview1".
    /// @param minVersion the minimum version to use
    /// @see Initialize_failfast(uint32_t, PCWSTR, PackageVersion)
    /// @see Initialize_nothrow(uint32_t, PCWSTR, PackageVersion)
    /// @see Shutdown()
    WI_NODISCARD inline unique_mddbootstrapshutdown_call Initialize(uint32_t majorMinorVersion = WINDOWSAPPSDK_RELEASE_MAJORMINOR,
                                                                    PCWSTR versionTag = WINDOWSAPPSDK_RELEASE_VERSION_TAG_W,
                                                                    PackageVersion minVersion = WINDOWSAPPSDK_RUNTIME_VERSION_UINT64)
    {
        THROW_IF_FAILED(::MddBootstrapInitialize(majorMinorVersion, versionTag, minVersion));
        return unique_mddbootstrapshutdown_call();
    }
#endif // defined(WIL_ENABLE_EXCEPTIONS)

    /// Call MddBootstrapInitialize and returns failure HRESULT if it fails.
    ///
    /// Initialize the calling process to use Windows App SDK's framework package.
    ///
    /// Find a Windows App SDK framework package meeting the criteria and make it available
    /// for use by the current process. If multiple packages meet the criteria the best
    /// candidate is selected.
    ///
    /// @param majorMinorVersion major and minor version of Windows App SDK's framework package, encoded as `0xMMMMNNNN` where M=Major, N=Minor (e.g. 1.2 == 0x00010002).
    /// @param versionTag version tag (if any), e.g. "preview1".
    /// @param minVersion the minimum version to use
    /// @see Initialize_failfast(uint32_t, PCWSTR, PackageVersion)
    /// @see Initialize(uint32_t, PCWSTR, PackageVersion)
    /// @see Shutdown()
    inline HRESULT Initialize_nothrow(uint32_t majorMinorVersion = WINDOWSAPPSDK_RELEASE_MAJORMINOR,
                                      PCWSTR versionTag = WINDOWSAPPSDK_RELEASE_VERSION_TAG_W,
                                      PackageVersion minVersion = WINDOWSAPPSDK_RUNTIME_VERSION_UINT64)
    {
        RETURN_IF_FAILED(::MddBootstrapInitialize(majorMinorVersion, versionTag, minVersion));
        return S_OK;
    }
}
}
#endif // defined(WINDOWSAPPSDK_RELEASE_MAJORMINOR) && defined(WINDOWSAPPSDK_RELEASE_VERSION_TAG_W) && defined()WINDOWSAPPSDK_RUNTIME_VERSION_UINT64)
#endif // defined(__cplusplus)

#endif // MDDBOOTSTRAP_H
