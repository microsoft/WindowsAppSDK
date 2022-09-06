// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

#include "AppActivationArguments.h"
#include "SharedMemory.h"

namespace winrt::Microsoft::Windows::AppLifecycle::implementation
{
    class RedirectionRequest
    {
    public:
        RedirectionRequest() = default;

        void Create(const std::wstring& name, const winrt::Microsoft::Windows::AppLifecycle::AppActivationArguments& args);
        void Open(const std::wstring& name);

        void MarshalArguments(winrt::Microsoft::Windows::AppLifecycle::AppActivationArguments const& args);
        winrt::Microsoft::Windows::AppLifecycle::AppActivationArguments UnmarshalArguments();

    private:
        std::wstring m_name;
        SharedMemory<uint8_t> m_data;
    };
}
