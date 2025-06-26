// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "FolderPicker.h"
#include "FolderPicker.g.cpp"
#include "StoragePickersTelemetry.h"
#include <shobjidl.h>
#include <shobjidl_core.h>
#include <winrt/Microsoft.UI.Interop.h>
#include "PickerCommon.h"
#include "PickFolderResult.h"

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
    // Define the static member
    winrt::com_ptr<IShellItem> FolderPicker::s_lastBrowsedFolder{};

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
        m_viewMode = value;
    }
    hstring FolderPicker::SettingsIdentifier()
    {
        return m_settingsIdentifier;
    }
    void FolderPicker::SettingsIdentifier(hstring const& value)
    {
        m_settingsIdentifier = value;
    }
    winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId FolderPicker::SuggestedStartLocation()
    {
        return m_suggestedStartLocation;
    }
    void FolderPicker::SuggestedStartLocation(winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId const& value)
    {
        m_suggestedStartLocation = value;
    }
    hstring FolderPicker::CommitButtonText()
    {
        return m_commitButtonText;
    }
    void FolderPicker::CommitButtonText(hstring const& value)
    {
        m_commitButtonText = value;
    }

    void FolderPicker::CaptureParameters(PickerCommon::PickerParameters& parameters)
    {
        parameters.HWnd = winrt::Microsoft::UI::GetWindowFromWindowId(m_windowId);
        parameters.CommitButtonText = m_commitButtonText;
        parameters.SettingsIdentifierId = m_settingsIdentifier;
        parameters.PickerLocationId = m_suggestedStartLocation;
    }


    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::Storage::Pickers::PickFolderResult> FolderPicker::PickSingleFolderAsync()
    {
        // TODO: remove get strong reference when telementry is safe stop
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
        FILEOPENDIALOGOPTIONS dialogOptions;
        check_hresult(dialog->GetOptions(&dialogOptions));
        check_hresult(dialog->SetOptions(dialogOptions | FOS_PICKFOLDERS));

        // Create event handler to track folder navigation
        auto eventHandler = new FolderDialogEventHandler();
        DWORD eventCookie;
        check_hresult(dialog->Advise(eventHandler, &eventCookie));

        // Set the folder to the last browsed folder if available
        if (s_lastBrowsedFolder)
        {
            check_hresult(dialog->SetFolder(s_lastBrowsedFolder.get()));
        }

        HRESULT hr;
        {
            hr = dialog->Show(parameters.HWnd);
            if (FAILED(hr) || cancellationToken())
            {
                // Clean up event handler
                dialog->Unadvise(eventCookie);
                eventHandler->Release();
                logTelemetry.Stop(m_telemetryHelper, false);
                co_return nullptr;
            }
        }

        // Save the last browsed folder from the event handler
        s_lastBrowsedFolder = eventHandler->GetLastBrowsedFolder();

        // Clean up event handler
        dialog->Unadvise(eventCookie);
        eventHandler->Release();

        // Get the selected folder
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
}
