// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include "MddBootstrap.h"
#include "MddBootstrapTest.h"

#include "MsixDynamicDependency.h"

#include "IDynamicDependencyLifetimeManager.h"

#include <filesystem>

HRESULT _MddBootstrapInitialize(
    UINT32 majorMinorVersion,
    PCWSTR versionTag,
    PACKAGE_VERSION minVersion) noexcept;
void VerifyInitializationIsCompatible(
    UINT32 majorMinorVersion,
    PCWSTR versionTag,
    PACKAGE_VERSION minVersion);
void FirstTimeInitialization(
    UINT32 majorMinorVersion,
    PCWSTR versionTag,
    PACKAGE_VERSION minVersion);
wil::unique_cotaskmem_ptr<BYTE[]> GetFrameworkPackageInfoForPackage(PCWSTR packageFullName, const PACKAGE_INFO*& frameworkPackageInfo);
DLL_DIRECTORY_COOKIE AddFrameworkToPath(PCWSTR path);
void RemoveFrameworkFromPath(PCWSTR frameworkPath);
bool IsLifetimeManagerViaEnumeration();
void CreateLifetimeManager(
    UINT32 majorMinorVersion,
    PCWSTR versionTag,
    PACKAGE_VERSION minVersion,
    wil::com_ptr_nothrow<IDynamicDependencyLifetimeManager>& lifetimeManager,
    wil::unique_event& endTheLifetimeManagerEvent,
    wil::unique_cotaskmem_string& ddlmPackageFullName);
void CreateLifetimeManagerViaAppExtension(
    UINT32 majorMinorVersion,
    PCWSTR versionTag,
    PACKAGE_VERSION minVersion,
    wil::com_ptr_nothrow<IDynamicDependencyLifetimeManager>& lifetimeManager,
    wil::unique_cotaskmem_string& ddlmPackageFullName);
void CreateLifetimeManagerViaEnumeration(
    UINT32 majorMinorVersion,
    PCWSTR versionTag,
    PACKAGE_VERSION minVersion,
    wil::unique_event& endTheLifetimeManagerEvent,
    wil::unique_cotaskmem_string& ddlmPackageFullName);
CLSID FindDDLMViaAppExtension(
    UINT32 majorMinorVersion,
    PCWSTR versionTag,
    PACKAGE_VERSION minVersion);
void FindDDLMViaEnumeration(
    UINT32 majorMinorVersion,
    PCWSTR versionTag,
    PACKAGE_VERSION minVersion,
    std::wstring& ddlmPackageFamilyName,
    std::wstring& ddlmPackageFullName);
CLSID GetClsid(const winrt::Windows::ApplicationModel::AppExtensions::AppExtension& appExtension);
bool IsOptionEnabled(PCWSTR name);
HRESULT MddBootstrapInitialize_Log(
    HRESULT hrInitialize,
    UINT32 majorMinorVersion,
    PCWSTR versionTag,
    PACKAGE_VERSION minVersion) noexcept;
HRESULT MddBootstrapInitialize_ShowUI(
    UINT32 majorMinorVersion,
    PCWSTR versionTag,
    PACKAGE_VERSION minVersion);

static std::mutex g_initializationLock;
static std::atomic<uint32_t> g_initializationCount{};

static IDynamicDependencyLifetimeManager* g_lifetimeManager{};
static wil::unique_event g_endTheLifetimeManagerEvent;
static wil::unique_hmodule g_windowsAppRuntimeDll;
static wil::unique_process_heap_string g_packageDependencyId;
static MDD_PACKAGEDEPENDENCY_CONTEXT g_packageDependencyContext{};

static UINT32 g_initializationMajorMinorVersion{};
static std::wstring g_initializationVersionTag;
static PACKAGE_VERSION g_initializationFrameworkPackageVersion{};

static std::wstring g_test_ddlmPackageNamePrefix;
static std::wstring g_test_ddlmPackagePublisherId;

STDAPI MddBootstrapInitialize(
    UINT32 majorMinorVersion,
    PCWSTR versionTag,
    PACKAGE_VERSION minVersion) noexcept
{
    return MddBootstrapInitialize2(majorMinorVersion, versionTag, minVersion, MddBootstrapInitializeOptions_None);
}

STDAPI MddBootstrapInitialize2(
    UINT32 majorMinorVersion,
    PCWSTR versionTag,
    PACKAGE_VERSION minVersion,
    MddBootstrapInitializeOptions options) noexcept try
{
    // Dynamic Dependencies Bootstrap API requires a non-packaged process
    LOG_HR_IF(HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED), AppModel::Identity::IsPackagedProcess());

    // Are we already initialized?
    const auto hr{ _MddBootstrapInitialize(majorMinorVersion, versionTag, minVersion) };
    if (FAILED(hr))
    {
        LOG_IF_FAILED(MddBootstrapInitialize_Log(hr, majorMinorVersion, versionTag, minVersion));

        if (WI_IsFlagSet(options, MddBootstrapInitializeOptions_OnError_DebugBreak) ||
            (WI_IsFlagSet(options, MddBootstrapInitializeOptions_OnError_DebugBreak_IfDebuggerAttached) && IsDebuggerPresent()) ||
            IsOptionEnabled(L"MICROSOFT_WINDOWSAPPRUNTIME_BOOTSTRAP_INITIALIZE_DEBUGBREAK"))
        {
            DebugBreak();
        }

        if (WI_IsFlagSet(options, MddBootstrapInitializeOptions_OnNoMatch_ShowUI) ||
            IsOptionEnabled(L"MICROSOFT_WINDOWSAPPRUNTIME_BOOTSTRAP_INITIALIZE_SHOWUI"))
        {
            LOG_IF_FAILED(MddBootstrapInitialize_ShowUI(majorMinorVersion, versionTag, minVersion));
        }

        if (WI_IsFlagSet(options, MddBootstrapInitializeOptions_OnError_FailFast) ||
            IsOptionEnabled(L"MICROSOFT_WINDOWSAPPRUNTIME_BOOTSTRAP_INITIALIZE_FAILFAST"))
        {
            FAIL_FAST_HR_MSG(hr,
                             "Bootstrap initialize(0x%08X, '%ls', %hu.%hu.%hu.%hu)",
                             majorMinorVersion, (!versionTag ? L"" : versionTag),
                             minVersion.Major, minVersion.Minor, minVersion.Build, minVersion.Revision);
        }
        RETURN_HR(hr);
    }

    // Success!
    ++g_initializationCount;
    return S_OK;
}
CATCH_RETURN();

