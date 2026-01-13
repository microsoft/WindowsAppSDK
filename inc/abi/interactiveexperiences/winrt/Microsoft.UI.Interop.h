//----------------------------------------------------------------------------
// Copyright (c) Microsoft Corporation.  All rights reserved.
//----------------------------------------------------------------------------

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <winrt/Microsoft.UI.h>

namespace ABI::Microsoft::UI 
{
    using WindowId = winrt::Microsoft::UI::WindowId;
    using DisplayId = winrt::Microsoft::UI::DisplayId;
    using IconId = winrt::Microsoft::UI::IconId;
}


namespace winrt::Microsoft::UI 
{

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
static void EnsureInteropImplLoaded()
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

            winrt::check_bool(
                (s_impl.pfnGetWindowIdFromWindow != nullptr) &&
                (s_impl.pfnGetWindowFromWindowId != nullptr) &&
                (s_impl.pfnGetDisplayIdFromMonitor != nullptr) &&
                (s_impl.pfnGetMonitorFromDisplayId != nullptr) &&
                (s_impl.pfnGetIconIdFromIcon != nullptr) &&
                (s_impl.pfnGetIconFromIconId != nullptr));

            // Store our HMODULE if none has been set so far
            ::InterlockedCompareExchangePointer(reinterpret_cast<volatile PVOID*>(&s_module), hmod, nullptr);

            // It is possible that due to race conditions the FrameworkUdk dll ends up loaded multiple
            // times. The expectation is that the FrameworkUdk dll will remain loaded for the lifetime
            // of the process so we won't attempt to mitigate the extra lib refcounts.
        }
    }

    winrt::check_bool(::InterlockedCompareExchangePointer(reinterpret_cast<volatile PVOID*>(&s_module), nullptr, nullptr) != nullptr);
}


static winrt::Microsoft::UI::WindowId GetWindowIdFromWindow(_In_ const HWND& hwnd) 
{
    ::ABI::Microsoft::UI::WindowId abiWindowId = {};
    EnsureInteropImplLoaded();
    winrt::check_hresult(s_impl.pfnGetWindowIdFromWindow(hwnd, &abiWindowId));
    winrt::Microsoft::UI::WindowId winrtWindowId { abiWindowId.Value };
    return winrtWindowId;
}


static HWND GetWindowFromWindowId(_In_ const winrt::Microsoft::UI::WindowId& windowId) 
{
    HWND hwnd = nullptr;
    EnsureInteropImplLoaded();
    ::ABI::Microsoft::UI::WindowId abiWindowId { windowId.Value };
    winrt::check_hresult(s_impl.pfnGetWindowFromWindowId(abiWindowId, &hwnd));
    return hwnd;
}


static winrt::Microsoft::UI::DisplayId GetDisplayIdFromMonitor(_In_ const HMONITOR& hmonitor) 
{
    ::ABI::Microsoft::UI::DisplayId abiDisplayId = {};
    EnsureInteropImplLoaded();
    winrt::check_hresult(s_impl.pfnGetDisplayIdFromMonitor(hmonitor, &abiDisplayId));
    winrt::Microsoft::UI::DisplayId winrtDisplayId { abiDisplayId.Value };
    return winrtDisplayId;
}


static HMONITOR GetMonitorFromDisplayId(_In_ const winrt::Microsoft::UI::DisplayId& displayId) 
{
    HMONITOR hmonitor = nullptr;
    EnsureInteropImplLoaded();
    ::ABI::Microsoft::UI::DisplayId abiDisplayId { displayId.Value };
    winrt::check_hresult(s_impl.pfnGetMonitorFromDisplayId(abiDisplayId, &hmonitor));
    return hmonitor;
}


static winrt::Microsoft::UI::IconId GetIconIdFromIcon(_In_ const HICON& hicon) 
{
    ::ABI::Microsoft::UI::IconId abiIconId = {};
    EnsureInteropImplLoaded();
    winrt::check_hresult(s_impl.pfnGetIconIdFromIcon(hicon, &abiIconId));
    winrt::Microsoft::UI::IconId winrtIconId { abiIconId.Value };
    return winrtIconId;
}


static HICON GetIconFromIconId(_In_ const winrt::Microsoft::UI::IconId& iconId) 
{
    HICON hicon = nullptr;
    EnsureInteropImplLoaded();
    ::ABI::Microsoft::UI::IconId abiIconId { iconId.Value };
    winrt::check_hresult(s_impl.pfnGetIconFromIconId(abiIconId, &hicon));
    return hicon;
}

#pragma warning(pop)

} // namespace winrt::Microsoft::UI
