// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "FileOpenPicker.h"
#include "Microsoft.Windows.Storage.Pickers.FileOpenPicker.g.cpp"
#include "StoragePickersTelemetry.h"
#include <windows.h>
#include <shobjidl.h>
#include <shobjidl_core.h>
#include <winrt/Microsoft.UI.Interop.h>
#include "TerminalVelocityFeatures-StoragePickers.h"
#include "TerminalVelocityFeatures-StoragePickers2.h"
#include "PickerCommon.h"
#include "PickFileResult.h"
#include "PickerLocalization.h"

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
    FileOpenPicker::FileOpenPicker(winrt::Microsoft::UI::WindowId const& windowId)
        : m_windowId(windowId)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Storage::Pickers::Feature_StoragePickers::IsEnabled());
    }

    winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode FileOpenPicker::ViewMode()
    {
        return m_viewMode;
    }
    void FileOpenPicker::ViewMode(winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode const& value)
    {
        PickerCommon::ValidateViewMode(value);
        m_viewMode = value;
    }
    winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId FileOpenPicker::SuggestedStartLocation()
    {
        return m_suggestedStartLocation;
    }
    void FileOpenPicker::SuggestedStartLocation(winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId const& value)
    {
        PickerCommon::ValidateSuggestedStartLocation(value);
        m_suggestedStartLocation = value;
    }
    winrt::hstring FileOpenPicker::CommitButtonText()
    {
        return m_commitButtonText;
    }
    void FileOpenPicker::CommitButtonText(winrt::hstring const& value)
    {
        PickerCommon::ValidateStringNoEmbeddedNulls(value);
        m_commitButtonText = value;
    }
    winrt::hstring FileOpenPicker::Title()
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Storage::Pickers::Feature_StoragePickers2::IsEnabled());
        return m_title;
    }
    void FileOpenPicker::Title(winrt::hstring const& value)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Storage::Pickers::Feature_StoragePickers2::IsEnabled());
        PickerCommon::ValidateStringNoEmbeddedNulls(value);
        m_title = value;
    }
    winrt::hstring FileOpenPicker::SettingsIdentifier()
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Storage::Pickers::Feature_StoragePickers2::IsEnabled());
        return m_settingsIdentifier;
    }
    void FileOpenPicker::SettingsIdentifier(winrt::hstring const& value)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Storage::Pickers::Feature_StoragePickers2::IsEnabled());
        PickerCommon::ValidateStringNoEmbeddedNulls(value);
        m_settingsIdentifier = value;
    }
    winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::Windows::Foundation::Collections::IVector<winrt::hstring>> FileOpenPicker::FileTypeChoices()
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Storage::Pickers::Feature_StoragePickers2::IsEnabled());
        return m_fileTypeChoices;
    }
    winrt::Windows::Foundation::Collections::IVector<winrt::hstring> FileOpenPicker::FileTypeFilter()
    {
        return m_fileTypeFilter;
    }
    int FileOpenPicker::InitialFileTypeIndex()
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Storage::Pickers::Feature_StoragePickers2::IsEnabled());
        return m_initialFileTypeIndex;
    }
    void FileOpenPicker::InitialFileTypeIndex(int value)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Storage::Pickers::Feature_StoragePickers2::IsEnabled());
        PickerCommon::ValidateInitialFileTypeIndex(value);
        m_initialFileTypeIndex = value;
    }
    winrt::hstring FileOpenPicker::SuggestedFolder()
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Storage::Pickers::Feature_StoragePickers2::IsEnabled());
        return m_suggestedFolder;
    }
    void FileOpenPicker::SuggestedFolder(winrt::hstring const& value)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Storage::Pickers::Feature_StoragePickers2::IsEnabled());
        PickerCommon::ValidateFolderPath(value, "SuggestedFolder");
        m_suggestedFolder = value;
    }
    winrt::hstring FileOpenPicker::SuggestedStartFolder()
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Storage::Pickers::Feature_StoragePickers2::IsEnabled());
        return m_suggestedStartFolder;
    }
    void FileOpenPicker::SuggestedStartFolder(winrt::hstring const& value)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Storage::Pickers::Feature_StoragePickers2::IsEnabled());
        PickerCommon::ValidateFolderPath(value, "SuggestedStartFolder");
        m_suggestedStartFolder = value;
    }

    void FileOpenPicker::CaptureParameters(PickerCommon::PickerParameters& parameters)
    {
        parameters.HWnd = winrt::Microsoft::UI::GetWindowFromWindowId(m_windowId);
        parameters.CommitButtonText = m_commitButtonText;
        parameters.Title = m_title;
        parameters.SettingsIdentifier = m_settingsIdentifier;
        parameters.SuggestedFolder = m_suggestedFolder;
        parameters.SuggestedStartLocation = m_suggestedStartLocation;
        parameters.SuggestedStartFolder = m_suggestedStartFolder;
        // Note: the InitialFileTypeIndex will be decided while capturing the filter spec data.
        parameters.CaptureFilterSpecData(m_fileTypeFilter.GetView(), m_fileTypeChoices.GetView(), m_initialFileTypeIndex);
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::Storage::Pickers::PickFileResult> FileOpenPicker::PickSingleFileAsync()
    {
        // Keep a strong ref so m_telemetryHelper (a member of the picker) stays valid after co_awaits.
        auto lifetime{ get_strong() };

        auto logTelemetry{ StoragePickersTelemetry::FileOpenPickerPickSingleFile::Start(m_telemetryHelper) };

        PickerCommon::PickerParameters parameters{};
        parameters.AllFilesText = PickerLocalization::GetStoragePickersLocalizationText(PickerCommon::AllFilesLocalizationKey);

        CaptureParameters(parameters);

        auto cancellationToken = co_await winrt::get_cancellation_token();
        cancellationToken.enable_propagation(true);
        co_await winrt::resume_background();

        if (cancellationToken())
        {
            logTelemetry.Stop(m_telemetryHelper, false);
            co_return nullptr;
        }

        auto dialog = create_instance<IFileOpenDialog>(CLSID_FileOpenDialog, CLSCTX_INPROC_SERVER);

        parameters.ConfigureDialog(dialog);

        {
            auto hr = dialog->Show(parameters.HWnd);
            if (FAILED(hr) || cancellationToken())
            {
                logTelemetry.Stop(m_telemetryHelper, false);
                co_return nullptr;
            }
        }

        winrt::com_ptr<IShellItem> shellItem{};
        check_hresult(dialog->GetResult(shellItem.put()));
        auto path = PickerCommon::GetPathFromShellItem(shellItem);

        if (cancellationToken())
        {
            logTelemetry.Stop(m_telemetryHelper, false);
            co_return nullptr;
        }

        auto result = make<winrt::Microsoft::Windows::Storage::Pickers::implementation::PickFileResult>(path);

        logTelemetry.Stop(m_telemetryHelper, true);
        co_return result;
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Microsoft::Windows::Storage::Pickers::PickFileResult> > FileOpenPicker::PickMultipleFilesAsync()
    {
        // Keep a strong ref so m_telemetryHelper (a member of the picker) stays valid after co_awaits.
        auto lifetime{ get_strong() };

        auto logTelemetry{ StoragePickersTelemetry::FileOpenPickerPickMultipleFile::Start(m_telemetryHelper) };

        PickerCommon::PickerParameters parameters{};
        parameters.AllFilesText = PickerLocalization::GetStoragePickersLocalizationText(PickerCommon::AllFilesLocalizationKey);

        CaptureParameters(parameters);

        auto cancellationToken = co_await winrt::get_cancellation_token();
        cancellationToken.enable_propagation(true);
        co_await winrt::resume_background();

        winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::Storage::Pickers::PickFileResult> results{ winrt::single_threaded_vector<winrt::Microsoft::Windows::Storage::Pickers::PickFileResult>() };

        if (cancellationToken())
        {
            logTelemetry.Stop(m_telemetryHelper, true, false);
            co_return results.GetView();
        }

        auto dialog = create_instance<IFileOpenDialog>(CLSID_FileOpenDialog, CLSCTX_INPROC_SERVER);

        parameters.ConfigureDialog(dialog);

        FILEOPENDIALOGOPTIONS dialogOptions;
        check_hresult(dialog->GetOptions(&dialogOptions));
        check_hresult(dialog->SetOptions(dialogOptions | FOS_ALLOWMULTISELECT));

        {
            auto hr = dialog->Show(parameters.HWnd);
            if (FAILED(hr) || cancellationToken())
            {
                logTelemetry.Stop(m_telemetryHelper, true, false);
                co_return results.GetView();
            }
        }

        winrt::com_ptr<IShellItemArray> shellItems{};
        check_hresult(dialog->GetResults(shellItems.put()));

        DWORD itemCount = 0;
        check_hresult(shellItems->GetCount(&itemCount));

        winrt::com_ptr<IShellItem> shellItem{};
        for (DWORD i = 0; i < itemCount; i++)
        {
            check_hresult(shellItems->GetItemAt(i, shellItem.put()));
            auto path = PickerCommon::GetPathFromShellItem(shellItem);
            auto result{ make<winrt::Microsoft::Windows::Storage::Pickers::implementation::PickFileResult>(path) };
            results.Append(result);
        }

        bool isCancelled = false;
        if (cancellationToken())
        {
            results.Clear();
            isCancelled = true;
        }
        auto resultView = results.GetView();

        if (results.Size() > 0)
        {
            logTelemetry.Stop(m_telemetryHelper, isCancelled, true);
        }
        else
        {
            logTelemetry.Stop(m_telemetryHelper, isCancelled, false);
        }
        co_return resultView;
    }
}