HRESULT _MddBootstrapInitialize(
    UINT32 majorMinorVersion,
    PCWSTR versionTag,
    PACKAGE_VERSION minVersion) noexcept try
{
    // Are we already initialized?
    auto lock{ std::lock_guard(g_initializationLock) };
    if (g_initializationCount > 0)
    {
        // Verify the request is compatible with our already initialized state
        VerifyInitializationIsCompatible(majorMinorVersion, versionTag, minVersion);
    }
    else
    {
        // First to the key! Do the initialization
        FirstTimeInitialization(majorMinorVersion, versionTag, minVersion);
    }
    return S_OK;
}
CATCH_RETURN();

STDAPI_(void) MddBootstrapShutdown() noexcept
{
    auto lock{ std::lock_guard(g_initializationLock) };
    const auto initializationCount{ g_initializationCount.load() };
    if (initializationCount > 1)
    {
        // Multiply initialized. Just decrement our count
        --g_initializationCount;
        return;
    }
    else if (initializationCount == 0)
    {
        // Not initialized. Nothing to do
        return;
    }

    // Last one out turn out the lights...
    if (g_packageDependencyContext && g_windowsAppRuntimeDll)
    {
        MddRemovePackageDependency(g_packageDependencyContext);
        g_packageDependencyContext = nullptr;
    }

    g_packageDependencyId.reset();

    g_windowsAppRuntimeDll.reset();

    if (g_endTheLifetimeManagerEvent)
    {
        g_endTheLifetimeManagerEvent.SetEvent();
        g_endTheLifetimeManagerEvent.reset();
    }

    if (g_lifetimeManager)
    {
        (void)LOG_IF_FAILED(g_lifetimeManager->Shutdown());
        g_lifetimeManager->Release();
        g_lifetimeManager = nullptr;
    }

    g_initializationMajorMinorVersion = {};
    g_initializationVersionTag.clear();
    g_initializationFrameworkPackageVersion = {};

    --g_initializationCount;
}

STDAPI MddBootstrapTestInitialize(
    _In_ PCWSTR ddlmPackageNamePrefix,
    _In_ PCWSTR ddlPackagePublisherId) noexcept try
{
    RETURN_HR_IF(E_INVALIDARG, !ddlmPackageNamePrefix);
    RETURN_HR_IF(E_INVALIDARG, *ddlmPackageNamePrefix == L'0');
    RETURN_HR_IF(E_INVALIDARG, !ddlPackagePublisherId);
    RETURN_HR_IF(E_INVALIDARG, *ddlPackagePublisherId == L'0');

    g_test_ddlmPackageNamePrefix = ddlmPackageNamePrefix;
    g_test_ddlmPackagePublisherId = ddlPackagePublisherId;
    return S_OK;
} CATCH_RETURN();

void VerifyInitializationIsCompatible(
    UINT32 majorMinorVersion,
    PCWSTR versionTag,
    PACKAGE_VERSION minVersion)
{
    // Sanity check we're already initialized
    // g_lifetimeManager is optional. Don't check it
    // g_endTheLifetimeManagerEvent is optional. Don't check it
    FAIL_FAST_HR_IF(E_UNEXPECTED, g_windowsAppRuntimeDll == nullptr);
    FAIL_FAST_HR_IF(E_UNEXPECTED, g_packageDependencyId == nullptr);
    FAIL_FAST_HR_IF(E_UNEXPECTED, g_packageDependencyContext == nullptr);

    // Is the initialization request compatible with the current initialization state?
    THROW_HR_IF_MSG(MDD_E_BOOTSTRAP_INITIALIZE_INCOMPATIBLE,
                    majorMinorVersion != g_initializationMajorMinorVersion,
                    "MddBootstrapInitialize(***0x%08X***, '%ls', %hu.%hu.%hu.%hu) not compatible with current initialization state (0x%X, '%ls', %hu.%hu.%hu.%hu)",
                    majorMinorVersion, (!versionTag ? L"" : versionTag),
                    minVersion.Major, minVersion.Minor, minVersion.Build, minVersion.Revision,
                    g_initializationMajorMinorVersion, g_initializationVersionTag.c_str(),
                    g_initializationFrameworkPackageVersion.Major, g_initializationFrameworkPackageVersion.Minor,
                    g_initializationFrameworkPackageVersion.Build, g_initializationFrameworkPackageVersion.Revision);
    THROW_HR_IF_MSG(MDD_E_BOOTSTRAP_INITIALIZE_INCOMPATIBLE,
                    CompareStringOrdinal((!versionTag ? L"" : versionTag), -1, g_initializationVersionTag.c_str(), -1, TRUE) != CSTR_EQUAL,
                    "MddBootstrapInitialize(0x%08X, ***'%ls'***, %hu.%hu.%hu.%hu) not compatible with current initialization state (0x%X, '%ls', %hu.%hu.%hu.%hu)",
                    majorMinorVersion, (!versionTag ? L"" : versionTag),
                    minVersion.Major, minVersion.Minor, minVersion.Build, minVersion.Revision,
                    g_initializationMajorMinorVersion, g_initializationVersionTag.c_str(),
                    g_initializationFrameworkPackageVersion.Major, g_initializationFrameworkPackageVersion.Minor,
                    g_initializationFrameworkPackageVersion.Build, g_initializationFrameworkPackageVersion.Revision);
    THROW_HR_IF_MSG(MDD_E_BOOTSTRAP_INITIALIZE_INCOMPATIBLE,
                    minVersion.Version > g_initializationFrameworkPackageVersion.Version,
                    "MddBootstrapInitialize(0x%08X, '%ls', ***%hu.%hu.%hu.%hu***) not compatible with current initialization state (0x%X, '%ls', %hu.%hu.%hu.%hu)",
                    majorMinorVersion, (!versionTag ? L"" : versionTag),
                    minVersion.Major, minVersion.Minor, minVersion.Build, minVersion.Revision,
                    g_initializationMajorMinorVersion, g_initializationVersionTag.c_str(),
                    g_initializationFrameworkPackageVersion.Major, g_initializationFrameworkPackageVersion.Minor,
                    g_initializationFrameworkPackageVersion.Build, g_initializationFrameworkPackageVersion.Revision);
}

