// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Microsoft.Windows.Storage.Pickers.FileOpenPicker.g.h"
#include "PickerCommon.h"
#include "StoragePickersTelemetryHelper.h"

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
    struct FileOpenPicker : FileOpenPickerT<FileOpenPicker>
    {
        FileOpenPicker(winrt::Microsoft::UI::WindowId const& windowId);

        winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode ViewMode();
        void ViewMode(winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode const& value);

        hstring SettingsIdentifier();
        void SettingsIdentifier(hstring const& value);

        winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId SuggestedStartLocation();
        void SuggestedStartLocation(winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId const& value);

        winrt::hstring CommitButtonText();
        void CommitButtonText(winrt::hstring const& value);

        winrt::Windows::Foundation::Collections::IVector<hstring> FileTypeFilter();

        winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::Storage::Pickers::PickFileResult> PickSingleFileAsync();
        winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Microsoft::Windows::Storage::Pickers::PickFileResult>> PickMultipleFilesAsync();

    private:
        winrt::Microsoft::UI::WindowId m_windowId{};
        PickerViewMode m_viewMode{ PickerViewMode::List };
        winrt::hstring m_settingsIdentifier{};
        PickerLocationId m_suggestedStartLocation{ PickerLocationId::Unspecified };
        winrt::hstring m_commitButtonText{};
        winrt::Windows::Foundation::Collections::IVector<hstring> m_fileTypeFilter{ winrt::single_threaded_vector<hstring>() };
        StoragePickersTelemetryHelper m_telemetryHelper{};

        void CaptureParameters(StoragePickersImpl::PickerParameters& parameters);
    };
}
namespace winrt::Microsoft::Windows::Storage::Pickers::factory_implementation
{
    struct FileOpenPicker : FileOpenPickerT<FileOpenPicker, implementation::FileOpenPicker>
    {
    };
}
