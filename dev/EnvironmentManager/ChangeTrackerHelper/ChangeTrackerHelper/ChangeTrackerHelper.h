#pragma once
#include <windows.h>
#include <appmodel.h>

enum AreChangesTracked
{
    YES,
    NO,
    NOT_CHECKED
};

AreChangesTracked m_AreChangesTracked{NOT_CHECKED};

inline bool DoesUnVirtualizedKeyExist()
{
    std::filesystem::path subKey = std::filesystem::path{ L"Software\\ChangeTracker" }

}

inline bool WillChangesBeTracked()
{
    if (m_AreChangesTracked == NOT_CHECKED)
    {
       // If we do need to track the changes get the Package Full Name
        WCHAR packageFullName[PACKAGE_FULL_NAME_MAX_LENGTH + 1]{};
        UINT32 packageFullNameLength{ static_cast<UINT32>(ARRAYSIZE(packageFullName)) };
        const long getPackageFullNameRC{ ::GetCurrentPackageFullName(&packageFullNameLength, packageFullName) };

        if (scope == EnvironmentManager::Scope::Process || getPackageFullNameRC == APPMODEL_ERROR_NO_PACKAGE)
        {
            m_ShouldTrackChange = false;
        }
        else if (getPackageFullNameRC == ERROR_SUCCESS)
        {
            m_PackageFullName = std::wstring(packageFullName);
            m_ShouldTrackChange = true;
        }
        else
        {
            THROW_WIN32(getPackageFullNameRC);
        }
    }

    if (m_AreChangesTracked == YES)
    {
        return true;
    }
    else if (m_AreChangesTracked == NO)
    {
        return false;
    }
    else
    {
        FAIL_FAST_HR_MSG(E_INVALIDARG, L"m_AreChangesTracked wasn't YES or NO");
    }
}
