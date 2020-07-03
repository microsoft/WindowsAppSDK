#pragma once

// Temporary hack until switching to the ProjectReunion project @jonwis is cooking
#if defined(WINAPI_FAMILY)
#   undef WINAPI_FAMILY
#endif

#include "targetver.h"

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <windows.h>

#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Foundation.Metadata.h>

#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.Data.Xml.Dom.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Management.Deployment.h>
