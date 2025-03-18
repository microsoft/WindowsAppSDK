#include "pch.h"
#include "FileSavePicker.h"
#include "Microsoft.Windows.Storage.Pickers.FileSavePicker.g.cpp"
#include <windows.h>
#include <shobjidl.h>
#include <shobjidl_core.h>
#include <KnownFolders.h>
#include <wil/cppwinrt.h>
#include <wil/com.h>
#include <wil/resource.h>
#include <winrt/Microsoft.UI.Interop.h>
#include <winrt/Windows.Foundation.Collections.h>
#include "PickerCommon.h"
#include "PickFileResult.h"

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{

    FileSavePicker::FileSavePicker(winrt::Microsoft::UI::WindowId const& windowId)
        : m_windowId(windowId)
    {
        THROW_HR_IF(E_NOTIMPL, !::Microsoft::Windows::Storage::Pickers::Feature_StoragePickers::IsEnabled());
    }
    hstring FileSavePicker::SettingsIdentifier()
    {
        return m_settingsIdentifier;
    }
    void FileSavePicker::SettingsIdentifier(hstring const& value)
    {
        m_settingsIdentifier = value;
    }
    winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId FileSavePicker::SuggestedStartLocation()
    {
        return m_suggestedStartLocation;
    }
    void FileSavePicker::SuggestedStartLocation(winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId const& value)
    {
        m_suggestedStartLocation = value;
    }
    hstring FileSavePicker::CommitButtonText()
    {
        return m_commitButtonText;
    }
    void FileSavePicker::CommitButtonText(hstring const& value)
    {
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
    winrt::Windows::Storage::StorageFile FileSavePicker::SuggestedSaveFile()
    {
        return m_suggestedSaveFile;
    }
    void FileSavePicker::SuggestedSaveFile(winrt::Windows::Storage::StorageFile const& value)
    {
        m_suggestedSaveFile = value;
    }
    hstring FileSavePicker::SuggestedFileName()
    {
        return m_suggestedFileName;
    }
    void FileSavePicker::SuggestedFileName(hstring const& value)
    {
        m_suggestedFileName = value;
    }


    void FileSavePicker::CaptureParameters(PickerCommon::PickerParameters& parameters)
    {
        parameters.HWnd = winrt::Microsoft::UI::GetWindowFromWindowId(m_windowId);
        parameters.CommitButtonText = m_commitButtonText;
        parameters.SettingsIdentifierId = m_settingsIdentifier;
        parameters.PickerLocationId = m_suggestedStartLocation;
        parameters.FileTypeFilterPara = PickerCommon::CaptureFilterSpec(parameters.FileTypeFilterData, m_fileTypeChoices.GetView());

    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::Storage::Pickers::PickFileResult> FileSavePicker::PickSaveFileAsync()
    {
        PickerCommon::PickerParameters parameters{};
        CaptureParameters(parameters);
        auto defaultFileExtension = m_defaultFileExtension;
        auto suggestedSaveFile = m_suggestedSaveFile;
        auto suggestedFileName = m_suggestedFileName;
        auto fileTypeChoices = m_fileTypeChoices;

        co_await winrt::resume_background();
        auto cancellationToken = co_await winrt::get_cancellation_token();
        if (cancellationToken())
        {
            co_return nullptr;
        }

        auto dialog = create_instance<IFileSaveDialog>(CLSID_FileSaveDialog, CONTEXT_ALL);
        parameters.ConfigureDialog(dialog);

        if (!PickerCommon::IsHStringNullOrEmpty(defaultFileExtension))
        {
            check_hresult(dialog->SetDefaultExtension(defaultFileExtension.c_str()));
        }

        if (!PickerCommon::IsHStringNullOrEmpty(suggestedFileName))
        {
            check_hresult(dialog->SetFileName(suggestedFileName.c_str()));
        }

        if (suggestedSaveFile != nullptr)
        {
            winrt::com_ptr<IShellItem> shellItem;
            check_hresult(SHCreateItemFromParsingName(suggestedSaveFile.Path().c_str(), nullptr, IID_PPV_ARGS(shellItem.put())));
            check_hresult(dialog->SetSaveAsItem(shellItem.get()));
        }

        {
            auto hr = dialog->Show(parameters.HWnd);
            if (FAILED(hr))
            {
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

        // Check if the file name has an extension
        if (fileNameStr.find_last_of(L".") == std::wstring::npos)
        {
            // If the user defined file name doesn't have an extension,
            //     automatically use the first extension from the first category in fileTypeChoices.
            auto firstCategory = fileTypeChoices.First().Current();
            auto firstExtension = firstCategory.Value().GetAt(0);
            pathStr = pathStr + firstExtension;
        }

        // Create a file. If the file already exists, will prompt to let user select cancele or override.
        auto [handle, _] = wil::try_open_or_truncate_existing_file(pathStr.c_str(), GENERIC_WRITE);

        if (cancellationToken())
        {
            co_return nullptr;
        }

        co_return make<winrt::Microsoft::Windows::Storage::Pickers::implementation::PickFileResult>(pathStr);
    }
}
