// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#if !defined(MDDBOOTSTRAP_H)
#define MDDBOOTSTRAP_H

#include <appmodel.h>

#if defined(__cplusplus)
#define MDDBOOTSTRAP_NOEXCEPT   noexcept
#else
#define MDDBOOTSTRAP_NOEXCEPT
#endif // defined(__cplusplus)

/// Options for Bootstrap initialization
typedef enum MddBootstrapInitializeOptions
{
    /// Default behavior
    MddBootstrapInitializeOptions_None = 0,

    /// If not successful call DebugBreak()
    MddBootstrapInitializeOptions_OnError_DebugBreak = 0x0001,

    /// If not successful call DebugBreak() if a debugger is attached to the process
    MddBootstrapInitializeOptions_OnError_DebugBreak_IfDebuggerAttached = 0x0002,

    /// If not successful perform a fail-fast
    MddBootstrapInitializeOptions_OnError_FailFast = 0x0004,

    /// If a compatible Windows App Runtime framework package is not found show UI
    MddBootstrapInitializeOptions_OnNoMatch_ShowUI = 0x0008,

    /// Do nothing (do not error) if the process has package identity
    MddBootstrapInitializeOptions_OnPackageIdentity_NOOP = 0x0010,
} MddBootstrapInitializeOptions;
#if defined(__cplusplus)
DEFINE_ENUM_FLAG_OPERATORS(MddBootstrapInitializeOptions)
#endif // defined(__cplusplus)

/// Initialize the calling process to use Windows App Runtime framework package.
///
/// Find a Windows App Runtime framework package meeting the criteria and make it available
/// for use by the current process. If multiple packages meet the criteria the best
/// candidate is selected.
///
/// If called multiple times the parameters must be compatible with the framework package
/// resolved by the first initialization call (i.e. the framework package currently in use).
/// If the request is not compatible with the framework package currently in use
/// the API fails and an error is returned.
///
/// @param majorMinorVersion the major and minor version to use, e..g 0x00010002 for Major.Minor=1.2
/// @param versionTag the version pre-release identifier, or NULL if none.
/// @param minVersion the minimum version to use
STDAPI MddBootstrapInitialize(
    UINT32 majorMinorVersion,
    PCWSTR versionTag,
    PACKAGE_VERSION minVersion) MDDBOOTSTRAP_NOEXCEPT;

/// Initialize the calling process to use Windows App Runtime framework package.
///
/// Find a Windows App Runtime framework package meeting the criteria and make it available
/// for use by the current process. If multiple packages meet the criteria the best
/// candidate is selected.
///
/// If called multiple times the parameters must be compatible with the framework package
/// resolved by the first initialization call (i.e. the framework package currently in use).
/// If the request is not compatible with the framework package currently in use
/// the API fails and an error is returned.
///
/// @param majorMinorVersion the major and minor version to use, e..g 0x00010002 for Major.Minor=1.2
/// @param versionTag the version pre-release identifier, or NULL if none.
/// @param minVersion the minimum version to use
STDAPI MddBootstrapInitialize2(
    UINT32 majorMinorVersion,
    PCWSTR versionTag,
    PACKAGE_VERSION minVersion,
    MddBootstrapInitializeOptions options) MDDBOOTSTRAP_NOEXCEPT;

/// Undo the changes made by MddBoostrapInitialize().
///
/// @warning Packages made available via MddBootstrapInitialize2() and
///          the Dynamic Dependencies API should not be used after this call.
STDAPI_(void) MddBootstrapShutdown() MDDBOOTSTRAP_NOEXCEPT;

// C++ friendly APIs
#if defined(__cplusplus)
#if defined(WINDOWSAPPSDK_RELEASE_MAJORMINOR) && defined(WINDOWSAPPSDK_RELEASE_VERSION_TAG_W) && defined(WINDOWSAPPSDK_RUNTIME_VERSION_UINT64)

