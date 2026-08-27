// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <Microsoft.Utf8.h>

#include "WindowsAppRuntime.VersionInfo.h"

#include "MddWin11.h"

// Function prototype of the function exported by the resource DLL
// (defined later in the build pipeline so we can't #include a header from there)
STDAPI_(const void*) WindowsAppRuntime_GetVersionInfo();

static std::wstring g_test_frameworkPackageFamilyName;
static std::wstring g_test_mainPackageFamilyName;
static std::atomic<const ::Microsoft::WindowsAppSDK::VersionInfo*> g_versionInfo{};

static const ::Microsoft::WindowsAppSDK::VersionInfo c_noVersionInfo{};

namespace Microsoft::WindowsAppRuntime::VersionInfo
{
class RuntimeInformation
{
public:
    static HRESULT GetFrameworkPackageFamilyName(PCWSTR* packageFamilyName)
    {
        if (!g_test_frameworkPackageFamilyName.empty())
        {
            *packageFamilyName = g_test_frameworkPackageFamilyName.c_str();
            return S_OK;
        }

        const uint32_t c_frameworkPackageFamilyNameResourceId{ 10002 };
        static OptionalResourceString frameworkPackageFamilyName{ c_frameworkPackageFamilyNameResourceId };
        if (!frameworkPackageFamilyName.Module)
        {
            return HRESULT_FROM_WIN32(ERROR_MOD_NOT_FOUND);
        }

        *packageFamilyName = frameworkPackageFamilyName.Value.c_str();
        RETURN_HR_IF_MSG(E_UNEXPECTED, frameworkPackageFamilyName.Value.empty(), "WindowsAppSDK framework PackageFamilyName resource not valid (\"\")");
        return S_OK;
    }

    static const std::wstring& GetMainPackageFamilyName()
    {
        if (!g_test_mainPackageFamilyName.empty())
        {
            return g_test_mainPackageFamilyName;
        }

        const uint32_t c_mainPackageFamilyNameResourceId{ 10002 };
        static wil::unique_hmodule module{ LoadResourceModule(true) };
        static std::wstring mainPackageFamilyName{ LoadStringWFromResource(module.get(), c_mainPackageFamilyNameResourceId) };
        return mainPackageFamilyName;
    }

public:
    static const ::Microsoft::WindowsAppSDK::VersionInfo* GetVersionInfo()
    {
        if (!g_versionInfo)
        {
            static wil::unique_hmodule module{ LoadResourceModule(false) };
            if (!module)
            {
                return nullptr;
            }

            auto getVersionInfo{ GetProcAddressByFunctionDeclaration(module.get(), WindowsAppRuntime_GetVersionInfo) };
            THROW_LAST_ERROR_IF_NULL(getVersionInfo);

            g_versionInfo = static_cast<const ::Microsoft::WindowsAppSDK::VersionInfo*>(getVersionInfo());
        }
        return g_versionInfo;
    }

private:
    struct OptionalResourceString
    {
        explicit OptionalResourceString(uint32_t id) :
            Module{ LoadResourceModule(false) },
            Value{ Module ? LoadStringWFromResource(Module.get(), id) : std::wstring{} }
        {
        }

        wil::unique_hmodule Module;
        std::wstring Value;
    };

    static std::wstring LoadStringWFromResource(HMODULE module, uint32_t id)
    {
        const uint32_t c_ResourceMaxLength{ 1024 };
        char resourceValue[c_ResourceMaxLength]{};
        const auto resourceValueLength{ ::LoadStringA(module, id, resourceValue, ARRAYSIZE(resourceValue)) };
        THROW_LAST_ERROR_IF_MSG(resourceValueLength == 0, "Failed to load resource string. id: %u", id);
        return ::Microsoft::Utf8::ToUtf16<std::wstring>(resourceValue);
    }

    static wil::unique_hmodule LoadResourceModule(bool required)
    {
        const PCWSTR c_resourceDllName{ L"Microsoft.WindowsAppRuntime.Insights.Resource.dll" };
        wil::unique_hmodule resourceDllHandle(::LoadLibraryW(c_resourceDllName));
        if (!resourceDllHandle)
        {
            const auto lastError{ ::GetLastError() };
            if (!required && (lastError == ERROR_MOD_NOT_FOUND))
            {
                return {};
            }
            THROW_HR_MSG(HRESULT_FROM_WIN32(lastError), "Unable to load resource dll. %ls", c_resourceDllName);
        }
        return resourceDllHandle;
    }
};
}

STDAPI WindowsAppRuntime_VersionInfo_MSIX_Framework_PackageFamilyName_Get(
    PCWSTR* packageFamilyName) noexcept try
{
    *packageFamilyName = nullptr;
    return ::Microsoft::WindowsAppRuntime::VersionInfo::RuntimeInformation::GetFrameworkPackageFamilyName(packageFamilyName);
}
CATCH_RETURN();

STDAPI WindowsAppRuntime_VersionInfo_MSIX_Main_PackageFamilyName_Get(
    PCWSTR* packageFamilyName) noexcept try
{
    *packageFamilyName = nullptr;
    const auto& mainPackageFamilyName{ ::Microsoft::WindowsAppRuntime::VersionInfo::RuntimeInformation::GetMainPackageFamilyName() };
    *packageFamilyName = mainPackageFamilyName.c_str();
    RETURN_HR_IF_MSG(E_UNEXPECTED, mainPackageFamilyName.empty(), "WindowsAppSDK main PackageFamilyName resource not valid (\"\")");
    return S_OK;
}
CATCH_RETURN();

STDAPI WindowsAppRuntime_VersionInfo_TestInitialize(
    PCWSTR frameworkPackageFamilyName,
    PCWSTR mainPackageFamilyName) noexcept try
{
    // Verify parameters
    const bool frameworkPackageFamilyNameIsEmpty{ !frameworkPackageFamilyName || (*frameworkPackageFamilyName == L'0') };
    const bool mainPackageFamilyNameIsEmpty{ !mainPackageFamilyName || (*mainPackageFamilyName == L'0') };
    if (MddCore::Win11::IsSupported())
    {
        // Framework is optional but Main is never specified
        FAIL_FAST_HR_IF(E_UNEXPECTED, !mainPackageFamilyNameIsEmpty);
    }
    else
    {
        // Both or neither must be valued
        FAIL_FAST_HR_IF(E_UNEXPECTED, frameworkPackageFamilyNameIsEmpty && !mainPackageFamilyNameIsEmpty);
        FAIL_FAST_HR_IF(E_UNEXPECTED, !frameworkPackageFamilyNameIsEmpty && mainPackageFamilyNameIsEmpty);
    }

    // Update our state
    if (frameworkPackageFamilyNameIsEmpty)
    {
        // Shutdown test support
        g_test_frameworkPackageFamilyName.clear();
        g_test_mainPackageFamilyName.clear();
    }
    else
    {
        // Initialize test support
        g_test_frameworkPackageFamilyName = frameworkPackageFamilyName;
        g_test_mainPackageFamilyName = (!mainPackageFamilyName ? L"" : mainPackageFamilyName);
    }
    return S_OK;
}
CATCH_RETURN();

const ::Microsoft::WindowsAppSDK::VersionInfo* Microsoft::WindowsAppSDK::GetVersionInfo()
{
    const auto versionInfo{ ::Microsoft::WindowsAppRuntime::VersionInfo::RuntimeInformation::GetVersionInfo() };
    return !versionInfo ? &c_noVersionInfo : versionInfo;
}
