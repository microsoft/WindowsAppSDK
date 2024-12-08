// TODO: use better namespace, maybe anonymous namespace?
#pragma once
#include "pch.h"
#include "ShObjIdl.h"
#include "winrt/Microsoft.Storage.Pickers.h"

namespace PickerCommon {
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFile> CreateStorageFileFromShellItem(winrt::com_ptr<IShellItem> shellItem);
    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFolder> CreateStorageFolderFromShellItem(winrt::com_ptr<IShellItem> shellItem);

    std::vector<COMDLG_FILTERSPEC> CaptureFilterSpec(std::vector<winrt::hstring>& buffer, winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> filters);
    std::vector<COMDLG_FILTERSPEC> CaptureFilterSpec(std::vector<winrt::hstring>& buffer, winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::Windows::Foundation::Collections::IVector<winrt::hstring>> filters);

    // TODO: remove this if we know proper and null safe empty test for string
    bool IsHStringNullOrEmpty(winrt::hstring value);

    struct PickerParameters {
        HWND HWnd;
        winrt::hstring CommitButtonText;
        winrt::hstring SettingsIdentifierId;
        winrt::Microsoft::Storage::Pickers::PickerLocationId PickerLocationId;
        std::vector<winrt::hstring> FileTypeFilterData{};
        std::vector<COMDLG_FILTERSPEC> FileTypeFilterPara{};

        void ConfigureDialog(winrt::com_ptr<IFileDialog> dialog);
    };
}