#include <memory>
#include <stdint.h>

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
    namespace details
    {
        struct mddbootstrapshutdown_t;

        struct mddbootstrapshutdown_deleter_t
        {
            void operator()(mddbootstrapshutdown_t*)
            {
                MddBootstrapShutdown();
            }
        };
    }
    using unique_mddbootstrapshutdown = std::unique_ptr<details::mddbootstrapshutdown_t, details::mddbootstrapshutdown_deleter_t>;

    /// Options for Bootstrap initialization APIs.
    /// @see InitializeFailFast(uint32_t, PCWSTR, PackageVersion, InitializeOptions)
    /// @see Initialize(uint32_t, PCWSTR, PackageVersion, InitializeOptions)
    /// @see InitializeNoThrow(uint32_t, PCWSTR, PackageVersion, InitializeOptions)
    enum class InitializeOptions
    {
        /// Default behavior
        None = MddBootstrapInitializeOptions_None,

        /// If not successful call DebugBreak()
        OnError_DebugBreak = MddBootstrapInitializeOptions_OnError_DebugBreak,

        /// If not successful call DebugBreak() if a debugger is attached to the process
        OnError_DebugBreak_IfDebuggerAttached = MddBootstrapInitializeOptions_OnError_DebugBreak_IfDebuggerAttached,

        /// If not successful perform a fail-fast
        OnError_FailFast = MddBootstrapInitializeOptions_OnError_FailFast,

        /// If a compatible Windows App Runtime framework package is not found show UI
        OnNoMatch_ShowUI = MddBootstrapInitializeOptions_OnNoMatch_ShowUI,

        /// Do nothing (do not error) if the process has package identity
        OnPackageIdentity_NOOP = MddBootstrapInitializeOptions_OnPackageIdentity_NOOP,
    };
    DEFINE_ENUM_FLAG_OPERATORS(InitializeOptions)

    /// Call MddBootstrapInitialize2() and aborts the process (via std::abort()) if it fails;
    /// returns an RAII object that reverts the initialization on success.
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
    /// @param options optional behavior
    /// @see Initialize(uint32_t, PCWSTR, PackageVersion, InitializeOptions)
    /// @see InitializeNoThrow(uint32_t, PCWSTR, PackageVersion, InitializeOptions)
    /// @see Shutdown()
    /// ~~~~~
    /// #include <windows.h>
    ///
    /// #include <WindowsAppSDK-VersionInfo.h>
    /// #include <MddBootstrap.h>
    ///
    /// #include <iostream>
    ///
    /// namespace MddBootstrap { using namespace ::Microsoft::Windows::ApplicationModel::DynamicDependency::Bootstrap; }
    ///
    /// int main()
    /// {
    ///     auto mddBootstrapShutdown = MddBootstrap::InitializeFailFast();
    ///     std::cout << "hello world";
    ///     return 0;
    /// }
    /// ~~~~~
    [[nodiscard]] inline unique_mddbootstrapshutdown InitializeFailFast(
        uint32_t majorMinorVersion = WINDOWSAPPSDK_RELEASE_MAJORMINOR,
        PCWSTR versionTag = WINDOWSAPPSDK_RELEASE_VERSION_TAG_W,
        PackageVersion minVersion = WINDOWSAPPSDK_RUNTIME_VERSION_UINT64,
        InitializeOptions options = ::Microsoft::Windows::ApplicationModel::DynamicDependency::Bootstrap::InitializeOptions::None)
    {
        const auto hr{ ::MddBootstrapInitialize2(majorMinorVersion, versionTag, minVersion, static_cast<MddBootstrapInitializeOptions>(options)) };
        if (FAILED(hr))
        {
            std::abort();
        }
        return unique_mddbootstrapshutdown(reinterpret_cast<details::mddbootstrapshutdown_t*>(1));
    }

