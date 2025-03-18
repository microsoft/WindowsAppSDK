// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Microsoft.Windows.Storage.Pickers.PickFolderResult.g.h"
#include "PickerCommon.h"

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
    struct PickFolderResult : PickFolderResultT<PickFolderResult>
    {
        PickFolderResult() = default;

        PickFolderResult(winrt::hstring const& path);

        hstring Path();

    private:
        hstring m_path{};
    };
}
