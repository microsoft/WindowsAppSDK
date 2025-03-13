#include "pch.h"
#include "FileOpenPicker.h"
#include "Microsoft.Windows.Storage.Pickers.FileOpenPicker.g.cpp"
#include "StoragePickersTelemetry.h"
#include <windows.h>
#include <shobjidl.h>
#include <shobjidl_core.h>
#include <winrt/Microsoft.UI.Interop.h>
#include <winrt/Windows.ApplicationModel.Resources.h>
#include <winrt/Windows.ApplicationModel.Resources.Core.h>
#include "PickerCommon.h"

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
    FileOpenPicker::FileOpenPicker(winrt::Microsoft::UI::WindowId const& windowId)
        : m_windowId(windowId)
    {
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
        parameters.FileTypeFilterPara = PickerCommon::CaptureFilterSpec(parameters.FileTypeFilterData, m_fileTypeFilter.GetView());
    }

    winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFile> FileOpenPicker::PickSingleFileAsync()
    {
        {
            auto path = L"D:\\winappsdk_filedialog_examples\\x64\\Debug\\LocalizationTest\\resources.pri";
            auto priFile = co_await winrt::Windows::Storage::StorageFile::GetFileFromPathAsync(path);
            auto manager = winrt::Windows::ApplicationModel::Resources::Core::ResourceManager::Current();
            manager.LoadPriFiles({ priFile });
            auto context = winrt::Windows::ApplicationModel::Resources::Core::ResourceContext::GetForViewIndependentUse().Clone();
            winrt::hstring resourceName{ L"Resources/Click/HelloWorld" };
            winrt::hstring text;
            winrt::hstring keys = L"";
            for (auto map : manager.AllResourceMaps())
            {
                auto mName = map.Key();
                for (auto item : map.Value())
                {
                    auto v = item.Value();
                    auto k = item.Key();
                    keys = keys + L"\n" + mName + L":" + k;
                }
                if (mName == L"5ff74bdd-f98c-4d39-907d-c3eb559f09b8")
                {

                    text = map.Value().GetValue(resourceName, context).ValueAsString();
                }
            }
            CommitButtonText(text);
        }

        bool isAppPackaged = m_telemetryHelper.IsPackagedApp();
        PCWSTR appName = m_telemetryHelper.GetAppName().c_str();
        auto logCaptureOperation{ StoragePickersTelemetry::StoragePickersOperation::Start(isAppPackaged, appName) };

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
