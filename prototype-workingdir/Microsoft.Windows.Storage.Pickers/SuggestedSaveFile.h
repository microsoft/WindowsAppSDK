// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "SuggestedSaveFile.g.h"
#include "PickerCommon.h"

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
    struct SuggestedSaveFile : SuggestedSaveFileT<SuggestedSaveFile>
    {
        SuggestedSaveFile() = default;

        SuggestedSaveFile(winrt::hstring const& path);

        hstring Path();

        void Path(winrt::hstring const& value);

    private:
        hstring m_path{};
    };
}
namespace winrt::Microsoft::Windows::Storage::Pickers::factory_implementation
{
    struct SuggestedSaveFile : SuggestedSaveFileT<SuggestedSaveFile, implementation::SuggestedSaveFile>
    {
    };
}
