// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "GraphicsCaptureItem.h"
#include "Microsoft.Windows.Graphics.Capture.GraphicsCaptureItem.g.cpp"
#include <winrt/Windows.Graphics.Capture.h>
#include <windows.graphics.capture.interop.h>

namespace winrt::Microsoft::Windows::Graphics::Capture::implementation
{
    winrt::Windows::Graphics::Capture::GraphicsCaptureItem GraphicsCaptureItem::TryCreateFromWindowId(
        winrt::Microsoft::UI::WindowId const& windowId)
    {
        auto hwnd{ reinterpret_cast<HWND>(windowId.Value) };
        if (!hwnd)
        {
            return nullptr;
        }

        auto factory{ winrt::get_activation_factory<winrt::Windows::Graphics::Capture::GraphicsCaptureItem, IGraphicsCaptureItemInterop>() };
        winrt::Windows::Graphics::Capture::GraphicsCaptureItem item{ nullptr };
        if (FAILED(factory->CreateForWindow(hwnd, winrt::guid_of<winrt::Windows::Graphics::Capture::GraphicsCaptureItem>(), winrt::put_abi(item))))
        {
            return nullptr;
        }
        return item;
    }

    winrt::Windows::Graphics::Capture::GraphicsCaptureItem GraphicsCaptureItem::TryCreateFromDisplayId(
        winrt::Microsoft::UI::DisplayId const& displayId)
    {
        auto hmonitor{ reinterpret_cast<HMONITOR>(displayId.Value) };
        if (!hmonitor)
        {
            return nullptr;
        }

        auto factory{ winrt::get_activation_factory<winrt::Windows::Graphics::Capture::GraphicsCaptureItem, IGraphicsCaptureItemInterop>() };
        winrt::Windows::Graphics::Capture::GraphicsCaptureItem item{ nullptr };
        if (FAILED(factory->CreateForMonitor(hmonitor, winrt::guid_of<winrt::Windows::Graphics::Capture::GraphicsCaptureItem>(), winrt::put_abi(item))))
        {
            return nullptr;
        }
        return item;
    }
}
