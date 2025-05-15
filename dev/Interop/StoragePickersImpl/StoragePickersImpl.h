// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include <Windows.h>
#include <vector>
#include <ShObjIdl.h>
#include <winrt/base.h>
#include <winrt/Windows.Foundation.h>
#include <winrt/Windows.Foundation.Collections.h>

namespace StoragePickersImpl {

    struct PickerParameters {
        HWND HWnd{};
        winrt::hstring CommitButtonText;
        winrt::hstring SettingsIdentifierId;
        std::vector<winrt::hstring> FileTypeFilterData{};
        std::vector<COMDLG_FILTERSPEC> FileTypeFilterPara{};

        void CaptureFilterSpec(winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> filters);
        void CaptureFilterSpec(winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::Windows::Foundation::Collections::IVector<winrt::hstring>> filters);
    };
}
