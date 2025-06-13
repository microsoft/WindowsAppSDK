// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "SuggestedSaveFile.h"
#include "Microsoft.Windows.Storage.Pickers.SuggestedSaveFile.g.cpp"

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
    SuggestedSaveFile::SuggestedSaveFile(hstring const& path) :
        m_path(path)
    {
    }

    hstring SuggestedSaveFile::Path()
    {
        return m_path;
    }

    void SuggestedSaveFile::Path(hstring const& value)
    {
        m_path = value;
    }
}