void FirstTimeInitialization(
    UINT32 majorMinorVersion,
    PCWSTR versionTag,
    PACKAGE_VERSION minVersion)
{
    // Sanity check we're not already initialized
    // g_lifetimeManager is optional. Don't check it
    // g_endTheLifetimeManagerEvent is optional. Don't check it
    FAIL_FAST_HR_IF(E_UNEXPECTED, g_windowsAppRuntimeDll != nullptr);
    FAIL_FAST_HR_IF(E_UNEXPECTED, g_packageDependencyId != nullptr);
    FAIL_FAST_HR_IF(E_UNEXPECTED, g_packageDependencyContext != nullptr);

    // Make a copy of the versionTag in preparation of succcess
    auto packageVersionTag{ std::wstring(!versionTag ? L"" : versionTag) };

    // Create the lifetime manager
    wil::unique_cotaskmem_string packageFullName;
    wil::com_ptr_nothrow<IDynamicDependencyLifetimeManager> lifetimeManager;
    wil::unique_event endTheLifetimeManagerEvent;
    CreateLifetimeManager(majorMinorVersion, versionTag, minVersion, lifetimeManager, endTheLifetimeManagerEvent, packageFullName);

    const PACKAGE_INFO* frameworkPackageInfo{};
    auto packageInfoBuffer{ GetFrameworkPackageInfoForPackage(packageFullName.get(), frameworkPackageInfo) };

    // Temporarily add the framework's package directory to PATH so LoadLibrary can find it and any colocated imports
    wil::unique_dll_directory_cookie dllDirectoryCookie{ AddFrameworkToPath(frameworkPackageInfo->path) };

    auto windowsAppRuntimeDllFilename{ std::wstring(frameworkPackageInfo->path) + L"\\Microsoft.WindowsAppRuntime.dll" };
    wil::unique_hmodule windowsAppRuntimeDll(LoadLibraryEx(windowsAppRuntimeDllFilename.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH));
    if (!windowsAppRuntimeDll)
    {
        const auto lastError{ GetLastError() };
        THROW_WIN32_MSG(lastError, "Error in LoadLibrary: %d (0x%X) loading %ls", lastError, lastError, windowsAppRuntimeDllFilename.c_str());
    }

    // Add the framework package to the package graph
    const MddPackageDependencyProcessorArchitectures architectureFilter{};
    const auto lifetimeKind{ MddPackageDependencyLifetimeKind::Process };
    const MddCreatePackageDependencyOptions createOptions{};
    wil::unique_process_heap_string packageDependencyId;
    THROW_IF_FAILED(MddTryCreatePackageDependency(nullptr, frameworkPackageInfo->packageFamilyName, minVersion, architectureFilter, lifetimeKind, nullptr, createOptions, &packageDependencyId));
    //
    const MddAddPackageDependencyOptions addOptions{};
    MDD_PACKAGEDEPENDENCY_CONTEXT packageDependencyContext{};
    THROW_IF_FAILED(MddAddPackageDependency(packageDependencyId.get(), MDD_PACKAGE_DEPENDENCY_RANK_DEFAULT, addOptions, &packageDependencyContext, nullptr));

    // Remove our temporary path addition
    RemoveFrameworkFromPath(frameworkPackageInfo->path);
    dllDirectoryCookie.reset();

    // Track our initialized state
    g_lifetimeManager = lifetimeManager.detach();
    g_endTheLifetimeManagerEvent = std::move(endTheLifetimeManagerEvent);
    g_windowsAppRuntimeDll = std::move(windowsAppRuntimeDll);
    g_packageDependencyId = std::move(packageDependencyId);
    g_packageDependencyContext = packageDependencyContext;
    //
    g_initializationMajorMinorVersion = majorMinorVersion;
    g_initializationVersionTag = std::move(packageVersionTag);
    g_initializationFrameworkPackageVersion.Version = frameworkPackageInfo->packageId.version.Version;
}

/// Determine the path for the Windows App Runtime Framework package
wil::unique_cotaskmem_ptr<BYTE[]> GetFrameworkPackageInfoForPackage(PCWSTR packageFullName, const PACKAGE_INFO*& frameworkPackageInfo)
{
    frameworkPackageInfo = nullptr;

    // We need to determine the exact Windows App Runtime Framework package
    // in the Dynamic Dependency Lifetime Manager package's dependencies,
    // as resolved by Windows. A user can have multiple framework packages
    // in a family registered at a time, for multiple reasons:
    //
    //   * Multiple Architectures -- x86/x64 on an x64 machine, x86/arm/arm64/x86ona64 on an arm64 machine, etc
    //   * Multiple Versions -- v1.0.0.0 in use by processes running as pkg1 and v1.0.0.1 in use by processes running as pkg2
    //                          or v1.0.0.0 in use by running processes and v1.0.0.1 in package graphs for packages w/no running process
    //
    // Thus FindPackagesByPackageFamily(pkgfamilyname,...) and PackageManager.FindPackages(user="", pkgfamilyname) could be ambiguous.
    // We need the actual dependency graph known to Windows for the DDLM package where we got our LifetimeManager.
    // That leaves us few options:
    //
    //   * PackageManager.FindPackage(user="", lifetimeManager->GetPackageFullName()).Dependencies
    //   * GetPackageInfo(OpenPackageInfoByFullName(lifetimeManager->GetPackageFullName())
    //
    // We'll go with the latter as the simpler (no COM/WinRT) and more performant solution.

    // Fetch the package graph for the package (per packageFullName)
    wil::unique_package_info_reference packageInfoReference;
    THROW_IF_WIN32_ERROR(OpenPackageInfoByFullName(packageFullName, 0, &packageInfoReference));
    UINT32 bufferLength{};
    UINT32 packageInfoCount{};
    const auto hr{ HRESULT_FROM_WIN32(GetPackageInfo(packageInfoReference.get(), PACKAGE_FILTER_DIRECT, &bufferLength, nullptr, &packageInfoCount)) };
    THROW_HR_IF(hr, hr != HRESULT_FROM_WIN32(ERROR_INSUFFICIENT_BUFFER));
    THROW_HR_IF(E_UNEXPECTED, packageInfoCount == 0);
    auto buffer{ wil::make_unique_cotaskmem<BYTE[]>(bufferLength) };
    THROW_IF_WIN32_ERROR(GetPackageInfo(packageInfoReference.get(), PACKAGE_FILTER_DIRECT, &bufferLength, buffer.get(), &packageInfoCount));

    // Find the Windows App Runtime framework package in the package graph to determine its path
    //
    // NOTE: The Windows App Runtime DDLM package...
    //          * ...has 1 framework package dependency
    //          * ...its framework package dependency's name starts with "Microsoft.WindowsAppRuntime"
    //          * ...its publisher id is "8wekyb3d8bbwe"
    // Any failure to find the DDLM's package graph but not find the expected framework dependency
    // implies the DDLM is improperly built and cannot be used. Of course ThisShouldNeverHappen
    // but a little paranoia isn't a bad thing :-)
    //
    // Verify the package providing the LifetimeManager declares a <PackageDependency> on the Windows App Runtime framework package.
    THROW_HR_IF_MSG(E_UNEXPECTED, packageInfoCount != 1, "PRddlm:%ls PackageGraph.Count:%u", packageFullName, packageInfoCount);
    //
    const PACKAGE_INFO* packageInfo{ reinterpret_cast<const PACKAGE_INFO*>(buffer.get()) };
    const WCHAR c_expectedNamePrefix[]{ L"Microsoft.WindowsAppRuntime" };
    const int c_expectedNamePrefixLength{ ARRAYSIZE(c_expectedNamePrefix) - 1 };
    THROW_HR_IF_MSG(E_UNEXPECTED, CompareStringOrdinal(packageInfo->packageId.name, c_expectedNamePrefixLength, c_expectedNamePrefix, c_expectedNamePrefixLength, TRUE) != CSTR_EQUAL,
                    "PRddlm:%ls Expected.Name:%ls PackageGraph[0].PackageFullName:%ls", packageFullName, c_expectedNamePrefix, packageInfo->packageFullName);
    //
    PCWSTR c_expectedPublisherId{ L"8wekyb3d8bbwe" };
    THROW_HR_IF_MSG(E_UNEXPECTED, CompareStringOrdinal(packageInfo->packageId.publisherId, -1, c_expectedPublisherId, -1, TRUE) != CSTR_EQUAL,
                    "PRddlm:%ls PackageGraph[0].PackageFullName:%ls", packageFullName, packageInfo->packageFullName);

    // Gotcha!
    frameworkPackageInfo = packageInfo;
    return buffer;
}

