// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Microsoft.Windows.Storage.Pickers.FolderPicker.g.h"
#include "PickerCommon.h"
#include "StoragePickersTelemetryHelper.h"

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
    struct FolderPicker : FolderPickerT<FolderPicker>
    {
        FolderPicker(winrt::Microsoft::UI::WindowId const& windowId);

        winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode ViewMode();
        void ViewMode(winrt::Microsoft::Windows::Storage::Pickers::PickerViewMode const& value);

        winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId SuggestedStartLocation();
        void SuggestedStartLocation(winrt::Microsoft::Windows::Storage::Pickers::PickerLocationId const& value);

        hstring CommitButtonText();
        void CommitButtonText(hstring const& value);

        hstring SuggestedFolder();
        void SuggestedFolder(hstring const& value);

        hstring SuggestedStartFolder();
        void SuggestedStartFolder(hstring const& value);

        winrt::Windows::Foundation::IAsyncOperation<winrt::Microsoft::Windows::Storage::Pickers::PickFolderResult> PickSingleFolderAsync();

    private:
        winrt::Microsoft::UI::WindowId m_windowId{};

        PickerViewMode m_viewMode{ PickerViewMode::List };
        PickerLocationId m_suggestedStartLocation{ PickerLocationId::Unspecified };
        hstring m_commitButtonText{};
        hstring m_suggestedFolder{};
        hstring m_suggestedStartFolder{};
        StoragePickersTelemetryHelper m_telemetryHelper{};

        void CaptureParameters(PickerCommon::PickerParameters& parameters);
    };
}
namespace winrt::Microsoft::Windows::Storage::Pickers::factory_implementation
{
    struct FolderPicker : FolderPickerT<FolderPicker, implementation::FolderPicker>
    {
    };
}
