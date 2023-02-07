// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

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
        static std::string LoadStringFromResource(uint32_t id)
        {
            const uint32_t c_ResourceMaxLength{ 100 };
            char resourceValue[c_ResourceMaxLength]{};
            static wil::unique_hmodule module{ LoadResourceModule() };
            if (module)
            {
                const auto resourceValueLength{ ::LoadStringA(module.get(), id, resourceValue, ARRAYSIZE(resourceValue)) };
                LOG_LAST_ERROR_IF_MSG(resourceValueLength == 0, "Failed to load resource string. id: %u", id);
            }
            return resourceValue;
        }

        static wil::unique_hmodule LoadResourceModule()
        {
            const PCWSTR c_resourceDllName{ L"Microsoft.WindowsAppRuntime.Insights.Resource.dll" };
            wil::unique_hmodule resourceDllHandle(::LoadLibraryW(c_resourceDllName));
            LOG_LAST_ERROR_IF_NULL_MSG(resourceDllHandle, "Unable to load resource dll. %ls", c_resourceDllName);
            return resourceDllHandle;
        }
    };
    }

    #define _GENERIC_PARTB_FIELDS_ENABLED \
            TraceLoggingStruct(4, "COMMON_WINDOWSAPPSDK_PARAMS"), \
            TraceLoggingString(::Microsoft::WindowsAppRuntime::Insights::RuntimeInformation::WindowsAppRuntimeVersion().c_str(), "Version"), \
            TraceLoggingString(::Microsoft::WindowsAppRuntime::Insights::RuntimeInformation::WindowsAppRuntimeChannel().c_str(), "WindowsAppSDKChannel"), \
            TraceLoggingBool(wil::details::IsDebuggerPresent(), "IsDebugging"), \
            TraceLoggingBool(true, "UTCReplace_AppSessionGuid")

    #include <wil/tracelogging.h>

#endif // __WINDOWSAPPRUNTIMEINSIGHTS_INCLUDED
#else
#error "WIL package must be referenced before including this header"
#endif
