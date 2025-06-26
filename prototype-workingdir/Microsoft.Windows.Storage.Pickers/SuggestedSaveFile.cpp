// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "SuggestedSaveFile.h"
#include "SuggestedSaveFile.g.cpp"

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
    SuggestedSaveFile::SuggestedSaveFile(winrt::hstring const& path)
        : m_path(path)
    {
        // Validate path is not empty
        if (path.empty())
        {
            throw winrt::hresult_invalid_argument(L"Path cannot be empty");
        }
    }

    winrt::hstring SuggestedSaveFile::Path()
    {
        return m_path;
    }
}
