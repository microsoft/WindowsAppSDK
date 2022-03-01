// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#if !defined(MDDBOOSTRAP_H)
#define MDDBOOSTRAP_H

#include <appmodel.h>

/// Iniitalize the calling process to use Windows App Runtime framework package.
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
#if defined(WINDOWSAPPRUNTIME_MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_FEATURE_BOOTSTRAPCPPINITIALIZATION_ENABLED) && (WINDOWSAPPRUNTIME_MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_FEATURE_BOOTSTRAPCPPINITIALIZATION_ENABLED == 1)
#if defined(__cplusplus)
#if defined(WINDOWSAPPSDK_RELEASE_MAJORMINOR) && defined(WINDOWSAPPSDK_RELEASE_VERSION_TAG_W) && defined(WINDOWSAPPSDK_RUNTIME_VERSION_UINT64)
namespace Microsoft::Windows::ApplicationModel
{
class PackageVersion : public PACKAGE_VERSION
{
public:
    PackageVersion() = default;

    // Create an instance with the value `major.0.0.0`.
    PackageVersion(uint16_t major) :
        PACKAGE_VERSION()
    {
        Major = major;
    }

    // Create an instance with the value `major.minor.0.0`.
    PackageVersion(uint16_t major, uint16_t minor) :
        PACKAGE_VERSION()
    {
        Major = major;
        Minor = minor;
    }

    // Create an instance with the value `major.minor.build.0`.
    PackageVersion(uint16_t major, uint16_t minor, uint16_t build) :
        PACKAGE_VERSION()
    {
        Major = major;
        Minor = minor;
        Build = build;
    }

    // Create an instance with the value `major.minor.build.revision`.
    PackageVersion(uint16_t major, uint16_t minor, uint16_t build, uint16_t revision) :
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

#if defined(_STRSAFE_H_INCLUDED_) && defined(WI_VERIFY)
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
    /// Initialize the calling process to use Windows App SDK's framework package.
    /// Failure returns false with the failure HRESULT in the hresult parameter.
    ///
    /// Find a Windows App SDK framework package meeting the criteria and make it available
    /// for use by the current process. If multiple packages meet the criteria the best
    /// candidate is selected.
    ///
    /// @param majorMinorVersion major and minor version of Windows App SDK's framework package, encoded as `0xMMMMNNNN` where M=Major, N=Minor (e.g. 1.2 == 0x00010002).
    /// @param versionTag version tag (if any), e.g. "preview1".
    /// @param minVersion the minimum version to use.
    /// @param hresult the error code if an error occurred.
    /// @see TryInitialize(uint32_t, PCWSTR)
    /// @see Shutdown()
    inline HRESULT TryInitialize(uint32_t majorMinorVersion, PCWSTR versionTag, PackageVersion minVersion)
    {
        const PACKAGE_VERSION{ minVersion.Version };
        return ::MddBootstrapInitialize(majorMinorVersion, versionTag, minVersion);
    }

    /// Initialize the calling process to use Windows App SDK's framework package.
    /// Failure returns false with the failure HRESULT in the hresult parameter.
    ///
    /// Find a Windows App SDK framework package meeting the criteria and make it available
    /// for use by the current process. If multiple packages meet the criteria the best
    /// candidate is selected.
    ///
    /// This is equivalent to `TryInitialize(majorMinorVersion, versionTag, PackageVersion())`.
    ///
    /// @param majorMinorVersion major and minor version of Windows App SDK's framework package, encoded as `0xMMMMNNNN` where M=Major, N=Minor (e.g. 1.2 == 0x00010002).
    /// @param versionTag version tag (if any), e.g. "preview1".
    /// @see TryInitialize(uint32_t, PCWSTR, PackageVersion)
    /// @see Shutdown()
    inline HRESULT TryInitialize(uint32_t majorMinorVersion = WINDOWSAPPSDK_RELEASE_MAJORMINOR,
                                 PCWSTR versionTag = WINDOWSAPPSDK_RELEASE_VERSION_TAG_W)
    {
        const PackageVersion minVersion{};
        return TryInitialize(majorMinorVersion, versionTag, minVersion);
    }

