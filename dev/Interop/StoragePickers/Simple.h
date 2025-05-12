// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "ShObjIdl.h"
#include "wil/cppwinrt.h"
#include "winrt/base.h"
// #include "winrt/Microsoft.Windows.Storage.Pickers.h"
// #include "TerminalVelocityFeatures-StoragePickers.h"
#include <winrt/Windows.Security.Cryptography.h>
#include <winrt/Windows.Security.Cryptography.Core.h>
#include <winrt/Microsoft.UI.Windowing.h>

// from pch.h in applicationdata
// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <Windows.h>

#include <unknwn.h>
#include <appmodel.h>

#include <filesystem>
#include <thread>
#include <mutex>

#include <wil/cppwinrt.h>
#include <wil/filesystem.h>
#include <wil/registry.h>
#include <wil/resource.h>
#include <wil/result_macros.h>
#include <wil/token_helpers.h>

#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

#include <winrt/Windows.ApplicationModel.h>
#include <winrt/Windows.Management.Deployment.h>
#include <winrt/Windows.Storage.h>
#include <winrt/Windows.System.h>

#include <appmodel.identity.h>
#include <security.user.h>

// from pch.h in WindowsAppRuntime_DLL
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

namespace TestCommon {
    int test_add(int a, int b);

    struct PickerParameters {
        HWND HWnd{};
        winrt::hstring CommitButtonText;
        winrt::hstring SettingsIdentifierId;
        //winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId PickerLocationId;
        std::vector<winrt::hstring> FileTypeFilterData{};
        std::vector<COMDLG_FILTERSPEC> FileTypeFilterPara{};

        void CaptureFilterSpec(winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> filters);
        void CaptureFilterSpec(winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::Windows::Foundation::Collections::IVector<winrt::hstring>> filters);

        //void ConfigureDialog(winrt::com_ptr<IFileDialog> dialog);
    };
}
