// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <Microsoft.Utf8.h>

#include "WindowsAppRuntime.VersionInfo.h"

static std::wstring g_test_frameworkPackageFamilyName{ L"asdf" };
static std::wstring g_test_mainPackageFamilyName{ L"asdf" };

namespace Microsoft::WindowsAppRuntime::VersionInfo
{
class RuntimeInformation
{
public:
    static const std::wstring& GetFrameworkPackageFamilyName()
    {
        if (!g_test_frameworkPackageFamilyName.empty())
        {
            return g_test_frameworkPackageFamilyName;
        }

        const uint32_t c_frameworkPackageFamilyNameResourceId{ 10002 };
        static std::wstring frameworkPackageFamilyName{ LoadStringWFromResource(c_frameworkPackageFamilyNameResourceId) };
        return frameworkPackageFamilyName;
    }

    static const std::wstring& GetMainPackageFamilyName()
    {
        if (!g_test_mainPackageFamilyName.empty())
        {
            return g_test_mainPackageFamilyName;
        }

        const uint32_t c_mainPackageFamilyNameResourceId{ 10002 };
        static std::wstring mainPackageFamilyName{ LoadStringWFromResource(c_mainPackageFamilyNameResourceId) };
        return mainPackageFamilyName;
    }

private:
    static std::wstring LoadStringWFromResource(uint32_t id)
    {
        const auto string{ LoadStringAFromResource(id) };
        return ::Microsoft::Utf8::ToUtf16<std::wstring>(string.c_str());
    }

    static std::string LoadStringAFromResource(uint32_t id)
    {
        static wil::unique_hmodule module{ LoadResourceModule() };

        const uint32_t c_ResourceMaxLength{ 1024 };
        char resourceValue[c_ResourceMaxLength]{};
        const auto resourceValueLength{ ::LoadStringA(module.get(), id, resourceValue, ARRAYSIZE(resourceValue)) };
        THROW_LAST_ERROR_IF_MSG(resourceValueLength == 0, "Failed to load resource string. id: %u", id);
        return resourceValue;
    }

    static wil::unique_hmodule LoadResourceModule()
    {
        const PCWSTR c_resourceDllName{ L"Microsoft.WindowsAppRuntime.Insights.Resource.dll" };
        wil::unique_hmodule resourceDllHandle(::LoadLibraryW(c_resourceDllName));
        THROW_LAST_ERROR_IF_NULL_MSG(resourceDllHandle, "Unable to load resource dll. %ls", c_resourceDllName);
        return resourceDllHandle;
    }
};
}

STDAPI WindowsAppRuntime_VersionInfo_MSIX_Framework_PackageFamilyName_Get(
    PCWSTR* packageFamilyName) noexcept try
{
    *packageFamilyName = nullptr;
    const auto& frameworkPackageFamilyName{ ::Microsoft::WindowsAppRuntime::VersionInfo::RuntimeInformation::GetFrameworkPackageFamilyName() };
    *packageFamilyName = frameworkPackageFamilyName.c_str();
    RETURN_HR_IF_MSG(E_UNEXPECTED, frameworkPackageFamilyName.empty(), "WindowsAppSDK framework PackageFamilyName resource not valid (\"\")");
    return S_OK;
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
    // Both or neither must be valued
    const bool frameworkPackageFamilyNameIsEmpty{ !frameworkPackageFamilyName || (*frameworkPackageFamilyName == L'0') };
    const bool mainPackageFamilyNameIsEmpty{ !mainPackageFamilyName || (*mainPackageFamilyName == L'0') };
    FAIL_FAST_HR_IF(E_UNEXPECTED, frameworkPackageFamilyNameIsEmpty && !mainPackageFamilyNameIsEmpty);
    FAIL_FAST_HR_IF(E_UNEXPECTED, !frameworkPackageFamilyNameIsEmpty && mainPackageFamilyNameIsEmpty);

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
        g_test_mainPackageFamilyName = mainPackageFamilyName;
    }
    return S_OK;
}
CATCH_RETURN();