DLL_DIRECTORY_COOKIE AddFrameworkToPath(PCWSTR frameworkPath)
{
    // Add the framework to the Loader's DllDirectory list
    wil::unique_dll_directory_cookie dllDirectoryCookie{ AddDllDirectory(frameworkPath) };
    THROW_LAST_ERROR_IF_NULL(dllDirectoryCookie);

    // Add the framework the the PATH environment variable
    wil::unique_cotaskmem_string path;
    THROW_IF_FAILED(wil::GetEnvironmentVariableW(L"PATH", path));
    if (path)
    {
        // PATH = frameworkPath + ";" + path
        auto newPath{ wil::str_concat<wil::unique_cotaskmem_string>(frameworkPath, L";", path) };
        THROW_IF_WIN32_BOOL_FALSE(SetEnvironmentVariableW(L"PATH", newPath.get()));
    }
    else
    {
        const auto lastError{ GetLastError() };
        THROW_HR_IF(HRESULT_FROM_WIN32(lastError), lastError != ERROR_ENVVAR_NOT_FOUND);
        THROW_IF_WIN32_BOOL_FALSE(SetEnvironmentVariableW(L"PATH", frameworkPath));
    }

    return dllDirectoryCookie.release();
}

void RemoveFrameworkFromPath(PCWSTR frameworkPath)
{
    // Remove frameworkPath from PATH (previously added by AddFrameworkToPath())

    // PATH should start with frameworkPath since we just prepended it. Remove it
    wil::unique_cotaskmem_string path;
    const auto hr{ wil::TryGetEnvironmentVariableW(L"PATH", path) };
    if (SUCCEEDED(hr) && path)
    {
        const auto pathLength{ wcslen(path.get()) };
        const auto frameworkPathLength{ wcslen(frameworkPath) };
        if (pathLength >= frameworkPathLength)
        {
            if (CompareStringOrdinal(path.get(), static_cast<int>(frameworkPathLength), frameworkPath, static_cast<int>(frameworkPathLength), TRUE) == CSTR_EQUAL)
            {
                PCWSTR pathWithoutFrameworkPath{ path.get() + frameworkPathLength };
                if (*pathWithoutFrameworkPath == L';')
                {
                    ++pathWithoutFrameworkPath;
                }
                (void)LOG_IF_WIN32_BOOL_FALSE(SetEnvironmentVariableW(L"PATH", pathWithoutFrameworkPath));
            }
            else
            {
                (void)LOG_HR_MSG(E_UNEXPECTED, "PATH doesn't start with %ls", frameworkPath);
            }
        }
    }
}

bool IsLifetimeManagerViaEnumeration()
{
    // AppExtension enumerates appextensions on <=19H1 only if the caller declares a matching AppExtensionHost.
    // To workaround on older systems we'll fallback to a more complex but functionally equivalent solution.
    if (!WindowsVersion::IsWindows10_20H1OrGreater())
    {
        // Windows version < 20H1. Enumeration is required
        return true;
    }

    // Select the LifetimeManager implementation if the environment variable
    // MICROSOFT_WINDOWSAPPRUNTIME_DDLM_ALGORITHM is defined (for testing scenarios)
    // where:
    //     envvar=0 => Enumeration
    //     envvar=1 => AppExtension
    {
        WCHAR value[1 + 1]{};
        if (GetEnvironmentVariableW(L"MICROSOFT_WINDOWSAPPRUNTIME_DDLM_ALGORITHM", value, ARRAYSIZE(value)) == 1)
        {
            if (*value == L'0')
            {
                return true;
            }
            else if (*value == L'1')
            {
                return false;
            }
        }
    }

    // Elevated processes MUST use Enumeration.
    // MediumIL can go either way so we'll favor it too.
    // AppContainer cannot use Enumeration (unless we have the packageQuery capability, which is uncommon).
    if (!wil::get_token_is_app_container())
    {
        return true;
    }

    // Use the AppExtension-style LifetimeManager
    return false;
}

void CreateLifetimeManager(
    UINT32 majorMinorVersion,
    PCWSTR versionTag,
    PACKAGE_VERSION minVersion,
    wil::com_ptr_nothrow<IDynamicDependencyLifetimeManager>& lifetimeManager,
    wil::unique_event& endTheLifetimeManagerEvent,
    wil::unique_cotaskmem_string& ddlmPackageFullName)
{
    if (IsLifetimeManagerViaEnumeration())
    {
        CreateLifetimeManagerViaEnumeration(majorMinorVersion, versionTag, minVersion, endTheLifetimeManagerEvent, ddlmPackageFullName);
    }
    else
    {
        CreateLifetimeManagerViaAppExtension(majorMinorVersion, versionTag, minVersion, lifetimeManager, ddlmPackageFullName);
    }
}

