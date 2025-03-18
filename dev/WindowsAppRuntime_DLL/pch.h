// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include <Windows.h>
#include <assert.h>
#include <unknwn.h>
#include <ShlObj_core.h>
#include <ShObjIdl_core.h>
#include <shlguid.h>
#include <shlwapi.h>
#include <shellapi.h>
#include <appmodel.h>
#include <xmllite.h>
#include <sddl.h>

#include <string>
#include <string_view>
#include <thread>
#include <mutex>
#include <list>
#include <stdexcept>
#include <regex>
#include <filesystem>

#include <wil/cppwinrt.h>
#include <wil/cppwinrt_authoring.h>
#include <wil/token_helpers.h>
#include <wil/stl.h>
#include <wil/resource.h>
#include <wil/result_macros.h>
#include <wil/filesystem.h>
#include <wil/registry.h>
#include <wil/com.h>
#include <wil/win32_helpers.h>
#include <wil/winrt.h>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.ApplicationModel.Activation.h>
#include <winrt/Windows.ApplicationModel.Core.h>
#include <winrt/Windows.ApplicationModel.AppExtensions.h>
#include <winrt/Windows.ApplicationModel.DataTransfer.h>
#include <winrt/Windows.Data.Json.h>
#include <winrt/Windows.Data.Xml.Dom.h>
#include <winrt/Windows.Management.Core.h>
#include <winrt/Windows.Management.Deployment.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.System.h>

#include <MsixDynamicDependency.h>

#include <appmodel.identity.h>
#include <appmodel.packagegraph.h>
#include <microsoft.configuration.h>
#include <microsoft.utf8.h>
#include <security.integritylevel.h>
#include <security.user.h>
#include <windowsappruntime.selfcontained.h>
#include <windowsappruntime.versioninfo.h>

#define MIDL_NS_PREFIX