    /// Undo the changes made by Initialize().
    ///
    /// @warning Packages made available via `Initialize()` and
    ///          the Dynamic Dependencies API should not be used after this call.
    /// @see TryInitialize(uint32_t, PCWSTR)
    /// @see TryInitialize(uint32_t, PCWSTR, PackageVersion)
    inline void Shutdown()
    {
        ::MddBootstrapShutdown();
    }

#if defined(_CPPUNWIND) && defined(WIL_ENABLE_EXCEPTIONS)
    /// Initialize the calling process to use Windows App SDK's framework package.
    ///
    /// Find a Windows App SDK framework package meeting the criteria and make it available
    /// for use by the current process. If multiple packages meet the criteria the best
    /// candidate is selected.
    ///
    /// @param majorMinorVersion major and minor version of Windows App SDK's framework package, encoded as `0xMMMMNNNN` where M=Major, N=Minor (e.g. 1.2 == 0x00010002).
    /// @param versionTag version tag (if any), e.g. "preview1".
    /// @param minVersion the minimum version to use
    /// @see Initialize(uint32_t)
    /// @see Initialize(uint32_t, PCWSTR)
    /// @see Shutdown()
    inline void Initialize(uint32_t majorMinorVersion, PCWSTR versionTag, PackageVersion minVersion)
    {
        THROW_IF_FAILED(TryInitialize(majorMinorVersion, versionTag, minVersion));
    }

    /// Initialize the calling process to use Windows App SDK's framework package.
    ///
    /// Find a Windows App SDK framework package meeting the criteria and make it available
    /// for use by the current process. If multiple packages meet the criteria the best
    /// candidate is selected.
    ///
    /// This is equivalent to `Initialize(majorMinorVersion, versionTag, PackageVersion())`.
    ///
    /// @param majorMinorVersion major and minor version of Windows App SDK's framework package, encoded as `0xMMMMNNNN` where M=Major, N=Minor (e.g. 1.2 == 0x00010002).
    /// @param versionTag version tag (if any), e.g. "preview1".
    /// @see Initialize(uint32_t)
    /// @see Initialize(uint32_t, PCWSTR, PackageVersion)
    /// @see Shutdown()
    inline void Initialize(uint32_t majorMinorVersion = WINDOWSAPPSDK_RELEASE_MAJORMINOR,
                           PCWSTR versionTag = WINDOWSAPPSDK_RELEASE_VERSION_TAG_W)
    {
        THROW_IF_FAILED(TryInitialize(majorMinorVersion, versionTag));
    }
#endif // defined(_CPPUNWIND) && defined(WIL_ENABLE_EXCEPTIONS)

    // Automate Boostrap shutdown when leaving scope.
    class AutoShutdown
    {
    public:
        AutoShutdown() = delete;

        ~AutoShutdown()
        {
            Shutdown();
        }
    };

#if defined(_CPPUNWIND) && defined(WIL_ENABLE_EXCEPTIONS)
    // Automate Boostrap initialization and shutdown.
    class AutoInitialize
    {
    public:
        AutoInitialize(uint32_t majorMinorVersion = WINDOWSAPPSDK_RELEASE_MAJORMINOR,
                       PCWSTR versionTag = WINDOWSAPPSDK_RELEASE_VERSION_TAG_W)
        {
            const PackageVersion c_minVersion{ WINDOWSAPPSDK_RUNTIME_VERSION_UINT64 };
            THROW_IF_FAILED(TryInitialize(majorMinorVersion, versionTag, c_minVersion));
        }

        AutoInitialize(uint32_t majorMinorVersion, PCWSTR versionTag, PackageVersion minVersion)
        {
            THROW_IF_FAILED(TryInitialize(majorMinorVersion, versionTag, minVersion));
        }

        ~AutoInitialize()
        {
            Shutdown();
        }
    };
#endif // defined(_CPPUNWIND) && defined(WIL_ENABLE_EXCEPTIONS)
}
}
#endif // defined(WINDOWSAPPSDK_RELEASE_MAJORMINOR) && defined(WINDOWSAPPSDK_RELEASE_VERSION_TAG_W) && defined()WINDOWSAPPSDK_RUNTIME_VERSION_UINT64)
#endif // defined(__cplusplus)
#endif // defined(WINDOWSAPPRUNTIME_MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_FEATURE_BOOTSTRAPCPPINITIALIZATION_ENABLED) && (WINDOWSAPPRUNTIME_MICROSOFT_WINDOWS_APPLICATIONMODEL_DYNAMICDEPENDENCY_FEATURE_BOOTSTRAPCPPINITIALIZATION_ENABLED == 1)


#endif // MDDBOOSTRAP_H
