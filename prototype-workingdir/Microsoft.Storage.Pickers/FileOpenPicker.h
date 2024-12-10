#pragma once
#include "FileOpenPicker.g.h"
#include "PickerCommon.h"

namespace winrt::Microsoft::Storage::Pickers::implementation
{
    struct FileOpenPicker : FileOpenPickerT<FileOpenPicker>
    {
        FileOpenPicker(winrt::Microsoft::UI::WindowId const& windowId);

        winrt::Microsoft::Storage::Pickers::PickerViewMode ViewMode();
        void ViewMode(winrt::Microsoft::Storage::Pickers::PickerViewMode const& value);

        hstring SettingsIdentifier();
        void SettingsIdentifier(hstring const& value);

        winrt::Microsoft::Storage::Pickers::PickerLocationId SuggestedStartLocation();
        void SuggestedStartLocation(winrt::Microsoft::Storage::Pickers::PickerLocationId const& value);

        winrt::hstring CommitButtonText();
        void CommitButtonText(winrt::hstring const& value);

        winrt::Windows::Foundation::Collections::IVector<hstring> FileTypeFilter();

        winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Storage::StorageFile> PickSingleFileAsync();
        winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Windows::Storage::StorageFile>> PickMultipleFilesAsync();

    private:
        winrt::Microsoft::UI::WindowId m_windowId{};
        PickerViewMode m_viewMode{ PickerViewMode::List };
        winrt::hstring m_settingsIdentifier{};
        PickerLocationId m_suggestedStartLocation{ PickerLocationId::Unspecified };
        winrt::hstring m_commitButtonText{};
        winrt::Windows::Foundation::Collections::IVector<hstring> m_fileTypeFilter{ winrt::single_threaded_vector<hstring>() };

        void CaptureParameters(PickerCommon::PickerParameters& parameters);
    };
}
namespace winrt::Microsoft::Storage::Pickers::factory_implementation
{
    struct FileOpenPicker : FileOpenPickerT<FileOpenPicker, implementation::FileOpenPicker>
    {
    };
}
