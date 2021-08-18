// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#ifndef __WINDOWSAPPSDKINSIGHTS_INCLUDED
#define __WINDOWSAPPSDKINSIGHTS_INCLUDED

#ifdef __WIL_TRACELOGGING_H_INCLUDED
#error "WIL Tracelogging.h must not be explicitly included when including this file"
#endif

#include <wil/resource.h>
#include <string>

#define _WINDOWSAPPSDK_PACKAGE_VER_RESOURCEID             10000
#define _WINDOWSAPPSDK_EXPERIMENTATION_FLAG_RESOURCEID    10001

#define INSIGHTSRESOURCEDLL "Microsoft.WindowsAppSDK.Insights.Resource.dll"

inline std::string load_resource_string(const char* dllName, uint32_t id)
{
    wil::unique_hmodule module(::LoadLibraryA(dllName));

    if (module)
    {
        char buffer[256];
        if (0 < LoadStringA(module.get(), id, buffer, ARRAYSIZE(buffer)))
        {
            return buffer;
        }
        else
        {
            LOG_LAST_ERROR_MSG("Unable to load resource string, id: %d", id);
        }
    }
    else
    {
        LOG_LAST_ERROR_MSG("Unable to load dll: %s", dllName);
    }

    return {};
}

static char* WINDOWSAPPSDK_PACKAGE_VER()
{
    static std::string packageVer = load_resource_string(INSIGHTSRESOURCEDLL, _WINDOWSAPPSDK_PACKAGE_VER_RESOURCEID);
    return const_cast<char*>(packageVer.c_str());
}

static char* WINDOWSAPPSDK_EXPERIMENTATION_LEVEL()
{
    static std::string experimentationLevel = load_resource_string(INSIGHTSRESOURCEDLL, _WINDOWSAPPSDK_EXPERIMENTATION_FLAG_RESOURCEID);
    return const_cast<char*>(experimentationLevel.c_str());
}

#define _GENERIC_PARTB_FIELDS_ENABLED \
        TraceLoggingStruct(4, "COMMON_WINDOWSAPPSDK_PARAMS"), \
        TraceLoggingString(WINDOWSAPPSDK_PACKAGE_VER(), "SDKVersion"), \
        TraceLoggingString(WINDOWSAPPSDK_EXPERIMENTATION_LEVEL(), "SDKExperimentationLevel"), \
        TraceLoggingBool(wil::details::IsDebuggerPresent(), "IsDebugging"), \
        TraceLoggingBool(true, "UTCReplace_AppSessionGuid")

#include <wil/tracelogging.h>
#endif // __WINDOWSAPPSDKINSIGHTS_INCLUDED
