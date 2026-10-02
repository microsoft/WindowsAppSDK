// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "PickFileResult.h"
#include "Microsoft.Windows.Storage.Pickers.PickFileResult.g.cpp"

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
    PickFileResult::PickFileResult(hstring const& path) : 
        m_path(path)
    {
    }

    hstring PickFileResult::Path()
    {
        return m_path;
    }
}
