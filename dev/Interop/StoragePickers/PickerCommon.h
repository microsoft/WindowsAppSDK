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
    const winrt::hstring AllFilesLocalizationKey = L"Microsoft.WindowsAppRuntime/StoragePickers/All Files";

    const winrt::hstring InvalidViewModeLocalizationKey{ L"Microsoft.WindowsAppRuntime/StoragePickers/IDS_APIERROR_INVALIDVIEWMODEVALUE"};
    const winrt::hstring InvalidViewModeContent{L"The specified ViewMode is invalid."};
    
    const winrt::hstring InvalidSuggestedStartLocationLocalizationKey{L"Microsoft.WindowsAppRuntime/StoragePickers/IDS_APIERROR_INVALIDSUGGESTEDSTARTLOCATIONVALUE"};
    const winrt::hstring InvalidSuggestedStartLocationContent{L"The specified SuggestedStartLocation is invalid."};

    const winrt::hstring ImproperFileExtensionLocationzationKey{L"Microsoft.WindowsAppRuntime/StoragePickers/IDS_APIERROR_IMPROPERFILEEXTENSION"};
    const winrt::hstring ImproperFileExtensionContent{L"File extensions must begin with '.' and contain no wildcards."};

    const winrt::hstring StringNoEmbeddedNullsLocalizationKey{L"Microsoft.WindowsAppRuntime/StoragePickers/IDS_APIERROR_STRINGSNOEMBEDDEDNULLS"};
    const winrt::hstring StringNoEmbeddedNullsContent{L"Strings cannot have embedded nulls."};

    const winrt::hstring MaxSaveFileLengthExceededLocalizationKey{L"Microsoft.WindowsAppRuntime/StoragePickers/IDS_APIERROR_MAXSAVEFILELENGTHEXCEEDED"};
    const winrt::hstring MaxSaveFileLengthExceededContent{L"The suggested file name exceeds the maximum number of characters allowed."};

    bool IsHStringNullOrEmpty(winrt::hstring value);

    std::pair<winrt::com_ptr<IShellItem>, std::wstring> ParseFolderItemAndFileName(winrt::hstring const& filePath);

    void ValidateStringNoEmbeddedNulls(winrt::hstring const& value);
    void ValidateViewMode(winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode const& value);
    void ValidateSuggestedStartLocation(winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId const& value);
    void ValidateSingleFileTypeFilterElement(winrt::hstring const& filter);
    void ValidateSuggestedFileName(winrt::hstring const& suggestedFileName);

    struct PickerParameters {
        HWND HWnd{};
        winrt::hstring CommitButtonText;
        winrt::hstring SettingsIdentifierId;
        winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId PickerLocationId;
        std::vector<winrt::hstring> FileTypeFilterData{};
        std::vector<COMDLG_FILTERSPEC> FileTypeFilterPara{};
        winrt::hstring AllFilesText{ L"All Files" }; // initialize to All Files as a default value, will be updated by localization

        winrt::hstring SuggestedFileName;
        winrt::hstring SuggestedSaveFilePath;

        winrt::hstring FormatExtensionWithWildcard(winrt::hstring extension);
        winrt::hstring JoinExtensions(winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> extensions);

        void CaptureFilterSpec(winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> filters);
        void CaptureFilterSpec(winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::Windows::Foundation::Collections::IVector<winrt::hstring>> filters);

        void ConfigureDialog(winrt::com_ptr<IFileDialog> dialog);
        void ConfigureFileSaveDialog(winrt::com_ptr<IFileSaveDialog> dialog);
    };
}
