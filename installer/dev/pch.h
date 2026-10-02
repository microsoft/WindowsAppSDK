// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <wil/result.h>
#include <wil/resource.h>
#include <wil/result_macros.h>
#include <wil/com.h>
#include <wil/win32_helpers.h>
#include <wil/token_helpers.h>
#include <wil/Tracelogging.h>

#include <iostream>
#include <sstream>
#include <filesystem>
#include <processenv.h>
#include <shellapi.h>
#include <shlwapi.h>
#include <WinBase.h>
#include <AppxPackaging.h>
#include <processthreadsapi.h>
#include <string_view>

#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Management.Deployment.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.System.h>

#include <Security.IntegrityLevel.h>
#include <Security.User.h>
#include <PushNotifications-Constants.h>
#include <AppModel.Package.h>

#include "tracelogging.h"
#include "InstallActivityContext.h"
#include "console.h"
#include "WindowsAppRuntime-License.h"
