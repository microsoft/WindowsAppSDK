// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "ShObjIdl.h"
#include "winrt/base.h"
#include "winrt/Microsoft.Windows.Storage.Pickers.h"
#include <winrt/Windows.Security.Cryptography.h>
#include <winrt/Windows.Security.Cryptography.Core.h>
#include <winrt/Microsoft.UI.Windowing.h>

namespace PickerCommon {
    winrt::hstring GetPathFromShellItem(winrt::com_ptr<IShellItem> shellItem);
    winrt::com_ptr<IShellItem> TryParseFolderItem(winrt::hstring const& folderPathStr);
    const winrt::hstring AllFilesLocalizationKey = L"Microsoft.WindowsAppRuntime/StoragePickers/All Files";

    const winrt::hstring InvalidViewModeLocalizationKey{ L"Microsoft.WindowsAppRuntime/StoragePickers/IDS_APIERROR_INVALIDVIEWMODEVALUE"};
    const winrt::hstring InvalidSuggestedStartLocationLocalizationKey{L"Microsoft.WindowsAppRuntime/StoragePickers/IDS_APIERROR_INVALIDSUGGESTEDSTARTLOCATIONVALUE"};
    const winrt::hstring ImproperFileExtensionLocalizationKey{L"Microsoft.WindowsAppRuntime/StoragePickers/IDS_APIERROR_IMPROPERFILEEXTENSION"};
    const winrt::hstring StringNoEmbeddedNullsLocalizationKey{L"Microsoft.WindowsAppRuntime/StoragePickers/IDS_APIERROR_STRINGSNOEMBEDDEDNULLS"};
    const winrt::hstring MaxSaveFileLengthExceededLocalizationKey{L"Microsoft.WindowsAppRuntime/StoragePickers/IDS_APIERROR_MAXSAVEFILELENGTHEXCEEDED"};

    bool IsHStringNullOrEmpty(winrt::hstring value);
    void ValidateStringNoEmbeddedNulls(winrt::hstring const& value);
    void ValidateViewMode(winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode const& value);
    void ValidateSuggestedStartLocation(winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId const& value);
    void ValidateSingleFileTypeFilterElement(winrt::hstring const& filter);
    void ValidateSuggestedFileName(winrt::hstring const& suggestedFileName);
    void ValidateFolderPath(winrt::hstring const& path, std::string const& propertyName);

    struct PickerParameters {
        HWND HWnd{};
        winrt::hstring CommitButtonText;
        winrt::hstring Title;
        winrt::hstring SettingsIdentifier;
        winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId SuggestedStartLocation;
        std::vector<winrt::hstring> FileTypeFilterData{};
        std::vector<COMDLG_FILTERSPEC> FileTypeFilterPara{};
        int DefaultFileTypeIndex{ -1 };
        winrt::hstring AllFilesText{ L"All Files" }; // initialize to All Files as a default value, will be updated by localization

        winrt::hstring SuggestedFileName;
        winrt::hstring SuggestedFolder;
        winrt::hstring SuggestedStartFolder;

        winrt::hstring FormatExtensionWithWildcard(winrt::hstring extension);
        winrt::hstring JoinExtensions(winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> extensions);

        void CaptureFilterSpecData(
            winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> fileTypeFilterView,
            winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::Windows::Foundation::Collections::IVector<winrt::hstring>> fileTypeChoicesView);

        void ConfigureDialog(winrt::com_ptr<IFileDialog> dialog);
        void ConfigureFileSaveDialog(winrt::com_ptr<IFileSaveDialog> dialog);

        winrt::hstring TryGetAppUserModelId();
        winrt::hstring TryGetProcessFullPath();

		bool ShowOverwritePrompt;

    private:
        void CaptureFilterSpec(winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> filters);
        void CaptureFilterSpec(winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::Windows::Foundation::Collections::IVector<winrt::hstring>> filters);
    };
}
