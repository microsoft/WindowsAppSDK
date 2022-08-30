// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#include <pch.h>
#include "PathChangeTracker.h"


namespace winrt::Microsoft::Windows::System::implementation
{
    PathChangeTracker::PathChangeTracker(const std::wstring& pathPart, EnvironmentManager::Scope scope, PathOperation operation)
    {
        THROW_HR_IF(E_INVALIDARG, pathPart.empty());

        // Check if we need to track the changes.
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

        m_Scope = scope;
        m_PathPart = pathPart;
        m_Operation = operation;
    }

    PCWSTR PathChangeTracker::KeyName() const
    {
        return L"PATH";
    }

    HRESULT PathChangeTracker::TrackChange(std::function<HRESULT(void)> callback)
    {
        if (m_ShouldTrackChange)
        {
            if (m_PathPart.back() != L';')
            {
                m_PathPart += L';';
            }

            wil::unique_hkey regLocationToWriteChange{ GetKeyForTrackingChange(nullptr) };

            if (m_Operation == PathOperation::Append)
            {
                std::wstring previouslyAppendedValues{ GetValueFromTracking(std::wstring(L"AppendedValues"))};

                previouslyAppendedValues += m_PathPart;

                RETURN_IF_WIN32_ERROR(RegSetValueEx(regLocationToWriteChange.get(),
                    L"AppendedValues", 0, REG_SZ,
                    reinterpret_cast<const BYTE*>(previouslyAppendedValues.c_str()),
                    static_cast<DWORD>((previouslyAppendedValues.size() + 1) * sizeof(wchar_t))));
            }
            else
            {
                // Find the index of the path part to remove.
                // The index allows the DEH best-effort to add the
                // removed value at its correct location.
                std::wstring existingPath{ QueryEvFromRegistry(L"Path", GetKeyForEnvironmentVariable().get())};

                int index{ -1 };

                PWSTR tokenizationState;
                PWSTR token{ wcstok_s(existingPath.data(), L";", &tokenizationState) };
                bool foundPathPart{};
                while (token != nullptr && !foundPathPart)
                {
                    std::wstring pathPartToken{ token };

                    pathPartToken += L';';

                    if (CompareStringOrdinal(m_PathPart.c_str(), -1,
                        pathPartToken.c_str(), -1,
                        TRUE) == CSTR_EQUAL)
                    {
                        foundPathPart = true;
                    }

                    index++;
                    token = wcstok_s(NULL, L";", &tokenizationState);
                }


                if (foundPathPart)
                {
                    std::wstring previouslyRemovedValues{ GetValueFromTracking(std::wstring(L"RemovedValues")) };

                    std::wstring removalInformation{ m_PathPart };
                    removalInformation += L",";
                    removalInformation += std::to_wstring(index);
                    removalInformation += L"\t";

                    previouslyRemovedValues += removalInformation;

                    RETURN_IF_WIN32_ERROR(RegSetValueEx(regLocationToWriteChange.get(),
                        L"RemovedValues", 0, REG_SZ,
                        reinterpret_cast<const BYTE*>(previouslyRemovedValues.c_str()),
                        static_cast<DWORD>((previouslyRemovedValues.size() + 1) * sizeof(wchar_t))));
                }
            }
        }

        return callback();
    }
}
