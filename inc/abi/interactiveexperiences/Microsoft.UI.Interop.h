//---------------------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//---------------------------------------------------------------------------

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <winerror.h>
#include <Microsoft.UI.h>

#ifdef BUILD_WINDOWS
namespace ABI::Microsoft::UI 
{
    using WindowId = ::Microsoft::UI::WindowId; 
    using DisplayId = ::Microsoft::UI::DisplayId;
    using IconId = ::Microsoft::UI::IconId;
}
#endif


#ifndef BUILD_WINDOWS
namespace ABI {
#endif
namespace Microsoft {
namespace UI {

typedef HRESULT (STDAPICALLTYPE *PfnGetWindowIdFromWindow)(_In_ HWND hwnd, _Out_ ABI::Microsoft::UI::WindowId* windowId);
typedef HRESULT (STDAPICALLTYPE *PfnGetWindowFromWindowId)(_In_ ABI::Microsoft::UI::WindowId windowId, _Out_ HWND* hwnd);
typedef HRESULT (STDAPICALLTYPE *PfnGetDisplayIdFromMonitor)(_In_ HMONITOR hmonitor, _Out_ ABI::Microsoft::UI::DisplayId* displayId);
typedef HRESULT (STDAPICALLTYPE *PfnGetMonitorFromDisplayId)(_In_ ABI::Microsoft::UI::DisplayId displayId, _Out_ HMONITOR* hmonitor);
typedef HRESULT (STDAPICALLTYPE *PfnGetIconIdFromIcon)(_In_ HICON hicon, _Out_ ABI::Microsoft::UI::IconId* iconId);
typedef HRESULT (STDAPICALLTYPE *PfnGetIconFromIconId)(_In_ ABI::Microsoft::UI::IconId iconId, _Out_ HICON* hicon);

typedef struct _InteropImpl
{
     PfnGetWindowIdFromWindow pfnGetWindowIdFromWindow;
     PfnGetWindowFromWindowId pfnGetWindowFromWindowId;
     PfnGetDisplayIdFromMonitor pfnGetDisplayIdFromMonitor;
     PfnGetMonitorFromDisplayId pfnGetMonitorFromDisplayId;
     PfnGetIconIdFromIcon pfnGetIconIdFromIcon;
     PfnGetIconFromIconId pfnGetIconFromIconId;
} InteropImpl;

#pragma warning(push)
#pragma warning(disable:4505) // linker warning: unreferenced local function has been removed

__declspec(selectany) InteropImpl s_impl {};
__declspec(selectany) HMODULE s_module {};

// Load the FrameworkUdk library if needed and store pointers to the handle conversion functions.
// We need this approach because third-party apps cannot link to the FrameworkUdk directly.
// Note that in unpackaged apps this will only work after a call to MddBootstrapInitialize().
static HRESULT EnsureInteropImplLoaded()
{
    if (::InterlockedCompareExchangePointer(reinterpret_cast<volatile PVOID*>(&s_module), nullptr, nullptr) == nullptr)
    {
        HMODULE hmod = ::GetModuleHandle(TEXT("Microsoft.Internal.FrameworkUdk.dll"));
        if (hmod == nullptr)
        {
            hmod = ::LoadLibrary(TEXT("Microsoft.Internal.FrameworkUdk.dll"));
        }

        if (hmod != nullptr)
        {
            // In case of race conditions, this should be idempotent
            *reinterpret_cast<FARPROC*>(&s_impl.pfnGetWindowIdFromWindow) = ::GetProcAddress(hmod, "Windowing_GetWindowIdFromWindow");
            *reinterpret_cast<FARPROC*>(&s_impl.pfnGetWindowFromWindowId) = ::GetProcAddress(hmod, "Windowing_GetWindowFromWindowId");
            *reinterpret_cast<FARPROC*>(&s_impl.pfnGetDisplayIdFromMonitor) = ::GetProcAddress(hmod, "Windowing_GetDisplayIdFromMonitor");
            *reinterpret_cast<FARPROC*>(&s_impl.pfnGetMonitorFromDisplayId) = ::GetProcAddress(hmod, "Windowing_GetMonitorFromDisplayId");
            *reinterpret_cast<FARPROC*>(&s_impl.pfnGetIconIdFromIcon) = ::GetProcAddress(hmod, "Windowing_GetIconIdFromIcon");
            *reinterpret_cast<FARPROC*>(&s_impl.pfnGetIconFromIconId) = ::GetProcAddress(hmod, "Windowing_GetIconFromIconId");

            if ((s_impl.pfnGetWindowIdFromWindow == nullptr) ||
                (s_impl.pfnGetWindowFromWindowId == nullptr) ||
                (s_impl.pfnGetDisplayIdFromMonitor == nullptr) ||
                (s_impl.pfnGetMonitorFromDisplayId == nullptr) ||
                (s_impl.pfnGetIconIdFromIcon == nullptr) ||
                (s_impl.pfnGetIconFromIconId == nullptr))
                {
                    return HRESULT_FROM_WIN32(::GetLastError());
                }

            // Store our HMODULE if none has been set so far
            ::InterlockedCompareExchangePointer(reinterpret_cast<volatile PVOID*>(&s_module), hmod, nullptr);

            // It is possible that due to race conditions the FrameworkUdk dll ends up loaded multiple
            // times. The expectation is that the FrameworkUdk dll will remain loaded for the lifetime
            // of the process so we won't attempt to mitigate the extra lib refcounts.
        }
    }

    return (::InterlockedCompareExchangePointer(reinterpret_cast<volatile PVOID*>(&s_module), nullptr, nullptr) != nullptr) ? S_OK : HRESULT_FROM_WIN32(::GetLastError());
}

static HRESULT GetWindowFromWindowId(_In_ ::ABI::Microsoft::UI::WindowId windowId, _Out_ HWND* hwnd) noexcept
{
    HRESULT hr = EnsureInteropImplLoaded();
    if (SUCCEEDED(hr))
    {
        hr = s_impl.pfnGetWindowFromWindowId(windowId, hwnd);
    }

    return hr;
}


static HRESULT GetWindowIdFromWindow(_In_ HWND hwnd, _Out_ ::ABI::Microsoft::UI::WindowId* windowId) noexcept
{
    HRESULT hr = EnsureInteropImplLoaded();
    if (SUCCEEDED(hr))
    {
        hr = s_impl.pfnGetWindowIdFromWindow(hwnd, windowId);
    }

    return hr;
}


static HRESULT GetMonitorFromDisplayId(_In_ ::ABI::Microsoft::UI::DisplayId displayId, _Out_ HMONITOR* hmonitor) noexcept
{
    HRESULT hr = EnsureInteropImplLoaded();
    if (SUCCEEDED(hr))
    {
        hr = s_impl.pfnGetMonitorFromDisplayId(displayId, hmonitor);
    }

    return hr;
}


static HRESULT GetDisplayIdFromMonitor(_In_ HMONITOR hmonitor, _Out_ ::ABI::Microsoft::UI::DisplayId* displayId) noexcept
{
    HRESULT hr = EnsureInteropImplLoaded();
    if (SUCCEEDED(hr))
    {
        hr = s_impl.pfnGetDisplayIdFromMonitor(hmonitor, displayId);
    }

    return hr;
}


static HRESULT GetIconFromIconId(_In_ ::ABI::Microsoft::UI::IconId iconId, _Out_ HICON* hicon) noexcept
{
    HRESULT hr = EnsureInteropImplLoaded();
    if (SUCCEEDED(hr))
    {
        hr = s_impl.pfnGetIconFromIconId(iconId, hicon);
    }

    return hr;
}


static HRESULT GetIconIdFromIcon(_In_ HICON hicon, _Out_ ::ABI::Microsoft::UI::IconId* iconId) noexcept
{
    HRESULT hr = EnsureInteropImplLoaded();
    if (SUCCEEDED(hr))
    {
        hr = s_impl.pfnGetIconIdFromIcon(hicon, iconId);
    }

    return hr;
}

#pragma warning(pop)

} // namespace UI
} // namespace Microsoft
#ifndef BUILD_WINDOWS
} // namespace ABI 
#endif
