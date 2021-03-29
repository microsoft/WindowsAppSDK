#pragma once
#include <string>
#include <functional>
#include <windows.h>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    class IChangeTracker {
    public:
        virtual HRESULT TrackChange(std::function<HRESULT(void)> callBack) = 0;

        bool m_ShouldTrackChange = false;
        std::wstring m_PackageFullName;

    private:
        virtual std::wstring KeyName() = 0;

    };
}
