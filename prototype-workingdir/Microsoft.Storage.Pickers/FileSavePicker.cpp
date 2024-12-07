#include "pch.h"
#include "FileSavePicker.h"
#include "FileSavePicker.g.cpp"
#include <windows.h>
#include <shobjidl.h>
#include <shobjidl_core.h>
#include <KnownFolders.h>
#include <wil/cppwinrt.h>
#include <wil/com.h>
#include <wil/resource.h>
#include <Microsoft.Ui.Xaml.Window.h>
#include <winrt/Microsoft.UI.Interop.h>
#include <winrt/Windows.Foundation.Collections.h>
#include "PickerCommon.h"

namespace winrt::Microsoft::Storage::Pickers::implementation
{

    FileSavePicker::FileSavePicker(winrt::Microsoft::UI::WindowId const& windowId)
        : m_windowId(windowId)
    {
    }
    hstring FileSavePicker::SettingsIdentifier()
    {
        return m_SettingsIdentifier;
    }
    void FileSavePicker::SettingsIdentifier(hstring const& value)
    {
        m_SettingsIdentifier = value;
    }
    winrt::Microsoft::Storage::Pickers::PickerLocationId FileSavePicker::SuggestedStartLocation()
    {
        return m_PickerLocationId;
    }
    void FileSavePicker::SuggestedStartLocation(winrt::Microsoft::Storage::Pickers::PickerLocationId const& value)
    {
        m_PickerLocationId = value;
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

    struct FileSavePickerParameters {
        HWND HWnd;
        winrt::hstring CommitButtonText;
        winrt::hstring SettingsIdentifierId;
        PickerLocationId PickerLocationId;

        void ConfigureDialog(winrt::com_ptr<IFileSaveDialog> dialog)
        {
            PickerCommon::ConfigureDialogCommon(dialog, CommitButtonText, SettingsIdentifierId, PickerLocationId);
        }
    };

    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFile> FileSavePicker::PickSaveFileAsync()
    {
        FileSavePickerParameters parameters{};

        co_await winrt::resume_background();
		auto cancellationToken = co_await winrt::get_cancellation_token();
		if (cancellationToken())
		{
			co_return nullptr;
		}

        auto dialog = create_instance<IFileSaveDialog>(CLSID_FileSaveDialog, CONTEXT_ALL);

        parameters.ConfigureDialog(dialog);

        // TODO: set filter typse
        COMDLG_FILTERSPEC save_filter[1];
        save_filter[0].pszName = L"All files";
        save_filter[0].pszSpec = L"*.*";
        check_hresult(dialog->SetFileTypes(1, save_filter));

        {
            auto hr = dialog->Show(parameters.HWnd);
            if (FAILED(hr))
            {
                co_return nullptr;
            }
        }

        winrt::com_ptr<IShellItem> shellItem{};
        check_hresult(dialog->GetResult(shellItem.put()));

        auto& file = co_await PickerCommon::CreateStorageFileFromShellItem(shellItem);
        if (cancellationToken())
        {
            co_return nullptr;
        }

        co_return file;
    }
}
