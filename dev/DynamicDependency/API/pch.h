// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <Windows.h>

#include <appmodel.h>
#include <shlwapi.h>
#include <xmllite.h>

#include <unknwn.h>
#include <appmodel.h>
#include <MsixDynamicDependency.h>

#include <filesystem>
#include <thread>
#include <mutex>

#include <wil/cppwinrt.h>
#include <wil/token_helpers.h>
#include <wil/win32_helpers.h>
#include <wil/resource.h>
#include <wil/result_macros.h>
#include <wil/com.h>

#include <appmodel_msixdynamicdependency.h>
#include <wil_msixdynamicdependency.h>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.ApplicationModel.AppExtensions.h>
#include <winrt/Windows.Data.Json.h>
#include <winrt/Windows.Management.Core.h>
#include <winrt/Windows.Management.Deployment.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.System.h>

#include <appmodel.identity.h>
#include <appmodel.packagegraph.h>
#include <microsoft.utf8.h>
#include <security.integritylevel.h>
#include <windowsappruntime.versioninfo.h>