void CreateLifetimeManagerViaAppExtension(
    UINT32 majorMinorVersion,
    PCWSTR versionTag,
    PACKAGE_VERSION minVersion,
    wil::com_ptr_nothrow<IDynamicDependencyLifetimeManager>& lifetimeManager,
    wil::unique_cotaskmem_string& ddlmPackageFullName)
{
    const auto appDynamicDependencyLifetimeManagerClsid{ FindDDLMViaAppExtension(majorMinorVersion, versionTag, minVersion) };

    wil::com_ptr_nothrow<IDynamicDependencyLifetimeManager> dynamicDependencyLifetimeManager{
        wil::CoCreateInstance<IDynamicDependencyLifetimeManager>(appDynamicDependencyLifetimeManagerClsid, CLSCTX_LOCAL_SERVER)
    };

    THROW_IF_FAILED(dynamicDependencyLifetimeManager->Initialize());

    wil::unique_cotaskmem_string packageFullName;
    THROW_IF_FAILED(dynamicDependencyLifetimeManager->GetPackageFullName(&packageFullName));

    lifetimeManager = std::move(dynamicDependencyLifetimeManager);
    ddlmPackageFullName = std::move(packageFullName);
}

void CreateLifetimeManagerViaEnumeration(
    UINT32 majorMinorVersion,
    PCWSTR versionTag,
    PACKAGE_VERSION minVersion,
    wil::unique_event& endTheLifetimeManagerEvent,
    wil::unique_cotaskmem_string& ddlmPackageFullName)
{
    std::wstring packageFamilyName;
    std::wstring packageFullName;
    FindDDLMViaEnumeration(majorMinorVersion, versionTag, minVersion, packageFamilyName, packageFullName);

    // Create the named event used later to signal to the lifetime manager it's time to quit
    // The named event has the syntax: "<processid>;<packagefullname>;<uniqueid>"
    GUID uniqueId{};
    THROW_IF_FAILED(CoCreateGuid(&uniqueId));
    const auto c_uniqueIdAsString{ winrt::to_hstring(uniqueId) };
    auto eventName{ wil::str_printf<wil::unique_cotaskmem_string>(L"%u;%s;%s", GetCurrentProcessId(), packageFullName.c_str(), c_uniqueIdAsString.c_str()) };
    wil::unique_event event;
    event.create(wil::EventOptions::ManualReset, eventName.get());

    WCHAR lifetimeManagerApplicationUserModelId[APPLICATION_USER_MODEL_ID_MAX_LENGTH]{};
    uint32_t lifetimeManagerApplicationUserModelIdLength{ ARRAYSIZE(lifetimeManagerApplicationUserModelId) };
    PCWSTR c_packageRelativeApplicationId{ L"DDLM" };
    THROW_IF_WIN32_ERROR(FormatApplicationUserModelId(packageFamilyName.c_str(), c_packageRelativeApplicationId, &lifetimeManagerApplicationUserModelIdLength, lifetimeManagerApplicationUserModelId));

    wil::com_ptr_nothrow<IApplicationActivationManager> aam{
        wil::CoCreateInstance<IApplicationActivationManager>(CLSID_ApplicationActivationManager, CLSCTX_INPROC_SERVER)
    };
    auto arguments{ eventName.get() };
    ACTIVATEOPTIONS c_options{ AO_NOERRORUI | AO_NOSPLASHSCREEN };
    DWORD processId{};
    THROW_IF_FAILED(aam->ActivateApplication(lifetimeManagerApplicationUserModelId, arguments, c_options, &processId));

    endTheLifetimeManagerEvent = std::move(event);
    ddlmPackageFullName = wil::make_cotaskmem_string(packageFullName.c_str());
}

CLSID FindDDLMViaAppExtension(
    UINT32 majorMinorVersion,
    PCWSTR versionTag,
    PACKAGE_VERSION minVersion)
{
    // Find the best fit
    bool foundAny{};
    PACKAGE_VERSION bestFitVersion{};
    CLSID bestFitClsid{};

    // Look for windows.appExtension with name="microsoft.winappruntime.ddlm-<majorversion>.<minorversion>-<shortarchitecture>[-shorttag]"
    // NOTE: <majorversion>.<minorversion> MUST have a string length <= 8 characters ("12.34567", "12345.67", etc) to fit within
    //       the maximum allowed length of a windows.appExtension's Name (39 chars) on Windows versions <= RS5 (10.0.17763.0).
    WCHAR appExtensionName[100]{};
    const UINT16 majorVersion{ HIWORD(majorMinorVersion) };
    const UINT16 minorVersion{ LOWORD(majorMinorVersion) };
    const auto versionShortTag{ AppModel::Identity::GetVersionShortTagFromVersionTag(versionTag) };
    if (!versionShortTag.empty())
    {
        wsprintf(appExtensionName, L"microsoft.winappruntime.ddlm-%hu.%hu-%s-%s", majorVersion, minorVersion, AppModel::Identity::GetCurrentArchitectureAsShortString(), versionShortTag.c_str());
    }
    else
    {
        wsprintf(appExtensionName, L"microsoft.winappruntime.ddlm-%hu.%hu-%s", majorVersion, minorVersion, AppModel::Identity::GetCurrentArchitectureAsShortString());
    }

    auto catalog{ winrt::Windows::ApplicationModel::AppExtensions::AppExtensionCatalog::Open(appExtensionName) };
    auto appExtensions{ catalog.FindAllAsync().get() };
    for (auto appExtension : appExtensions)
    {
        // Check the package identity against the package identity test qualifiers (if any)
        if (!g_test_ddlmPackageNamePrefix.empty())
        {
            const auto packageId{ appExtension.Package().Id() };
            std::wstring name{ packageId.Name().c_str() };
            if ((name.rfind(g_test_ddlmPackageNamePrefix.c_str(), 0) != 0) ||
                (CompareStringOrdinal(packageId.PublisherId().c_str(), -1, g_test_ddlmPackagePublisherId.c_str(), -1, TRUE) != CSTR_EQUAL))
            {
                // The package's Name prefix or PublisherId don't match the expected value. Skip it
                continue;
            }
        }

        // appExtension.Id == "ddlm-<major.minor.build.revision>-<architecture>"
        const auto id{ appExtension.Id() };
        PACKAGE_VERSION version{};
        WCHAR architectureAsString[9 + 1]{};
        const auto maxIdLength{ ARRAYSIZE(L"ddlm-12345.12345.12345.12345-abcdefghi") - 1 }; // -1 for length not counting null-terminator
        if ((id.size() >= maxIdLength) ||
            (swscanf_s(id.c_str(), L"ddlm-%hu.%hu.%hu.%hu-%9s", &version.Major, &version.Minor, &version.Build, &version.Revision, architectureAsString, static_cast<unsigned>(ARRAYSIZE(architectureAsString))) != 5))
        {
            (void)LOG_WIN32_MSG(ERROR_INVALID_DATA, "%ls", id.c_str());
            continue;
        }

        // Does the version meet the minVersion criteria?
        if (version.Version < minVersion.Version)
        {
            continue;
        }

        // Does the architecture match?
        const auto architecture{ AppModel::Identity::ParseArchitecture(architectureAsString) };
        if (architecture != AppModel::Identity::GetCurrentArchitecture())
        {
            continue;
        }

        // Do we have a package under consideration?
        if (!foundAny)
        {
            bestFitVersion = version;
            bestFitClsid = GetClsid(appExtension);
            foundAny = true;
            continue;
        }

        // Do we already have a higher version under consideration?
        if (bestFitVersion.Version < version.Version)
        {
            bestFitVersion = version;
            bestFitClsid = GetClsid(appExtension);
            continue;
        }
    }
    THROW_HR_IF_MSG(HRESULT_FROM_WIN32(ERROR_NO_MATCH), !foundAny, "AppExtension.Name=%ls, Major=%hu, Minor=%hu, Tag=%ls, MinVersion=%hu.%hu.%hu.%hu",
                    appExtensionName, majorVersion, minorVersion, (!versionTag ? L"" : versionTag),
                    minVersion.Major, minVersion.Minor, minVersion.Build, minVersion.Revision);
    return bestFitClsid;
}

