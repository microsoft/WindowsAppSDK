// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "FileSavePicker.h"
#include "Microsoft.Windows.Storage.Pickers.FileSavePicker.g.cpp"
#include "StoragePickersTelemetry.h"
#include <windows.h>
#include <shobjidl.h>
#include <shobjidl_core.h>
#include <KnownFolders.h>
#include <wil/cppwinrt.h>
#include <wil/com.h>
#include <wil/resource.h>
#include <winrt/Microsoft.UI.Interop.h>
#include <winrt/Windows.Foundation.Collections.h>
#include "TerminalVelocityFeatures-StoragePickers.h"
#include "PickerCommon.h"
#include "PickerLocalization.h"
#include "PickFileResult.h"

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{

    FileSavePicker::FileSavePicker(winrt::Microsoft::UI::WindowId const& windowId)
        : m_windowId(windowId)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Storage::Pickers::Feature_StoragePickers::IsEnabled());
    }
    winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId FileSavePicker::SuggestedStartLocation()
    {
        return m_suggestedStartLocation;
    }
    void FileSavePicker::SuggestedStartLocation(winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId const& value)
    {
        PickerCommon::ValidateSuggestedStartLocation(value);
        m_suggestedStartLocation = value;
    }
    hstring FileSavePicker::CommitButtonText()
    {
        return m_commitButtonText;
    }
    void FileSavePicker::CommitButtonText(hstring const& value)
    {
        PickerCommon::ValidateStringNoEmbeddedNulls(value);
        m_commitButtonText = value;
    }
    winrt::Windows::Foundation::Collections::IMap<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>> FileSavePicker::FileTypeChoices()
    {
        return m_fileTypeChoices;
    }
    hstring FileSavePicker::DefaultFileExtension()
    {
        return m_defaultFileExtension;
    }
    void FileSavePicker::DefaultFileExtension(hstring const& value)
    {
        m_defaultFileExtension = value;
    }
    hstring FileSavePicker::SuggestedFolder()
    {
        return m_suggestedFolder;
    }
    void FileSavePicker::SuggestedFolder(hstring const& value)
    {
        PickerCommon::ValidateSuggestedFolder(value);
        m_suggestedFolder = value;
    }

    hstring FileSavePicker::SuggestedFileName()
    {
        return m_suggestedFileName;
    }

    void FileSavePicker::SuggestedFileName(hstring const& value)
    {
        PickerCommon::ValidateSuggestedFileName(value);
        m_suggestedFileName = value;
    }

    void FileSavePicker::CaptureParameters(PickerCommon::PickerParameters& parameters)
    {
        parameters.HWnd = winrt::Microsoft::UI::GetWindowFromWindowId(m_windowId);
        parameters.CommitButtonText = m_commitButtonText;
        parameters.PickerLocationId = m_suggestedStartLocation;
        parameters.SuggestedFileName = m_suggestedFileName;
        parameters.SuggestedFolder = m_suggestedFolder;
        parameters.CaptureFilterSpec(m_fileTypeChoices.GetView());
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::Storage::Pickers::PickFileResult> FileSavePicker::PickSaveFileAsync()
    {
        // TODO: remove get strong reference when telementry is safe stop
        auto lifetime{ get_strong() };

        auto logTelemetry{ StoragePickersTelemetry::FileSavePickerPickSingleFile::Start(m_telemetryHelper) };

        PickerCommon::PickerParameters parameters{};
        parameters.AllFilesText = PickerLocalization::GetStoragePickersLocalizationText(PickerCommon::AllFilesLocalizationKey);

        CaptureParameters(parameters);

        auto defaultFileExtension = m_defaultFileExtension;
        auto suggestedFolder = m_suggestedFolder;
        auto suggestedFileName = m_suggestedFileName;
        auto fileTypeChoices = m_fileTypeChoices;

        auto cancellationToken = co_await winrt::get_cancellation_token();
        cancellationToken.enable_propagation(true);
        co_await winrt::resume_background();

        if (cancellationToken())
        {
            logTelemetry.Stop(m_telemetryHelper, false);
            co_return nullptr;
        }

        auto dialog = create_instance<IFileSaveDialog>(CLSID_FileSaveDialog, CLSCTX_INPROC_SERVER);
        parameters.ConfigureDialog(dialog);
        parameters.ConfigureFileSaveDialog(dialog);

        if (!PickerCommon::IsHStringNullOrEmpty(defaultFileExtension))
        {
            // the default extension has a ".", like ".txt". remove the "." (a.k.a "txt") then set it to the dialog
            //      otherwise, the diaplayed file name would have two "."
            check_hresult(dialog->SetDefaultExtension(defaultFileExtension.c_str() + 1));
        }
        else
        {
            check_hresult(dialog->SetDefaultExtension(L""));
        }

        FILEOPENDIALOGOPTIONS dialogOptions;
        check_hresult(dialog->GetOptions(&dialogOptions));
        check_hresult(dialog->SetOptions(dialogOptions | FOS_STRICTFILETYPES));

        {
            auto hr = dialog->Show(parameters.HWnd);
            if (FAILED(hr))
            {
                logTelemetry.Stop(m_telemetryHelper, false);
                co_return nullptr;
            }
        }

        winrt::com_ptr<IShellItem> shellItem{};
        check_hresult(dialog->GetResult(shellItem.put()));

        // Get the file path from the dialog
        wil::unique_cotaskmem_string filePath{};
        check_hresult(shellItem->GetDisplayName(SIGDN_FILESYSPATH, filePath.put()));
        winrt::hstring pathStr(filePath.get());

        wil::unique_cotaskmem_string fileName;
        check_hresult(shellItem->GetDisplayName(SIGDN_NORMALDISPLAY, fileName.put()));
        std::wstring fileNameStr(fileName.get());

        // Create a file. If the file already exists,
        // since common item dialog prompts to let user select cancel or override, thus we can safely truncate here.
        // Due to our design spec to align with UWP pickers, we need ensure existance of picked file.
        auto [handle, _] = wil::try_open_or_truncate_existing_file(pathStr.c_str(), GENERIC_WRITE);

        if (cancellationToken())
        {
            logTelemetry.Stop(m_telemetryHelper, false);
            co_return nullptr;
        }

        auto result = make<winrt::Microsoft::Windows::Storage::Pickers::implementation::PickFileResult>(pathStr);

        logTelemetry.Stop(m_telemetryHelper, true);
        co_return result;
    }
}
