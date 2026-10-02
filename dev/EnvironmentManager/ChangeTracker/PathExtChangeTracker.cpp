// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#include <pch.h>
#include "PathExtChangeTracker.h"


namespace winrt::Microsoft::Windows::System::implementation
{
    PathExtChangeTracker::PathExtChangeTracker(const std::wstring& pathExtPart, EnvironmentManager::Scope scope, PathOperation operation)
    {
        THROW_HR_IF(E_INVALIDARG, pathExtPart.empty());

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
        m_PathExtPart = pathExtPart;
        m_Operation = operation;
    }

    PCWSTR PathExtChangeTracker::KeyName() const
    {
        return L"PATHEXT";
    }

    HRESULT PathExtChangeTracker::TrackChange(std::function<HRESULT(void)> callback)
    {
        if (m_ShouldTrackChange)
        {
            if (m_PathExtPart.back() != L';')
            {
                m_PathExtPart += L';';
            }

            wil::unique_hkey regLocationToWriteChange{ GetKeyForTrackingChange(nullptr) };

            if (m_Operation == PathOperation::Append)
            {
                std::wstring previouslyAppendedValues{ GetValueFromTracking(std::wstring(L"AppendedValues")) };

                previouslyAppendedValues += m_PathExtPart;

                RETURN_IF_FAILED(HRESULT_FROM_WIN32(RegSetValueEx(regLocationToWriteChange.get(),
                    L"AppendedValues", 0, REG_SZ,
                    reinterpret_cast<const BYTE*>(previouslyAppendedValues.c_str()),
                    static_cast<DWORD>((previouslyAppendedValues.size() + 1) * sizeof(wchar_t)))));
            }
            else
            {
                // Find the index of the path part to remove.
                // The index allows the DEH best-effort to add the
                // removed value at its correct location.
                std::wstring existingPathExt{ QueryEvFromRegistry(L"PathExt", GetKeyForEnvironmentVariable().get()) };

                int index{ -1 };

                PWSTR tokenizationState;
                PWSTR token{ wcstok_s(existingPathExt.data(), L";", &tokenizationState) };
                bool foundPathExtPart{};
                while (token != nullptr && !foundPathExtPart)
                {
                    std::wstring pathExtPartToken{ token };

                    pathExtPartToken += L';';

                    if (CompareStringOrdinal(m_PathExtPart.c_str(), -1,
                        pathExtPartToken.c_str(), -1,
                        TRUE) == CSTR_EQUAL)
                    {
                        foundPathExtPart = true;
                    }

                    index++;
                    token = wcstok_s(NULL, L";", &tokenizationState);
                }

                if (foundPathExtPart)
                {
                    std::wstring previouslyRemovedValues{ GetValueFromTracking(std::wstring(L"RemovedValues")) };

                    std::wstring removalInformation{ m_PathExtPart };
                    removalInformation += L",";
                    removalInformation += std::to_wstring(index);
                    removalInformation += L"\t";

                    previouslyRemovedValues += removalInformation;

                    RETURN_IF_FAILED(HRESULT_FROM_WIN32(RegSetValueEx(regLocationToWriteChange.get(),
                        L"RemovedValues", 0, REG_SZ,
                        reinterpret_cast<const BYTE*>(previouslyRemovedValues.c_str()),
                        static_cast<DWORD>((previouslyRemovedValues.size() + 1) * sizeof(wchar_t)))));
                }
            }
        }

        return callback();
    }
}