#if defined(_CPPUNWIND) && defined(WINRT_BASE_H)
    /// Call MddBootstrapInitialize2() and throws an exception if it fails;
    /// returns an RAII object that reverts the initialization on success.
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
    /// @param options optional behavior
    /// @see Initialize_failfast(uint32_t, PCWSTR, PackageVersion, InitializeOptions)
    /// @see Initialize_nothrow(uint32_t, PCWSTR, PackageVersion, InitializeOptions)
    /// @see Shutdown()
    /// @exception winrt::hresult_error thrown if intialization fails; see code() for more details.
    /// ~~~~~
    /// #include <windows.h>
    ///
    /// #include <winrt\base.h>
    ///
    /// #include <WindowsAppSDK-VersionInfo.h>
    /// #include <MddBootstrap.h>
    ///
    /// #include <iostream>
    ///
    /// namespace MddBootstrap { using namespace ::Microsoft::Windows::ApplicationModel::DynamicDependency::Bootstrap; }
    ///
    /// int main()
    /// {
    ///     try
    ///     {
    ///         auto mddBootstrapCleanup = MddBootstrap::Initialize();
    ///         std::cout << "hello world";
    ///     }
    ///     catch (const winrt::hresult_error& ex)
    ///     {
    ///         const auto hr{ ex.code() };
    ///         std::cout << "Error 0x" << std::hex << hr << " in Bootstrap initialization";
    ///         return hr;
    ///     }
    ///     return 0;
    /// }
    /// ~~~~~
    [[nodiscard]] inline unique_mddbootstrapshutdown Initialize(
        uint32_t majorMinorVersion = WINDOWSAPPSDK_RELEASE_MAJORMINOR,
        PCWSTR versionTag = WINDOWSAPPSDK_RELEASE_VERSION_TAG_W,
        PackageVersion minVersion = WINDOWSAPPSDK_RUNTIME_VERSION_UINT64,
        InitializeOptions options = ::Microsoft::Windows::ApplicationModel::DynamicDependency::Bootstrap::InitializeOptions::None)
    {
        winrt::check_hresult(::MddBootstrapInitialize2(majorMinorVersion, versionTag, minVersion, static_cast<MddBootstrapInitializeOptions>(options)));
        return unique_mddbootstrapshutdown(reinterpret_cast<details::mddbootstrapshutdown_t*>(1));
    }
#endif // defined(_CPPUNWIND) && defined(WINRT_BASE_H)

    /// Call MddBootstrapInitialize2() and returns a failure HRESULT if it fails.
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
    /// @param options optional behavior
    /// @see InitializeFailFast(uint32_t, PCWSTR, PackageVersion, InitializeOptions)
    /// @see Initialize(uint32_t, PCWSTR, PackageVersion, InitializeOptions)
    /// @see Shutdown()
    /// ~~~~~
    /// #include <windows.h>
    ///
    /// #include <WindowsAppSDK-VersionInfo.h>
    /// #include <MddBootstrap.h>
    ///
    /// #include <iostream>
    ///
    /// namespace MddBootstrap { using namespace ::Microsoft::Windows::ApplicationModel::DynamicDependency::Bootstrap; }
    ///
    /// int main()
    /// {
    ///     const auto hr{ MddBootstrap::InitializeNoThrow() };
    ///     if (FAILED(hr))
    ///     {
    ///         std::cout << "Error 0x" << std::hex << hr << " in Bootstrap initialization";
    ///         return hr;
    ///     }
    ///     auto mddBootstrapShutdown{ MddBootstrap::unique_mddbootstrapshutdown(reinterpret_cast<MddBootstrap::details::mddbootstrapshutdown_t*>(1)) };
    ///     std::cout << "hello world";
    ///     return 0;
    /// }
    /// ~~~~~
    inline HRESULT InitializeNoThrow(
        uint32_t majorMinorVersion = WINDOWSAPPSDK_RELEASE_MAJORMINOR,
        PCWSTR versionTag = WINDOWSAPPSDK_RELEASE_VERSION_TAG_W,
        PackageVersion minVersion = WINDOWSAPPSDK_RUNTIME_VERSION_UINT64,
        InitializeOptions options = ::Microsoft::Windows::ApplicationModel::DynamicDependency::Bootstrap::InitializeOptions::None)
    {
        return ::MddBootstrapInitialize2(majorMinorVersion, versionTag, minVersion, static_cast<MddBootstrapInitializeOptions>(options));
    }
}
}
#endif // defined(WINDOWSAPPSDK_RELEASE_MAJORMINOR) && defined(WINDOWSAPPSDK_RELEASE_VERSION_TAG_W) && defined(WINDOWSAPPSDK_RUNTIME_VERSION_UINT64)
#endif // defined(__cplusplus)

#endif // MDDBOOTSTRAP_H
