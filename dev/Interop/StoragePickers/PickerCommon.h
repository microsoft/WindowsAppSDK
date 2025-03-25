// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "pch.h"
#include "ShObjIdl.h"
#include "wil/cppwinrt.h"
#include "winrt/base.h"
#include "winrt/Microsoft.Windows.Storage.Pickers.h"
#include "TerminalVelocityFeatures-StoragePickers.h"
#include <winrt/Windows.Security.Cryptography.h>
#include <winrt/Windows.Security.Cryptography.Core.h>
#include <winrt/Microsoft.UI.Windowing.h>

namespace PickerCommon {
    winrt::hstring GetPathFromShellItem(winrt::com_ptr<IShellItem> shellItem);

    std::vector<COMDLG_FILTERSPEC> CaptureFilterSpec(std::vector<winrt::hstring>& buffer, winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> filters);
    std::vector<COMDLG_FILTERSPEC> CaptureFilterSpec(std::vector<winrt::hstring>& buffer, winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::Windows::Foundation::Collections::IVector<winrt::hstring>> filters);

    bool IsHStringNullOrEmpty(winrt::hstring value);

    struct PickerParameters {
        HWND HWnd{};
        winrt::hstring CommitButtonText;
        winrt::hstring SettingsIdentifierId;
        winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId PickerLocationId;
        std::vector<winrt::hstring> FileTypeFilterData{};
        std::vector<COMDLG_FILTERSPEC> FileTypeFilterPara{};

        void ConfigureDialog(winrt::com_ptr<IFileDialog> dialog);
    };
}
