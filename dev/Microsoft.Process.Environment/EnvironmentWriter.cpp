// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "EnvironmentHelper.h"
#include <EnvironmentWriter.h>
#include <EnvironmentWriter.g.cpp>
#include <EnvironmentVariableChangeTracker.h>
#include <PathChangeTracker.h>

namespace winrt::Microsoft::ProjectReunion::implementation
{

    EnvironmentWriter::EnvironmentWriter(Scope const& scope)
        : m_Scope(scope) { }

    ProjectReunion::EnvironmentWriter EnvironmentWriter::GetForProcess()
    {
        ProjectReunion::EnvironmentWriter environmentWriter{ nullptr };
        environmentWriter = winrt::make<implementation::EnvironmentWriter>(Scope::Process);
        return environmentWriter;
    }

    Microsoft::ProjectReunion::EnvironmentWriter EnvironmentWriter::GetForUser()
    {
        ProjectReunion::EnvironmentWriter environmentWriter{ nullptr };
        environmentWriter = winrt::make<implementation::EnvironmentWriter>(Scope::User);
        return environmentWriter;
    }

    Microsoft::ProjectReunion::EnvironmentWriter EnvironmentWriter::GetForMachine()
    {
        ProjectReunion::EnvironmentWriter environmentWriter{ nullptr };
        environmentWriter = winrt::make<implementation::EnvironmentWriter>(Scope::Machine);
        return environmentWriter;
    }

    bool EnvironmentWriter::IsSupported()
    {
        throw hresult_not_implemented();
    }

    void EnvironmentWriter::SetEnvironmentVariable(hstring const& name, hstring const& value)
    {
        auto setEV = [&, name, value, this]()
        {
            if (m_Scope == Scope::Process)
            {
                BOOL result = FALSE;
                if (!value.empty())
                {
                    result = ::SetEnvironmentVariable(name.c_str(), value.c_str());
                }
                else
                {
                    result = ::SetEnvironmentVariable(name.c_str(), nullptr);
                }

                if (result == TRUE)
                {
                    return S_OK;
                }
                else
                {
                    DWORD lastError = GetLastError();
                    RETURN_HR(HRESULT_FROM_WIN32(lastError));
                }
            }

            // m_Scope should be user or machine here.
            wil::unique_hkey environmentVariableKey = GetRegHKeyForEVUserAndMachineScope(m_Scope, true);

            if (!value.empty())
            {
                THROW_IF_FAILED(HRESULT_FROM_WIN32(RegSetValueEx(
                    environmentVariableKey.get()
                    , name.c_str()
                    , 0
                    , REG_SZ
                    , reinterpret_cast<const BYTE*>(value.c_str())
                    , static_cast<DWORD>((value.size() + 1) * sizeof(wchar_t)))));
            }
            else
            {
                THROW_IF_FAILED(HRESULT_FROM_WIN32(RegDeleteValue(environmentVariableKey.get()
                    , name.c_str())));

                LRESULT broadcastResult = SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE,
                    reinterpret_cast<WPARAM>(nullptr), reinterpret_cast<LPARAM>(L"Environment"),
                    SMTO_NOTIMEOUTIFNOTHUNG | SMTO_BLOCK, 1000, nullptr);

                if (broadcastResult == 0)
                {
                    THROW_HR(HRESULT_FROM_WIN32(GetLastError()));
                }
            }

            return S_OK;
        };

        EnvironmentVariableChangeTracker changeTracker(std::wstring(name), std::wstring(value), m_Scope);

