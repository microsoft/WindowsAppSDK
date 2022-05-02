// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"

#include <Microsoft.Utf8.h>

#include "WindowsAppRuntime.VersionInfo.h"

static std::wstring g_test_frameworkPackageFamilyName{ L"Microsoft.WindowsAppRuntime.Framework_8wekyb3d8bbwe" };

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

STDAPI WindowsAppRuntime_VersionInfo_TestInitialize(
    PCWSTR frameworkPackageFamilyName) noexcept try
{
    if (!frameworkPackageFamilyName || (*frameworkPackageFamilyName == L'0'))
    {
        // Shutdown test support
        g_test_frameworkPackageFamilyName.clear();
    }
    else
    {
        // Initialize test support
        g_test_frameworkPackageFamilyName = frameworkPackageFamilyName;
    }
    return S_OK;
}
CATCH_RETURN();
