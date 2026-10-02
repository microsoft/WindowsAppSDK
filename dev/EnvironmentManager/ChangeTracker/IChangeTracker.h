// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once
#include <string>
#include <functional>
#include <windows.h>

namespace winrt::Microsoft::Windows::System::implementation
{
    class IChangeTracker {
    public:
        virtual HRESULT TrackChange(std::function<HRESULT(void)> callBack) = 0;

        bool m_ShouldTrackChange{};
        static inline const std::wstring c_UserEvRegLocation{ L"Environment" };
        static inline const std::wstring c_MachineEvRegLocation{ L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment" };
        std::wstring m_PackageFullName;

        enum PathOperation
        {
            Append,
            Remove
        };

        virtual PCWSTR KeyName() const = 0;

    private:

    };
}
