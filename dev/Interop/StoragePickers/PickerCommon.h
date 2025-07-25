// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "ShObjIdl.h"
#include "winrt/base.h"
#include "winrt/Microsoft.Windows.Storage.Pickers.h"
#include <winrt/Windows.Security.Cryptography.h>
#include <winrt/Windows.Security.Cryptography.Core.h>
#include <winrt/Microsoft.UI.Windowing.h>
#include <shlobj_core.h>

namespace PickerCommon {
    winrt::hstring GetPathFromShellItem(winrt::com_ptr<IShellItem> shellItem);
    const winrt::hstring AllFilesLocalizationKey = L"Microsoft.WindowsAppRuntime/StoragePickers/All Files";

    const winrt::hstring InvalidViewModeLocalizationKey{ L"Microsoft.WindowsAppRuntime/StoragePickers/IDS_APIERROR_INVALIDVIEWMODEVALUE"};
    const winrt::hstring InvalidSuggestedStartLocationLocalizationKey{L"Microsoft.WindowsAppRuntime/StoragePickers/IDS_APIERROR_INVALIDSUGGESTEDSTARTLOCATIONVALUE"};
    const winrt::hstring ImproperFileExtensionLocalizationKey{L"Microsoft.WindowsAppRuntime/StoragePickers/IDS_APIERROR_IMPROPERFILEEXTENSION"};
    const winrt::hstring StringNoEmbeddedNullsLocalizationKey{L"Microsoft.WindowsAppRuntime/StoragePickers/IDS_APIERROR_STRINGSNOEMBEDDEDNULLS"};
    const winrt::hstring MaxSaveFileLengthExceededLocalizationKey{L"Microsoft.WindowsAppRuntime/StoragePickers/IDS_APIERROR_MAXSAVEFILELENGTHEXCEEDED"};

    bool IsHStringNullOrEmpty(winrt::hstring value);

    std::pair<winrt::com_ptr<IShellItem>, std::wstring> ParseFolderItemAndFileName(winrt::hstring const& filePath);

    void ValidateStringNoEmbeddedNulls(winrt::hstring const& value);
    void ValidateViewMode(winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode const& value);
    void ValidateSuggestedStartLocation(winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId const& value);
    void ValidateSingleFileTypeFilterElement(winrt::hstring const& filter);
    void ValidateSuggestedFileName(winrt::hstring const& suggestedFileName);

    class FileDialogEventsHandler : public winrt::implements<FileDialogEventsHandler, IFileDialogEvents>
    {
    public:
        FileDialogEventsHandler() = default;
        
        // IFileDialogEvents methods
        IFACEMETHODIMP OnFileOk(IFileDialog*) { return S_OK; }
        IFACEMETHODIMP OnFolderChanging(IFileDialog*, IShellItem*) { return S_OK; }
        IFACEMETHODIMP OnFolderChange(IFileDialog* pfd);
        IFACEMETHODIMP OnSelectionChange(IFileDialog*) { return S_OK; }
        IFACEMETHODIMP OnShareViolation(IFileDialog*, IShellItem*, FDE_SHAREVIOLATION_RESPONSE*) { return S_OK; }
        IFACEMETHODIMP OnTypeChange(IFileDialog*) { return S_OK; }
        IFACEMETHODIMP OnOverwrite(IFileDialog*, IShellItem*, FDE_OVERWRITE_RESPONSE*) { return S_OK; }
        
        winrt::com_ptr<IShellItem> GetLastNavigatedFolder() { return m_lastNavigatedFolder; }
        
    private:
        winrt::com_ptr<IShellItem> m_lastNavigatedFolder;
    };

    void SaveLastOpenedLocation(winrt::hstring const& settingsIdentifier, winrt::com_ptr<IShellItem> folderItem);
    winrt::com_ptr<IShellItem> GetLastOpenedLocation(winrt::hstring const& settingsIdentifier);

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
