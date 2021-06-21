#pragma once
#include <string>
#include <functional>
#include <windows.h>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    class IChangeTracker {
    public:
        virtual HRESULT TrackChange(std::function<HRESULT(void)> callBack) = 0;

        bool m_ShouldTrackChange{ false };
        const std::wstring c_userEvRegLocation{ L"Environment" };
        const std::wstring c_machineEvRegLocation{ L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment" };
        std::wstring m_PackageFullName;

        enum PathOperation
        {
            Append,
            Remove
        };

    private:
        virtual std::wstring KeyName() = 0;

    };
}
