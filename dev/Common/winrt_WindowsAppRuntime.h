// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#ifndef __WINRT_WINDOWS_APP_RUNTIME_H
#define __WINRT_WINDOWS_APP_RUNTIME_H

namespace winrt
{
    // Per https://docs.microsoft.com/windows/uwp/cpp-and-winrt-apis/interop-winrt-abi#convert_from_abi-function
    template <typename T>
    T convert_from_abi(::IUnknown* from)
    {
        T to{ nullptr }; // `T` is a projected type.

        winrt::check_hresult(from->QueryInterface(winrt::guid_of<T>(),
            winrt::put_abi(to)));

        return to;
    }

    template <typename T>
    T convert_from_abi(::IInspectable* from)
    {
        T to{ nullptr }; // `T` is a projected type.

        winrt::check_hresult(from->QueryInterface(winrt::guid_of<T>(),
            winrt::put_abi(to)));

        return to;
    }
}

#endif  // __WINRT_WINDOWS_APP_RUNTIME_H