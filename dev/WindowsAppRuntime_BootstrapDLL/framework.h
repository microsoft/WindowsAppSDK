// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <unknwn.h>
#include <appmodel.h>
#include <shobjidl.h>

#include <thread>
#include <mutex>

#include <wil/cppwinrt.h>
#include <wil/token_helpers.h>
#include <wil/win32_helpers.h>
#include <wil/result.h>
#include <wil/com.h>
#include <wil/resource.h>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.ApplicationModel.AppExtensions.h>
#include <winrt/Windows.Management.Deployment.h>

#include <appmodel.identity.h>
#include <iswindowsversion.h>
#include <security.integritylevel.h>
#include <WindowsAppRuntime.VersionInfo.h>

#include "wil_msixdynamicdependency.h"
