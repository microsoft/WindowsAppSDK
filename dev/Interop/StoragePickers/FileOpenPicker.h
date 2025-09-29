// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Microsoft.Windows.Storage.Pickers.FileOpenPicker.g.h"
#include "PickerCommon.h"
#include "StoragePickersTelemetryHelper.h"
#include <winrt/Windows.Foundation.Collections.h>
#include "FileTypeChoicesMap.h"
#include "FileTypeFilterVector.h"

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
    struct FileOpenPicker : FileOpenPickerT<FileOpenPicker>
    {
        FileOpenPicker(winrt::Microsoft::UI::WindowId const& windowId);

        winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode ViewMode();
        void ViewMode(winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode const& value);

        winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId SuggestedStartLocation();
        void SuggestedStartLocation(winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId const& value);

        winrt::hstring CommitButtonText();
        void CommitButtonText(winrt::hstring const& value);

        winrt::Windows::Foundation::Collections::IVector<winrt::hstring> FileTypeFilter();
        winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::Windows::Foundation::Collections::IVector<winrt::hstring>> FileTypeChoices();

        winrt::hstring SuggestedFolder();
        void SuggestedFolder(winrt::hstring const& value);

        winrt::hstring SuggestedStartFolder();
        void SuggestedStartFolder(winrt::hstring const& value);

        winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::Storage::Pickers::PickFileResult> PickSingleFileAsync();
        winrt::Windows::Foundation::IAsyncOperation<winrt::Windows::Foundation::Collections::IVectorView<winrt::Microsoft::Windows::Storage::Pickers::PickFileResult>> PickMultipleFilesAsync();

    private:
        winrt::Microsoft::UI::WindowId m_windowId{};
        PickerViewMode m_viewMode{ PickerViewMode::List };
        PickerLocationId m_suggestedStartLocation{ PickerLocationId::Unspecified };
        winrt::hstring m_commitButtonText{};

        winrt::Windows::Foundation::Collections::IVector<winrt::hstring> m_fileTypeFilter{ make<FileTypeFilterVector>() };
        winrt::Windows::Foundation::Collections::IMap<winrt::hstring, winrt::Windows::Foundation::Collections::IVector<winrt::hstring>> m_fileTypeChoices{ make<FileTypeChoicesMap>(false) };

        winrt::hstring m_suggestedFolder{};
        winrt::hstring m_suggestedStartFolder{};

        StoragePickersTelemetryHelper m_telemetryHelper{};

        void CaptureParameters(PickerCommon::PickerParameters& parameters);
    };
}
namespace winrt::Microsoft::Windows::Storage::Pickers::factory_implementation
{
    struct FileOpenPicker : FileOpenPickerT<FileOpenPicker, implementation::FileOpenPicker>
    {
    };
}
