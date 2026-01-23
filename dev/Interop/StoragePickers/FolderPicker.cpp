// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "FolderPicker.h"
#include "Microsoft.Windows.Storage.Pickers.FolderPicker.g.cpp"
#include "StoragePickersTelemetry.h"
#include <shobjidl.h>
#include <shobjidl_core.h>
#include <winrt/Microsoft.UI.Interop.h>
#include "TerminalVelocityFeatures-StoragePickers.h"
#include "TerminalVelocityFeatures-StoragePickers2.h"
#include "PickerCommon.h"
#include "PickFolderResult.h"
#include "PickerLocalization.h" 

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
    FolderPicker::FolderPicker(winrt::Microsoft::UI::WindowId const& windowId)
        : m_windowId(windowId)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Storage::Pickers::Feature_StoragePickers::IsEnabled());
    }
    winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode FolderPicker::ViewMode()
    {
        return m_viewMode;
    }
    void FolderPicker::ViewMode(winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode const& value)
    {
        PickerCommon::ValidateViewMode(value);
        m_viewMode = value;
    }
    winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId FolderPicker::SuggestedStartLocation()
    {
        return m_suggestedStartLocation;
    }
    void FolderPicker::SuggestedStartLocation(winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId const& value)
    {
        PickerCommon::ValidateSuggestedStartLocation(value);
        m_suggestedStartLocation = value;
    }
    hstring FolderPicker::CommitButtonText()
    {
        return m_commitButtonText;
    }
    void FolderPicker::CommitButtonText(hstring const& value)
    {
        PickerCommon::ValidateStringNoEmbeddedNulls(value);
        m_commitButtonText = value;
    }
    winrt::hstring FolderPicker::Title()
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Storage::Pickers::Feature_StoragePickers2::IsEnabled());
        return m_title;
    }
    void FolderPicker::Title(winrt::hstring const& value)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Storage::Pickers::Feature_StoragePickers2::IsEnabled());
        PickerCommon::ValidateStringNoEmbeddedNulls(value);
        m_title = value;
    }
    winrt::hstring FolderPicker::SettingsIdentifier()
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Storage::Pickers::Feature_StoragePickers2::IsEnabled());
        return m_settingsIdentifier;
    }
    void FolderPicker::SettingsIdentifier(winrt::hstring const& value)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Storage::Pickers::Feature_StoragePickers2::IsEnabled());
        PickerCommon::ValidateStringNoEmbeddedNulls(value);
        m_settingsIdentifier = value;
    }
    hstring FolderPicker::SuggestedFolder()
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Storage::Pickers::Feature_StoragePickers2::IsEnabled());
        return m_suggestedFolder;
    }
    void FolderPicker::SuggestedFolder(hstring const& value)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Storage::Pickers::Feature_StoragePickers2::IsEnabled());
        PickerCommon::ValidateFolderPath(value, "SuggestedFolder");
        m_suggestedFolder = value;
    }
    hstring FolderPicker::SuggestedStartFolder()
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Storage::Pickers::Feature_StoragePickers2::IsEnabled());
        return m_suggestedStartFolder;
    }
    void FolderPicker::SuggestedStartFolder(hstring const& value)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Storage::Pickers::Feature_StoragePickers2::IsEnabled());
        PickerCommon::ValidateFolderPath(value, "SuggestedStartFolder");
        m_suggestedStartFolder = value;
    }

    void FolderPicker::CaptureParameters(PickerCommon::PickerParameters& parameters)
    {
        parameters.HWnd = winrt::Microsoft::UI::GetWindowFromWindowId(m_windowId);
        parameters.CommitButtonText = m_commitButtonText;
        parameters.Title = m_title;
        parameters.SettingsIdentifier = m_settingsIdentifier;
        parameters.SuggestedFolder = m_suggestedFolder;
        parameters.SuggestedStartLocation = m_suggestedStartLocation;
        parameters.SuggestedStartFolder = m_suggestedStartFolder;
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::Storage::Pickers::PickFolderResult> FolderPicker::PickSingleFolderAsync()
    {
        // Keep a strong ref so m_telemetryHelper (a member of the picker) stays valid after co_awaits.
        auto lifetime{ get_strong() };

        auto logTelemetry{ StoragePickersTelemetry::FolderPickerPickSingleFolder::Start(m_telemetryHelper) };

        PickerCommon::PickerParameters parameters{};
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
        dialog->SetOptions(FOS_PICKFOLDERS | FOS_FORCEFILESYSTEM);

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

        auto result = make<winrt::Microsoft::Windows::Storage::Pickers::implementation::PickFolderResult>(path);

        logTelemetry.Stop(m_telemetryHelper, true);
        co_return result;
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Microsoft::Windows::Storage::Pickers::PickFolderResult>> FolderPicker::PickMultipleFoldersAsync()
    {
        // Keep a strong ref so m_telemetryHelper (a member of the picker) stays valid after co_awaits.
        auto lifetime{ get_strong() };

        auto logTelemetry{ StoragePickersTelemetry::FolderPickerPickMultipleFolder::Start(m_telemetryHelper) };

        PickerCommon::PickerParameters parameters{};
        CaptureParameters(parameters);
        
        auto cancellationToken = co_await winrt::get_cancellation_token();
        cancellationToken.enable_propagation(true);
        co_await winrt::resume_background();

        winrt::Windows::Foundation::Collections::IVector<winrt::Microsoft::Windows::Storage::Pickers::PickFolderResult> results{ winrt::single_threaded_vector<winrt::Microsoft::Windows::Storage::Pickers::PickFolderResult>() };
        if (cancellationToken())
        {
            logTelemetry.Stop(m_telemetryHelper, true, false);
            co_return results.GetView();
        }

        auto dialog = create_instance<IFileOpenDialog>(CLSID_FileOpenDialog, CLSCTX_INPROC_SERVER);
        parameters.ConfigureDialog(dialog);

        FILEOPENDIALOGOPTIONS dialogOptions;
        check_hresult(dialog->GetOptions(&dialogOptions));
        check_hresult(dialog->SetOptions(dialogOptions | FOS_PICKFOLDERS | FOS_FORCEFILESYSTEM | FOS_ALLOWMULTISELECT));

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
            auto result{ make<winrt::Microsoft::Windows::Storage::Pickers::implementation::PickFolderResult>(path) };
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
