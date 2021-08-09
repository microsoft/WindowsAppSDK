// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#ifndef __WINDOWSAPPSDKINSIGHTS_INCLUDED
#define __WINDOWSAPPSDKINSIGHTS_INCLUDED

#ifdef __WIL_TRACELOGGING_H_INCLUDED
#error "WIL Tracelogging.h must not be explicitly included when including this file"
#endif

char* WINDOWSAPPSDK_PACKAGE_VER();
char* WINDOWSAPPSDK_EXPERIMENTATION_LEVEL();

#define _GENERIC_PARTB_FIELDS_ENABLED \
        TraceLoggingStruct(4, "COMMON_WINDOWSAPPSDK_PARAMS"), \
        TraceLoggingString(WINDOWSAPPSDK_PACKAGE_VER(), "SDKVersion"), \
        TraceLoggingString(WINDOWSAPPSDK_EXPERIMENTATION_LEVEL(), "SDKExperimentationLevel"), \
        TraceLoggingBool(wil::details::IsDebuggerPresent(), "IsDebugging"), \
        TraceLoggingBool(true, "UTCReplace_AppSessionGuid")

#include <wil/tracelogging.h>
#endif // __WINDOWSAPPSDKINSIGHTS_INCLUDED
