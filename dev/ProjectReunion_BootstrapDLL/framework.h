// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

//#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files
//#include <windows.h>
//#include <appmodel.h>

#include <unknwn.h>
#include <appmodel.h>

#include <thread>
#include <mutex>

#include <wil/cppwinrt.h>
#include <wil/win32_helpers.h>
#include <wil/result.h>
#include <wil/com.h>
#include <wil/resource.h>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.ApplicationModel.AppExtensions.h>

#include "wil_msixdynamicdependency.h"
