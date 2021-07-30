// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

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
            LOG_LAST_ERROR_MSG("Unable to load resource string, id: %d, error: %d", id, GetLastError());
        }
        
    }
    else
    {
        LOG_LAST_ERROR_IF_MSG(module == nullptr, "Unable to load dll: %s", dllName);
    }

    return {};
}

__declspec(dllexport) char* WINDOWSAPPSDK_PACKAGE_VER()
{
    static std::string packageVer = load_resource_string(INSIGHTSRESOURCEDLL, _WINDOWSAPPSDK_PACKAGE_VER_RESOURCEID);
    return const_cast<char*>(packageVer.c_str());
}

__declspec(dllexport) char* WINDOWSAPPSDK_EXPERIMENTATION_LEVEL()
{
    static std::string experimentationLevel = load_resource_string(INSIGHTSRESOURCEDLL, _WINDOWSAPPSDK_EXPERIMENTATION_FLAG_RESOURCEID);
    return const_cast<char*>(experimentationLevel.c_str());
}
