// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#if __has_include(<wil/tracelogging.h>)
#ifndef __WINDOWSAPPRUNTIMEINSIGHTS_INCLUDED
#define __WINDOWSAPPRUNTIMEINSIGHTS_INCLUDED

#ifdef __WIL_TRACELOGGING_H_INCLUDED
#error "WIL Tracelogging.h must not be explicitly included when including this file"
#endif

#include <wil/resource.h>
#include <string>
    namespace Microsoft::WindowsAppRuntime::Insights
    {
    class RuntimeInformation
    {
    public:
        static std::string WindowsAppRuntimeVersion()
        {
            const uint32_t c_versionResourceId{ 10000 };
            static std::string version{ LoadStringFromResource(c_versionResourceId) };
            return version;
        }

        static std::string WindowsAppRuntimeChannel()
        {
            const uint32_t c_channelResourceId{ 10001 };
            static std::string channel{ LoadStringFromResource(c_channelResourceId) };
            return channel;
        }

    private:
        static inline std::string LoadStringFromResource(uint32_t id)
        {
            static wil::unique_hmodule module = std::move(LoadResourceModule());
            const uint32_t c_ResourceMaxLength{ 100 };
            char resourceValue[c_ResourceMaxLength]{};

            if(module)
            {
                if(0 == ::LoadStringA(module.get(), id, resourceValue, ARRAYSIZE(resourceValue)))
                {
                    DWORD error{ GetLastError() };
                    LOG_HR_IF_MSG(HRESULT_FROM_WIN32(error), ERROR_SUCCESS != error, "Failed to load resource string. id: %d", id);
                }
            }
            return resourceValue;
        }

        static wil::unique_hmodule LoadResourceModule()
        {
            const PCWSTR c_resourceDllName{ L"Microsoft.WindowsAppRuntime.Insights.Resource.dll" };
            wil::unique_hmodule resourceDllHandle(::LoadLibraryW(c_resourceDllName));
            LOG_HR_IF_NULL_MSG(HRESULT_FROM_WIN32(GetLastError()), resourceDllHandle, "Unable to load resource dll. %ws", c_resourceDllName);
            return resourceDllHandle;
        }
    };

    } // namespace Microsoft::WindowsAppRuntime::Insights


    #define _GENERIC_PARTB_FIELDS_ENABLED \
            TraceLoggingStruct(4, "COMMON_WINDOWSAPPSDK_PARAMS"), \
            TraceLoggingString(Microsoft::WindowsAppRuntime::Insights::RuntimeInformation::WindowsAppRuntimeVersion().c_str(), "Version"), \
            TraceLoggingString(Microsoft::WindowsAppRuntime::Insights::RuntimeInformation::WindowsAppRuntimeChannel().c_str(), "WindowsAppSDKChannel"), \
            TraceLoggingBool(wil::details::IsDebuggerPresent(), "IsDebugging"), \
            TraceLoggingBool(true, "UTCReplace_AppSessionGuid")

    #include <wil/tracelogging.h>

#endif // __WINDOWSAPPRUNTIMEINSIGHTS_INCLUDED
#else
#error "WIL package must be referenced before including this header"
#endif
