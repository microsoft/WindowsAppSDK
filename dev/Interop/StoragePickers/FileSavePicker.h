// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Microsoft.Windows.Storage.Pickers.FileSavePicker.g.h"
#include "PickerCommon.h"
#include "StoragePickersTelemetryHelper.h"
#include "FileTypeChoicesMap.h"
#include "FileTypeChoicesMapUnordered.h"

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
    struct FileSavePickerParameters;

    struct FileSavePicker : FileSavePickerT<FileSavePicker>
    {
        FileSavePicker(winrt::Microsoft::UI::WindowId const& windowId);

        winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId SuggestedStartLocation();
        void SuggestedStartLocation(winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId const& value);

        hstring CommitButtonText();
        void CommitButtonText(hstring const& value);

        winrt::Windows::Foundation::Collections::IMap<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>> FileTypeChoices();

        hstring DefaultFileExtension();
        void DefaultFileExtension(hstring const& value);

        hstring SuggestedFolder();
        void SuggestedFolder(hstring const& value);

        hstring SuggestedFileName();
        void SuggestedFileName(hstring const& value);

        winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::Storage::Pickers::PickFileResult> PickSaveFileAsync();

    private:
        winrt::Microsoft::UI::WindowId m_windowId{};
        PickerLocationId m_suggestedStartLocation{ PickerLocationId::Unspecified };
        hstring m_commitButtonText{};
        winrt::Windows::Foundation::Collections::IMap<hstring, winrt::Windows::Foundation::Collections::IVector<hstring>> m_fileTypeChoices{ make<FileTypeChoicesMapUnordered>() };
        hstring m_defaultFileExtension{};
        hstring m_suggestedFolder{};
        hstring m_suggestedFileName{};
        StoragePickersTelemetryHelper m_telemetryHelper{};

        void CaptureParameters(PickerCommon::PickerParameters& parameters);
    };
}
namespace winrt::Microsoft::Windows::Storage::Pickers::factory_implementation
{
    struct FileSavePicker : FileSavePickerT<FileSavePicker, implementation::FileSavePicker>
    {
    };
}
