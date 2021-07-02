#pragma once

#ifndef __REUNIONTELEMETRY_INCLUDED
#define __REUNIONTELEMETRY_INCLUDED

#ifdef __WIL_TRACELOGGING_H_INCLUDED
#error "WIL Tracelogging.h must not be explicitly included when including this file"
#endif

#define _REUNION_PACKAGE_VER_RESOURCEID             10001
#define _REUNION_EXPERIMENTATION_FLAG_RESOURCEID    10002

static std::wstring s_ReunionPackageVer = L"";
static std::wstring s_ExperimentationLevel = L"not_initialized";

wchar_t* REUNION_PACKAGE_VER()
{
   if(s_ReunionPackageVer.empty())
   {
       HMODULE resourceDll = LoadLibraryW(L"ProjectReunionTelemetryResource.dll");

       if(resourceDll)
       {
        wchar_t packageVer[256];
        LoadStringW((HINSTANCE)resourceDll, _REUNION_PACKAGE_VER_RESOURCEID, packageVer, 256);
        s_ReunionPackageVer = packageVer;
        FreeLibrary(resourceDll);
       }
   }

   return s_ReunionPackageVer.c_str();
}

wchar_t* REUNION_EXPERIMENTATION_LEVEL()
{
    if (s_ExperimentationLevel.compare(L"not_initialized") == 0)
    {
        HMODULE resourceDll = LoadLibraryW(L"ProjectReunionTelemetryResource.dll");

        if(resourceDll)
        {
            wchar_t experimentationLevel[256];
            LoadStringW((HINSTANCE)resourceDll, _REUNION_EXPERIMENTATION_FLAG_RESOURCEID, experimentationLevel, 256);
            s_ExperimentationLevel = experimentationLevel;
            FreeLibrary(resourceDll);
        }
    }

    return s_ExperimentationLevel.c_str();
}


#define REUNION_SDK_VER REUNION_PACKAGE_VER()
#define REUNION_EXPERIMENTATION_LEVEL REUNION_EXPERIMENTATION_LEVEL()

#define _GENERIC_PARTB_FIELDS_ENABLED \
        TraceLoggingStruct(3, "PartB_Reunion_API"), \
        TraceLoggingString(REUNION_SDK_VER, "Reunion package version"), \
        TraceLoggingString(REUNION_EXPERIMENTATION_LEVEL, "Reunion experimentation level"), \
        TraceLoggingBool(wil::details::IsDebuggerPresent(), "IsDebugging")

#include <wil/tracelogging.h>
#endif // __REUNIONTELEMETRY_INCLUDED
