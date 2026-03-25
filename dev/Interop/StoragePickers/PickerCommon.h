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
    const winrt::hstring InvalidInitialFileTypeIndexLocalizationKey{ L"Microsoft.WindowsAppRuntime/StoragePickers/IDS_APIERROR_INVALIDINITIALFILETYPEINDEX"};
    const winrt::hstring InvalidAppIdForSettingsIdentifierLocalizationKey{ L"Microsoft.WindowsAppRuntime/StoragePickers/IDS_APIERROR_INVALIDAPPIDFORSETTINGSIDENTIFIER"};
    constexpr int DefaultInitialFileTypeIndex{ -1 };

    bool IsHStringNullOrEmpty(winrt::hstring value);
    void ValidateStringNoEmbeddedNulls(winrt::hstring const& value);
    void ValidateViewMode(winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode const& value);
    void ValidateSuggestedStartLocation(winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId const& value);
    void ValidateSingleFileTypeFilterElement(winrt::hstring const& filter);
    void ValidateSuggestedFileName(winrt::hstring const& suggestedFileName);
    void ValidateFolderPath(winrt::hstring const& path, std::string const& propertyName);
    void ValidateInitialFileTypeIndex(int const& value);

    // Shows the WSL node in the navigation pane of COM file dialogs that hide it by default.
    // The WSL node was hidden in FileSavePicker (IFileSaveDialog) and FolderPicker (IFileOpenDialog + FOS_PICKFOLDERS + FOS_FORCEFILESYSTEM);
    // It takes time for the navigation pane to load nodes.
    // This handler checks the root nodes and looks for the WSL node in children nodes.
    // When finds the existing hidden WSL node, makes it visible.
    struct WslNodeRevealer : winrt::implements<WslNodeRevealer, IFileDialogEvents>
    {
        bool m_revealed{ false };

        static winrt::com_ptr<INameSpaceTreeControl> s_nstc;
        static winrt::com_ptr<IShellItem> s_wslItem;
        static UINT_PTR s_timerId;
        static int s_pollCount;

        // looking for the navigation node for 1 second at most
        static constexpr UINT s_pollIntervalMs{ 10 };
        static constexpr int s_maxPollCount{ 100 };

        static void CALLBACK PollTimerProc(HWND, UINT, UINT_PTR timerId, DWORD) noexcept;
        static void CancelPendingReveal() noexcept;

        IFACEMETHODIMP OnFolderChange(IFileDialog* pfd) noexcept override;
        IFACEMETHODIMP OnFileOk(IFileDialog*) noexcept override { return S_OK; }
        IFACEMETHODIMP OnFolderChanging(IFileDialog*, IShellItem*) noexcept override { return S_OK; }
        IFACEMETHODIMP OnSelectionChange(IFileDialog*) noexcept override { return S_OK; }
        IFACEMETHODIMP OnShareViolation(IFileDialog*, IShellItem*, FDE_SHAREVIOLATION_RESPONSE*) noexcept override { return S_OK; }
        IFACEMETHODIMP OnTypeChange(IFileDialog*) noexcept override { return S_OK; }
        IFACEMETHODIMP OnOverwrite(IFileDialog*, IShellItem*, FDE_OVERWRITE_RESPONSE*) noexcept override { return S_OK; }
    };

    struct PickerParameters {
        HWND HWnd{};
        winrt::hstring CommitButtonText;
        winrt::hstring Title;
        winrt::hstring SettingsIdentifier;
        winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId SuggestedStartLocation;
        std::vector<winrt::hstring> FileTypeFilterData{};
        std::vector<COMDLG_FILTERSPEC> FileTypeFilterParams{};
        int InitialFileTypeIndex{ DefaultInitialFileTypeIndex };
        winrt::hstring AllFilesText{ L"All Files" }; // initialize to All Files as a default value, will be updated by localization

        winrt::hstring SuggestedFileName;
        winrt::hstring SuggestedFolder;
        winrt::hstring SuggestedStartFolder;

        winrt::hstring FormatExtensionWithWildcard(winrt::hstring extension);
        winrt::hstring JoinExtensions(winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> extensions);

        void CaptureFilterSpecData(
            winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> fileTypeFilterView,
            winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::Windows::Foundation::Collections::IVector<winrt::hstring>> fileTypeChoicesView,
            int initialFileTypeIndex);

        void ConfigureDialog(winrt::com_ptr<IFileDialog> dialog);
        void ConfigureFileSaveDialog(winrt::com_ptr<IFileSaveDialog> dialog);

        winrt::hstring TryGetAppUserModelId();
        winrt::hstring TryGetProcessFullPath();

		bool ShowOverwritePrompt{ true };

    private:
        void CaptureFilterSpec(winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring> filters);
        void CaptureFilterSpec(winrt::Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::Windows::Foundation::Collections::IVector<winrt::hstring>> filters);
    };
}
