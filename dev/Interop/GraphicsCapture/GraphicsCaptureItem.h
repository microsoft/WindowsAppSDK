// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Microsoft.Windows.Graphics.Capture.GraphicsCaptureItem.g.h"

namespace winrt::Microsoft::Windows::Graphics::Capture::implementation
{
    struct GraphicsCaptureItem
    {
        GraphicsCaptureItem() = default;

        static winrt::Windows::Graphics::Capture::GraphicsCaptureItem TryCreateFromWindowId(winrt::Microsoft::UI::WindowId const& windowId);
        static winrt::Windows::Graphics::Capture::GraphicsCaptureItem TryCreateFromDisplayId(winrt::Microsoft::UI::DisplayId const& displayId);
    };
}
namespace winrt::Microsoft::Windows::Graphics::Capture::factory_implementation
{
    struct GraphicsCaptureItem : GraphicsCaptureItemT<GraphicsCaptureItem, implementation::GraphicsCaptureItem>
    {
    };
}