void FindDDLMViaEnumeration(
    UINT32 majorMinorVersion,
    PCWSTR versionTag,
    PACKAGE_VERSION minVersion,
    std::wstring& ddlmPackageFamilyName,
    std::wstring& ddlmPackageFullName)
{
    // Find the best fit
    bool foundAny{};
    PACKAGE_VERSION bestFitVersion{};
    winrt::hstring bestFitPackageFamilyName{};
    winrt::hstring bestFitPackageFullName{};

    // We need to look for DDLM packages in the package family for release <major>.<minor> and <versiontag>
    // But we have no single (simple) enumeration to match that so our logic's more involved compared
    // to FindDDLMViaAppExtension():
    // 1. Look for Framework packages with Name="microsoft.winappruntime.ddlm.<minorversion>*[-shorttag]"
    // 1a. Enumerate all Framework packages registered to the user
    // 1b. Only consider packages whose Name starts with "microsoft.winappruntime.ddlm.<minorversion>."
    // 1c. If versiontag is specified, Only consider packages whose Name ends with [-shorttag]
    // 1d. Only consider packages whose PublisherID = "8wekyb3d8bbwe"
    // 2. Check if the package is in the <majorversion>.<minorversion> release
    // 2a. Check if the package's Description starts with "Microsoft Windows App Runtime DDLM <majorversion>.<minorversion> "
    // 3. Check if the architecture matches
    // 4. Check if the package meets the specified minVersion

    const UINT16 majorVersion{ HIWORD(majorMinorVersion) };
    const UINT16 minorVersion{ LOWORD(majorMinorVersion) };
    PCWSTR packageNamePrefix{};
    if (!g_test_ddlmPackageNamePrefix.empty())
    {
        packageNamePrefix = g_test_ddlmPackageNamePrefix.c_str();
    }
    else
    {
        packageNamePrefix = L"microsoft.winappruntime.ddlm.";
    }
    const auto packageNamePrefixLength{ wcslen(packageNamePrefix) };

    WCHAR packageNameSuffix[10]{};
    size_t packageNameSuffixLength{};
    const auto versionShortTag{ AppModel::Identity::GetVersionShortTagFromVersionTag(versionTag) };
    if (!versionShortTag.empty())
    {
        packageNameSuffix[0] = L'-';
        FAIL_FAST_IF_FAILED(StringCchCopyW(packageNameSuffix + 1, ARRAYSIZE(packageNameSuffix) - 1, versionShortTag.c_str()));
        packageNameSuffixLength = wcslen(packageNameSuffix);
    }

    PCWSTR expectedPublisherId{ L"8wekyb3d8bbwe" };
    if (!g_test_ddlmPackagePublisherId.empty())
    {
        expectedPublisherId = g_test_ddlmPackagePublisherId.c_str();
    }

    auto criteria{ wil::str_printf<wil::unique_cotaskmem_string>(L"Major.Minor=%hu.%hu, Tag=%ls, MinVersion=%hu.%hu.%hu.%hu",
                                                                 majorVersion, minorVersion, (!versionTag ? L"" : versionTag),
                                                                 minVersion.Major, minVersion.Minor, minVersion.Build, minVersion.Revision) };

    winrt::Windows::Management::Deployment::PackageManager packageManager;
    winrt::hstring currentUser;
    const auto c_packageTypes{ winrt::Windows::Management::Deployment::PackageTypes::Main };
    auto packages{ packageManager.FindPackagesForUserWithPackageTypes(currentUser, c_packageTypes) };
    (void)LOG_HR_MSG(MDD_E_BOOTSTRAP_INITIALIZE_SCAN_FOR_DDLM, "Bootstrap.Intitialize: Scanning packages for %ls", criteria.get());
    int packagesScanned{};
    for (auto package : packages)
    {
        ++packagesScanned;

        // Check the package identity against the package identity test qualifiers (if any)
        const auto packageId{ package.Id() };
        const auto packageName{ packageId.Name() };
        const auto packageNameLength{ packageName.size() };
        if (packageNameLength < packageNamePrefixLength + packageNameSuffixLength)
        {
            // The package's Name can't match the expected prefix and/or suffix. Skip it
            continue;
        }
        if (CompareStringOrdinal(packageName.c_str(), static_cast<int>(packageNamePrefixLength), packageNamePrefix, static_cast<int>(packageNamePrefixLength), TRUE) != CSTR_EQUAL)
        {
            // The package's Name prefix doesn't match the expected value. Skip it
            continue;
        }
        if (packageNameSuffixLength > 0)
        {
            const auto offsetToSuffix{ packageNameLength - packageNameSuffixLength };
            if (CompareStringOrdinal(packageName.c_str() + offsetToSuffix, static_cast<int>(packageNameSuffixLength), packageNameSuffix, static_cast<int>(packageNameSuffixLength), TRUE) != CSTR_EQUAL)
            {
                // The package's Name suffix doesn't match the expected value. Skip it
                continue;
            }
        }
        if (CompareStringOrdinal(packageId.PublisherId().c_str(), -1, expectedPublisherId, -1, TRUE) != CSTR_EQUAL)
        {
            // The package's PublisherId doesn't match the expected value. Skip it
            continue;
        }

        // Is this DDLM in the major.minor release?
        //
        // NOTE: Package.InstalledLocation.Path can be expensive as it has to create
        //       a StorageFolder just to get the path as a string. We'd like to use
        //       Package.EffectivePath but that didn't exist until 20H1 and we need
        //       to work down to RS5. So instead we'll use GetPackagePathByFullName()
        //       as that exists since Win81 (and can be significantly faster than
        //       Package.InstalledLocation).
        const auto packageFullName{ packageId.FullName() };
        wil::unique_cotaskmem_string packagePathBufferDynamic;
        uint32_t packagePathLength{};
        const auto rc{ GetPackagePathByFullName(packageFullName.c_str(), &packagePathLength, nullptr) };
        if (rc != ERROR_INSUFFICIENT_BUFFER)
        {
            THROW_HR_MSG(HRESULT_FROM_WIN32(rc), "Enumeration: %ls", packageFullName.c_str());
        }
        auto packagePath{ wil::make_cotaskmem_string_nothrow(nullptr, packagePathLength) };
        THROW_IF_WIN32_ERROR(GetPackagePathByFullName(packageFullName.c_str(), &packagePathLength, packagePath.get()));
        auto fileSpec{ std::filesystem::path(packagePath.get()) };
        fileSpec /= L"Microsoft.WindowsAppRuntime.Release!*";
        //
        WIN32_FIND_DATA findFileData{};
        wil::unique_hfind hfind{ FindFirstFile(fileSpec.c_str(), &findFileData) };
        if (!hfind)
        {
            // The package's release version couldn't be determined. Skip it
            (void)LOG_LAST_ERROR_MSG("Enumeration: FindFirst(%ls)", fileSpec.c_str());
            continue;
        }
        uint16_t releaseMajorVersion{};
        uint16_t releaseMinorVersion{};
        if (swscanf_s(findFileData.cFileName, L"Microsoft.WindowsAppRuntime.Release!%hu.%hu", &releaseMajorVersion, &releaseMinorVersion) != 2)
        {
            // These aren't the droids you're looking for...
            (void)LOG_LAST_ERROR_MSG("Enumeration: FindFirst(%ls) found %ls", fileSpec.c_str(), findFileData.cFileName);
            continue;
        }
        if ((releaseMajorVersion != majorVersion) || (releaseMinorVersion != minorVersion))
        {
            // The package's major or minor release version doesn't match the expected value. Skip it
            continue;
        }

        // Does the version meet the minVersion criteria?
        auto packageVersion{ packageId.Version() };
        PACKAGE_VERSION version{};
        version.Major = packageVersion.Major;
        version.Minor = packageVersion.Minor;
        version.Build = packageVersion.Build;
        version.Revision = packageVersion.Revision;
        if (version.Version < minVersion.Version)
        {
            (void)LOG_HR_MSG(MDD_E_BOOTSTRAP_INITIALIZE_DDLM_SCAN_NO_MATCH,
                             "Bootstrap.Intitialize: %ls not applicable. Version doesn't match MinVersion criteria (%ls)",
                             packageFullName.c_str(), criteria.get());
            continue;
        }

        // Does the architecture match?
        const auto architecture{ packageId.Architecture() };
        const auto currentArchitecture{ AppModel::Identity::GetCurrentArchitecture() };
        if (architecture != currentArchitecture)
        {
            (void)LOG_HR_MSG(MDD_E_BOOTSTRAP_INITIALIZE_DDLM_SCAN_NO_MATCH,
                             "Bootstrap.Intitialize: %ls not applicable. Architecture doesn't match current architecture %ls (%ls)",
                             packageFullName.c_str(), ::AppModel::Identity::GetCurrentArchitectureAsString(), criteria.get());
            continue;
        }

        // Do we have a package under consideration?
        if (!foundAny)
        {
            (void)LOG_HR_MSG(MDD_E_BOOTSTRAP_INITIALIZE_DDLM_SCAN_MATCH,
                             "Bootstrap.Intitialize: %ls is applicable (%ls)",
                             packageFullName.c_str(), criteria.get());
            bestFitVersion = version;
            bestFitPackageFamilyName = packageId.FamilyName();
            bestFitPackageFullName = packageId.FullName();
            foundAny = true;
            continue;
        }

        // Do we already have a higher version under consideration?
        if (bestFitVersion.Version < version.Version)
        {
            (void)LOG_HR_MSG(MDD_E_BOOTSTRAP_INITIALIZE_DDLM_SCAN_MATCH,
                             "Bootstrap.Intitialize: %ls is more applicable (%ls)",
                             packageFullName.c_str(), criteria.get());
            bestFitVersion = version;
            bestFitPackageFamilyName = packageId.FamilyName();
            bestFitPackageFullName = packageId.FullName();
            continue;
        }
    }
    THROW_HR_IF_MSG(HRESULT_FROM_WIN32(ERROR_NO_MATCH), !foundAny, "Enumeration: %ls", criteria.get());
    (void)LOG_HR_MSG(MDD_E_BOOTSTRAP_INITIALIZE_DDLM_FOUND,
                     "Bootstrap.Intitialize: %ls best matches the criteria (%ls) of %d packages scanned",
                     bestFitPackageFullName.c_str(), criteria.get(), packagesScanned);
    ddlmPackageFamilyName = bestFitPackageFamilyName.c_str();
    ddlmPackageFullName = bestFitPackageFullName.c_str();
}

