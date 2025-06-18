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
        m_viewMode = value;
    }
    hstring FileOpenPicker::SettingsIdentifier()
    {
        return m_settingsIdentifier;
    }
    void FileOpenPicker::SettingsIdentifier(hstring const& value)
    {
        m_settingsIdentifier = value;
    }
    winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId FileOpenPicker::SuggestedStartLocation()
    {
        return m_suggestedStartLocation;
    }
    void FileOpenPicker::SuggestedStartLocation(winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId const& value)
    {
        m_suggestedStartLocation = value;
    }
    winrt::hstring FileOpenPicker::CommitButtonText()
    {
        return m_commitButtonText;
    }
    void FileOpenPicker::CommitButtonText(winrt::hstring const& value)
    {
        m_commitButtonText = value;
    }
    winrt::Windows::Foundation::Collections::IVector<hstring> FileOpenPicker::FileTypeFilter()
    {
        return m_fileTypeFilter;
    }

    void FileOpenPicker::CaptureParameters(PickerCommon::PickerParameters& parameters)
    {
        parameters.HWnd = winrt::Microsoft::UI::GetWindowFromWindowId(m_windowId);
        parameters.CommitButtonText = m_commitButtonText;
        parameters.SettingsIdentifierId = m_settingsIdentifier;
        parameters.PickerLocationId = m_suggestedStartLocation;
        parameters.CaptureFilterSpec(m_fileTypeFilter.GetView());
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::Storage::Pickers::PickFileResult> FileOpenPicker::PickSingleFileAsync()
    {
        // TODO: remove get strong reference when telementry is safe stop
        auto lifetime{ get_strong() };

        auto logTelemetry{ StoragePickersTelemetry::FileOpenPickerPickSingleFile::Start(m_telemetryHelper) };

        PickerCommon::PickerParameters parameters{};
        parameters.AllFilesText = PickerCommon::GetStoragePickersLocalizationText(PickerCommon::AllFilesLocalizationKey);

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
        check_hresult(dialog->SetFileTypeIndex(parameters.FileTypeFilterPara.size()));

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
        // TODO: remove get strong reference when telementry is safe stop
        auto lifetime{ get_strong() };

        auto logTelemetry{ StoragePickersTelemetry::FileOpenPickerPickMultipleFile::Start(m_telemetryHelper) };

        // capture parameters to avoid using get strong referece of picker
        PickerCommon::PickerParameters parameters{};
        parameters.AllFilesText = PickerCommon::GetStoragePickersLocalizationText(PickerCommon::AllFilesLocalizationKey);

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
        check_hresult(dialog->SetFileTypeIndex(parameters.FileTypeFilterPara.size()));

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
