// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "SuggestedSaveFile.g.h"  // Microsoft.Windows.Storage.Pickers.

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
    struct SuggestedSaveFile : SuggestedSaveFileT<SuggestedSaveFile>
    {
        SuggestedSaveFile(winrt::hstring const& path);

        winrt::hstring Path();

    private:
        winrt::hstring m_path;
    };
}

namespace winrt::Microsoft::Windows::Storage::Pickers::factory_implementation
{
    struct SuggestedSaveFile : SuggestedSaveFileT<SuggestedSaveFile, implementation::SuggestedSaveFile>
    {
    };
}
