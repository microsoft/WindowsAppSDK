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

#include <restrictederrorinfo.h>
#include <hstring.h>

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

#include <winrt/Windows.Security.Cryptography.h>
#include <winrt/Windows.Security.Cryptography.Core.h>
#include <winrt/Windows.UI.Xaml.Interop.h>
#include <winrt/Microsoft.UI.h>
#include <winrt/Microsoft.UI.Composition.h>
#include <winrt/Microsoft.UI.Dispatching.h>
#include <winrt/Microsoft.UI.Windowing.h>


#include <winrt/Microsoft.UI.Xaml.h>
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include <winrt/Microsoft.UI.Xaml.Controls.Primitives.h>
#include <winrt/Microsoft.UI.Xaml.Data.h>
#include <winrt/Microsoft.UI.Xaml.Interop.h>
#include <winrt/Microsoft.UI.Xaml.Markup.h>
#include <winrt/Microsoft.UI.Xaml.Media.h>
#include <winrt/Microsoft.UI.Xaml.Navigation.h>
#include <winrt/Microsoft.UI.Xaml.Shapes.h>


#define MIDL_NS_PREFIX

// Undefine GetCurrentTime macro to prevent
// conflict with Storyboard::GetCurrentTime
#undef GetCurrentTime