CLSID GetClsid(const winrt::Windows::ApplicationModel::AppExtensions::AppExtension& appExtension)
{
    const auto properties{ appExtension.GetExtensionPropertiesAsync().get() };
    auto propertiesClsid{ properties.Lookup(L"CLSID").as<winrt::Windows::Foundation::Collections::IPropertySet>() };
    auto value{ propertiesClsid.Lookup(L"#text").as<winrt::Windows::Foundation::IPropertyValue>() };
    THROW_HR_IF_NULL(E_UNEXPECTED, value);
    THROW_HR_IF(E_UNEXPECTED, value.Type() != winrt::Windows::Foundation::PropertyType::String);
    const auto text{ value.GetString() };

    // Convert the CLSID as a string to a CLSID as a GUID
    // Problem: CLSIDFromString() also does a lookup for a registered object by the CLSID.
    //          We just want the string->GUID conversion, not any additional work.
    // Workaround this by using UuidFromString()

    // Problem: UuidFromString() takes a RPC_WSTR but that's defined as unsigned short*
    //          unless RPC_USE_NATIVE_WCHAR is defined.
    // Workaround this with casts. Include some asserts to verify we're not misusing memory.

    auto textString{ const_cast<PWSTR>(text.c_str()) };
    auto textRpcString{ reinterpret_cast<RPC_WSTR>(textString) };

    static_assert(sizeof(textString) == sizeof(textRpcString));
    static_assert(sizeof(textString[0]) == sizeof(textRpcString[0]));

    UUID clsid{};
    THROW_IF_WIN32_ERROR(UuidFromStringW(textRpcString, &clsid));
    return clsid;
}

