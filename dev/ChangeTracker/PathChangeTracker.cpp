#include <pch.h>
#include <PathChangeTracker.h>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    PathChangeTracker::PathChangeTracker(std::wstring const& pathPart, EnvironmentManager::Scope scope)
    {
        MessageBoxEx(NULL, L"In constructor", L"In constructor", 0, 0);
        if (pathPart.empty())
        {
            THROW_HR(E_INVALIDARG);
        }

        // Check if we need to track the changes.
       // If we do need to track the changes get the Package Full Name
        UINT32 sizeOfBuffer{};
        long fullNameResult = ::GetCurrentPackageFullName(&sizeOfBuffer, nullptr);
        if (fullNameResult == APPMODEL_ERROR_NO_PACKAGE)
        {
            m_ShouldTrackChange = false;
        }
        else if (fullNameResult == ERROR_INSUFFICIENT_BUFFER)
        {
            std::unique_ptr<WCHAR> packageFullName(new WCHAR[sizeOfBuffer]);

            LONG getNameResult = ::GetCurrentPackageFullName(&sizeOfBuffer, packageFullName.get());
            THROW_IF_FAILED(HRESULT_FROM_WIN32(getNameResult));
            m_PackageFullName = std::wstring(packageFullName.get());
            m_ShouldTrackChange = true;
        }
        else
        {
            THROW_HR(HRESULT_FROM_WIN32(fullNameResult));
        }

        m_Scope = scope;
        m_PathPart = pathPart;
    }

    std::wstring PathChangeTracker::KeyName()
    {
        return L"Path";
    }

    HRESULT PathChangeTracker::TrackChange(std::function<HRESULT(void)> callback)
    {
        if (m_ShouldTrackChange)
        {
            std::wstring pathOrPathExtChanges = GetChangesFromRegistry();

            std::wstring newPathChanges = pathOrPathExtChanges.append(m_PathPart.c_str()).append(L";");

            wil::unique_hkey regLocationToWriteChange = GetKeyForTrackingChange();
            RETURN_IF_FAILED(HRESULT_FROM_WIN32(RegSetValueEx(regLocationToWriteChange.get()
                , L"AppendedValues"
                , 0
                , REG_SZ
                , reinterpret_cast<const BYTE*>(newPathChanges.c_str()), (newPathChanges.size() + 1) * sizeof(wchar_t))));
        }

        return S_OK;
    }
}
