#include "pch.h"
#include "FileOpenPicker.h"
#include "FileOpenPicker.g.cpp"
#include <windows.h>
#include <shobjidl.h>
#include <shobjidl_core.h>
#include <winrt/Microsoft.UI.Interop.h>
#include "PickerCommon.h"

namespace winrt::Microsoft::Storage::Pickers::implementation
{
    FileOpenPicker::FileOpenPicker(winrt::Microsoft::UI::WindowId const& windowId)
        : m_windowId(windowId)
    {
    }

    winrt::Microsoft::Storage::Pickers::PickerViewMode FileOpenPicker::ViewMode()
    {
        return m_viewMode;
    }
    void FileOpenPicker::ViewMode(winrt::Microsoft::Storage::Pickers::PickerViewMode const& value)
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
    winrt::Microsoft::Storage::Pickers::PickerLocationId FileOpenPicker::SuggestedStartLocation()
    {
        return m_suggestedStartLocation;
    }
    void FileOpenPicker::SuggestedStartLocation(winrt::Microsoft::Storage::Pickers::PickerLocationId const& value)
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
        parameters.FileTypeFilterPara = PickerCommon::CaptureFilterSpec(parameters.FileTypeFilterData, m_fileTypeFilter.GetView());
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFile> FileOpenPicker::PickSingleFileAsync()
    {
        PickerCommon::PickerParameters parameters{};

        CaptureParameters(parameters);

        co_await winrt::resume_background();

        auto cancellationToken = co_await winrt::get_cancellation_token();
        if (cancellationToken())
        {
            co_return nullptr;
        }

        // TODO: should we initialize COM?
        // wil::com_initialize_ex initializeCom{ COINIT_APARTMENTTHREADED };

        auto dialog = create_instance<IFileOpenDialog>(CLSID_FileOpenDialog, CONTEXT_ALL);

        parameters.ConfigureDialog(dialog);

        {
            auto hr = dialog->Show(parameters.HWnd);
            if (FAILED(hr) || cancellationToken())
            {
                co_return nullptr;
            }
        }

        winrt::com_ptr<IShellItem> shellItem{};
        check_hresult(dialog->GetResult(shellItem.put()));
        auto file = co_await PickerCommon::CreateStorageFileFromShellItem(shellItem);

        if (cancellationToken())
        {
            co_return nullptr;
        }
        co_return file;
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Storage::StorageFile>> FileOpenPicker::PickMultipleFilesAsync()
    {
        PickerCommon::PickerParameters parameters{};

        CaptureParameters(parameters);

        co_await winrt::resume_background();

        winrt::Windows::Foundation::Collections::IVector<winrt::Windows::Storage::StorageFile> results{ winrt::single_threaded_vector<winrt::Windows::Storage::StorageFile>() };

        auto cancellationToken = co_await winrt::get_cancellation_token();
        if (cancellationToken())
        {
            co_return results.GetView();
        }

        auto dialog = create_instance<IFileOpenDialog>(CLSID_FileOpenDialog, CONTEXT_ALL);

        parameters.ConfigureDialog(dialog);

        check_hresult(dialog->SetOptions(FOS_ALLOWMULTISELECT));

        {
            auto hr = dialog->Show(parameters.HWnd);
            if (FAILED(hr) || cancellationToken())
            {
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
            auto file = co_await PickerCommon::CreateStorageFileFromShellItem(shellItem);
            results.Append(file);
        }

        if (cancellationToken())
        {
            results.Clear();
            co_return results.GetView();
        }
        co_return results.GetView();
    }
}