        THROW_IF_FAILED(changeTracker.TrackChange(setEV));
    }

    void EnvironmentWriter::AppendToPath(hstring const& path)
    {
        // Get the existing path because we will append to it.
        std::wstring existingPath = GetPath();

        // Don't append to the path if the addition already exists.
        if (existingPath.find(path) != std::wstring::npos)
        {
            return;
        }

        std::wstring newPath = existingPath.append(path);

        if (newPath.back() != L';')
        {
            newPath += L';';
        }

        auto setPath = [&, newPath, this]()
        {
            if (m_Scope == Scope::Process)
            {
                BOOL result = FALSE;
                result = ::SetEnvironmentVariable(L"Path", newPath.c_str());

                if (result == 0)
                {
                    THROW_HR(HRESULT_FROM_WIN32(GetLastError()));
                }
            }
            else //Scope is either user or machine
            {
                wil::unique_hkey environmentVariableKey = GetRegHKeyForEVUserAndMachineScope(m_Scope, true);

                THROW_IF_FAILED(HRESULT_FROM_WIN32(RegSetValueEx(
                    environmentVariableKey.get()
                    , L"Path"
                    , 0
                    , REG_EXPAND_SZ
                    , reinterpret_cast<const BYTE*>(newPath.c_str())
                    , static_cast<DWORD>((newPath.size() + 1) * sizeof(wchar_t)))));

                LRESULT broadcastResult = SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE,
                    reinterpret_cast<WPARAM>(nullptr), reinterpret_cast<LPARAM>(L"Environment"),
                    SMTO_NOTIMEOUTIFNOTHUNG | SMTO_BLOCK, 1000, nullptr);

                if (broadcastResult == 0)
                {
                    THROW_HR(HRESULT_FROM_WIN32(GetLastError()));
                }
            }

            return S_OK;
        };

        EnvironmentVariableChangeTracker changeTracker(L"Path", std::wstring(newPath), m_Scope);

        THROW_IF_FAILED(changeTracker.TrackChange(setPath));
    }

    void EnvironmentWriter::RemoveFromPath(hstring const& path)
    {
        // A user is only allowed to remove something from the PATH if
        // 1. path exists in PATH
        // 2. path matches a path part exactly (ignoring case)
        std::wstring currentPath = GetPath();
        std::wstring pathPartToFind(path);

        if (pathPartToFind.back() != L';')
        {
            pathPartToFind += L';';
        }

        int left = currentPath.size();
        int right = currentPath.size() - 1;
        bool foundPathPart = false;

        while (!foundPathPart && left >= 0)
        {
            if (left == 0 || currentPath[left - 1] == L';')
            {
                std::wstring pathPart(currentPath, left, right - left);

                if (_wcsnicmp(pathPart.c_str(), pathPartToFind.c_str(), pathPart.size() + 1) == 0)
                {
                    foundPathPart = true;
                }
                else
                {
                    right = left;
                }
            }

            left--;
        }

        // foundPathPart is used to check if we need to track and
        // apply the change.
        currentPath.erase(left + 1, right - left - 1);

        auto removeFromPath = [&, currentPath, this]()
        {
            if (m_Scope == Scope::Process)
            {
                BOOL result = FALSE;
                result = ::SetEnvironmentVariable(L"Path", currentPath.c_str());

                if (result == 0)
                {
                    THROW_HR(HRESULT_FROM_WIN32(GetLastError()));
                }
            }
            else //Scope is either user or machine
            {
                wil::unique_hkey environmentVariableKey = GetRegHKeyForEVUserAndMachineScope(m_Scope, true);

                THROW_IF_FAILED(HRESULT_FROM_WIN32(RegSetValueEx(
                    environmentVariableKey.get()
                    , L"Path"
                    , 0
                    , REG_EXPAND_SZ
                    , reinterpret_cast<const BYTE*>(currentPath.c_str())
                    , static_cast<DWORD>((currentPath.size() + 1) * sizeof(wchar_t)))));

                LRESULT broadcastResult = SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE,
                    reinterpret_cast<WPARAM>(nullptr), reinterpret_cast<LPARAM>(L"Environment"),
                    SMTO_NOTIMEOUTIFNOTHUNG | SMTO_BLOCK, 1000, nullptr);

                if (broadcastResult == 0)
                {
                    THROW_HR(HRESULT_FROM_WIN32(GetLastError()));
                }
            }

            return S_OK;
        };

        if (foundPathPart)
        {
            EnvironmentVariableChangeTracker changeTracker(L"Path", std::wstring(currentPath), m_Scope);

            THROW_IF_FAILED(changeTracker.TrackChange(removeFromPath));
        }
    }

    void EnvironmentWriter::AddExecutableFileExtension(hstring const& pathExt)
    {
        throw hresult_not_implemented();
    }

    void EnvironmentWriter::RemoveExecutableFileExtension(hstring const& pathExt)
    {
        throw hresult_not_implemented();
    }

    std::wstring EnvironmentWriter::GetPath()
    {
        std::wstring path;
        if (m_Scope == Scope::Process)
        {
            path = GetProcessEnvironmentVariable(L"Path");
        }
        else
        {
            wil::unique_hkey environmentVariableKey = GetRegHKeyForEVUserAndMachineScope(m_Scope);

            DWORD sizeOfEnvironmentValue;

            // See how big we need the buffer to be
            LSTATUS queryResult = RegQueryValueEx(environmentVariableKey.get(), L"Path", 0, nullptr, nullptr, &sizeOfEnvironmentValue);

            if (queryResult == ERROR_FILE_NOT_FOUND)
            {
                path = L"";
            }

            if (queryResult != ERROR_SUCCESS)
            {
                THROW_HR(HRESULT_FROM_WIN32((queryResult)));
            }

            std::unique_ptr<wchar_t[]> environmentValue(new wchar_t[sizeOfEnvironmentValue]);
            THROW_IF_FAILED(HRESULT_FROM_WIN32((RegQueryValueEx(environmentVariableKey.get(), L"Path", 0, nullptr, (LPBYTE)environmentValue.get(), &sizeOfEnvironmentValue))));

            path = std::wstring(environmentValue.get());
        }

        if (path.back() != L';')
        {
            path += L';';
        }

        return path;
    }
}
