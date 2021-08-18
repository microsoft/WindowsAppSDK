// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#ifndef __WINDOWSAPPRUNTIMEINSIGHTS_INCLUDED
#define __WINDOWSAPPRUNTIMEINSIGHTS_INCLUDED

#ifdef __WIL_TRACELOGGING_H_INCLUDED
#error "WIL Tracelogging.h must not be explicitly included when including this file"
#endif

#include <wil/resource.h>
#include <string>

namespace Microsoft::WindowsAppSDK::Insights
{ 
class RuntimeInformation
{
public:
    static std::string WindowsAppSDKPackageVersion()
    {
        const uint32_t c_PackageVersionResourceId{ 10000 };
        static std::string version{ LoadStringFromResource(c_PackageVersionResourceId) };
        return version;
    }

    static std::string WindowsAppSDKExperimentationLevel()
    {
        const uint32_t c_ExperimentationLevelResourceId{ 10001 };
        static std::string experimentationLevel{ LoadStringFromResource(c_ExperimentationLevelResourceId) };
        return experimentationLevel;
    }

private:
    static inline std::string LoadStringFromResource(uint32_t id)
    {
        static wil::unique_hmodule module = std::move(LoadResourceModule());
        const uint32_t c_ResourceMaxLength{ 100 };
        char resourceValue[c_ResourceMaxLength]{};

        THROW_IF_WIN32_BOOL_FALSE_MSG(::LoadStringA(module.get(), id, resourceValue, ARRAYSIZE(resourceValue)), "Failed to load resource string. id: %d", id);
        return resourceValue;
    }

    static wil::unique_hmodule LoadResourceModule()
    {
        const PCWSTR c_ResourceDllName{ L"Microsoft.WindowsAppSDK.Insights.Resource.dll" };
        wil::unique_hmodule resourceDllHandle(::LoadLibraryW(c_ResourceDllName));
        THROW_HR_IF_NULL_MSG(HRESULT_FROM_WIN32(GetLastError()), resourceDllHandle, "Unable to load resource dll. %ws", c_ResourceDllName);
        return resourceDllHandle;
    }
};

} // namespace Microsoft::WindowsAppSDK::Insights


#define _GENERIC_PARTB_FIELDS_ENABLED \
        TraceLoggingStruct(4, "COMMON_WINDOWSAPPSDK_PARAMS"), \
        TraceLoggingString(Microsoft::WindowsAppSDK::Insights::RuntimeInformation::WindowsAppSDKPackageVersion().c_str(), "Version"), \
        TraceLoggingString(Microsoft::WindowsAppSDK::Insights::RuntimeInformation::WindowsAppSDKExperimentationLevel().c_str(), "WindowsAppSDKChannel"), \
        TraceLoggingBool(wil::details::IsDebuggerPresent(), "IsDebugging"), \
        TraceLoggingBool(true, "UTCReplace_AppSessionGuid")

#include <wil/tracelogging.h>

#endif // __WINDOWSAPPRUNTIMEINSIGHTS_INCLUDED
