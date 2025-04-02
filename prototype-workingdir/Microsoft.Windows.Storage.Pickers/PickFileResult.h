// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "PickFileResult.g.h"
#include "PickerCommon.h"

namespace winrt::Microsoft::Windows::Storage::Pickers::implementation
{
    struct PickFileResult : PickFileResultT<PickFileResult>
    {
        PickFileResult() = default;

        PickFileResult(winrt::hstring const& path);

        hstring Path();

        private:
            hstring m_path{};
    };
}