bool IsOptionEnabled(PCWSTR name)
{
    WCHAR value[1 + 1]{};
    if (GetEnvironmentVariableW(name, value, ARRAYSIZE(value)) == 1)
    {
        if (*value == L'0')
        {
            return false;
        }
        else if (*value == L'1')
        {
            return true;
        }
    }
    return false;
}

HRESULT MddBootstrapInitialize_Log(
    HRESULT hrInitialize,
    UINT32 majorMinorVersion,
    PCWSTR versionTag,
    PACKAGE_VERSION minVersion) noexcept try
{
    HANDLE hEventLog{ RegisterEventSourceW(nullptr, L"Windows App Runtime") };
    RETURN_LAST_ERROR_IF_NULL(hEventLog);

    const DWORD c_eventId{ static_cast<DWORD>(hrInitialize) };
    PCWSTR message1{ L"Windows App Runtime" };
    WCHAR message2[1024]{};
    PCWSTR message2Format{ L"ERROR 0x%08X: Bootstrapper initialization failed while looking for version %hu.%hu%s (MSIX package version >= %hu.%hu.%hu.%hu)" };
    const UINT16 majorVersion{ HIWORD(majorMinorVersion) };
    const UINT16 minorVersion{ LOWORD(majorMinorVersion) };
    WCHAR formattedVersionTag[64]{};
    if (versionTag && (versionTag[0] != L'\0'))
    {
        FAIL_FAST_IF_FAILED(StringCchPrintfW(formattedVersionTag, ARRAYSIZE(formattedVersionTag), L"-%s", versionTag));
    }
    FAIL_FAST_IF_FAILED(StringCchPrintfW(message2, ARRAYSIZE(message2), message2Format,
                                         hrInitialize, majorVersion, minorVersion, formattedVersionTag,
                                         minVersion.Major, minVersion.Minor, minVersion.Build, minVersion.Revision));
    PCWSTR strings[2]{ message1, message2 };
    LOG_IF_WIN32_BOOL_FALSE(ReportEventW(hEventLog, EVENTLOG_ERROR_TYPE, 0, c_eventId, nullptr, ARRAYSIZE(strings), 0, strings, nullptr));

    DeregisterEventSource(hEventLog);

    return S_OK;
}
CATCH_RETURN()

HRESULT MddBootstrapInitialize_ShowUI(
    UINT32 majorMinorVersion,
    PCWSTR versionTag,
    PACKAGE_VERSION minVersion)
{
    //TODO: Show this if ERROR_NO_MATCH vs simpler MessageBox("ERROR 0xN in Bootstrapper initialize", MB_OK) ?

    // Get the message caption
    PCWSTR caption{};
    wil::unique_cotaskmem_string captionString;
    WCHAR captionOnError[100]{};
    try
    {
        PCWSTR executable{};
        wil::unique_cotaskmem_string module;
        auto hr{ LOG_IF_FAILED(wil::GetModuleFileNameW(nullptr, module)) };
        if (SUCCEEDED(hr))
        {
            auto delimiter{ wcsrchr(module.get(), L'\\') };
            if (delimiter)
            {
                executable = delimiter + 1;
            }
            else
            {
                executable = module.get();
            }
            PCWSTR captionSuffix{ L"This application could not be started" };
            captionString = wil::str_printf<wil::unique_cotaskmem_string>(L"%s - %s", executable, captionSuffix);
            caption = captionString.get();
        }
    }
    catch (...)
    {
    }
    if (!caption)
    {
        LOG_IF_FAILED(StringCchPrintfW(captionOnError, ARRAYSIZE(captionOnError),
                                       L"<Process %d> - This application could not be started",
                                       GetCurrentProcessId()));
        caption = captionOnError;
    }

    // Get the message body
    WCHAR text[1024]{};
    PCWSTR textFormat{ L"This application requires the Windows App Runtime\n"
                       L"    Version %hu.%hu%s\n"
                       L"    (MSIX package version >= %hu.%hu.%hu.%hu)\n"
                       L"\n"
                       L"Do you want to install a compatible Windows App Runtime now?"
                     };
    const UINT16 majorVersion{ HIWORD(majorMinorVersion) };
    const UINT16 minorVersion{ LOWORD(majorMinorVersion) };
    WCHAR formattedVersionTag[64]{};
    if (versionTag && (versionTag[0] != L'\0'))
    {
        FAIL_FAST_IF_FAILED(StringCchPrintfW(formattedVersionTag, ARRAYSIZE(formattedVersionTag), L"-%s", versionTag));
    }
    FAIL_FAST_IF_FAILED(StringCchPrintfW(text, ARRAYSIZE(text), textFormat,
                                         majorVersion, minorVersion, formattedVersionTag,
                                         minVersion.Major, minVersion.Minor, minVersion.Build, minVersion.Revision));

    // Show the prompt
    const auto yesno{ MessageBoxW(nullptr, text, caption, MB_YESNO | MB_ICONERROR) };
    if (yesno == IDYES)
    {
        SHELLEXECUTEINFOW sei{};
        sei.cbSize = sizeof(sei);
        sei.lpVerb = L"open";
        sei.lpFile = L"https://docs.microsoft.com/en-us/windows/apps/windows-app-sdk/downloads";
        //TODO:Replace with https://aka.ms/windowsappsdk/<major>.<minor>/latest/windowsappruntimeinstall-<architecture>.exe
        sei.nShow = SW_SHOWNORMAL;
        LOG_IF_WIN32_BOOL_FALSE(ShellExecuteExW(&sei));
    }
    return S_OK;
}
