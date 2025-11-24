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
#include "TerminalVelocityFeatures-StoragePickers2.h"
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
        PickerCommon::ValidateFolderPath(value, "SuggestedFolder");
        m_suggestedFolder = value;
    }

    hstring FileSavePicker::SuggestedStartFolder()
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Storage::Pickers::Feature_StoragePickers2::IsEnabled());
        return m_suggestedStartFolder;
    }
    void FileSavePicker::SuggestedStartFolder(hstring const& value)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Storage::Pickers::Feature_StoragePickers2::IsEnabled());
        PickerCommon::ValidateFolderPath(value, "SuggestedStartFolder");
        m_suggestedStartFolder = value;
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
        parameters.DefaultFileExtension = m_defaultFileExtension;
        parameters.SuggestedFileName = m_suggestedFileName;
        parameters.SuggestedFolder = m_suggestedFolder;
        parameters.SuggestedStartLocation = m_suggestedStartLocation;
        parameters.SuggestedStartFolder = m_suggestedStartFolder;
        parameters.CaptureFilterSpecData(
            winrt::Windows::Foundation::Collections::IVectorView<winrt::hstring>{},
            m_fileTypeChoices.GetView());
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::Storage::Pickers::PickFileResult> FileSavePicker::PickSaveFileAsync()
    {
        // TODO: remove get strong reference when telementry is safe stop
        auto lifetime{ get_strong() };

        auto logTelemetry{ StoragePickersTelemetry::FileSavePickerPickSingleFile::Start(m_telemetryHelper) };

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

        auto dialog = create_instance<IFileSaveDialog>(CLSID_FileSaveDialog, CLSCTX_INPROC_SERVER);
        parameters.ConfigureDialog(dialog);
        parameters.ConfigureFileSaveDialog(dialog);

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

        // Create an empty file if the file doesn't exist,
        // If the file already exists, do nothing.
        auto [handle, _] = wil::try_open_or_create_file(pathStr.c_str(), GENERIC_WRITE);

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
