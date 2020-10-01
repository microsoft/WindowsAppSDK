// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include "FileType.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    void FileType::Load()
    {
        std::wstring key_path{ get_association_path(m_extension.c_str()) };
        wil::unique_hkey key;

        auto error = ::RegOpenKeyEx(HKEY_CURRENT_USER, key_path.c_str(), 0, KEY_READ | KEY_QUERY_VALUE,
            key.put());

        // Nothing to load.
        if (error == ERROR_FILE_NOT_FOUND)
        {
            return;
        }

        if (error != ERROR_SUCCESS)
        {
            THROW_IF_WIN32_ERROR(error);
        }

        DWORD size = 0;
        THROW_IF_WIN32_ERROR(::RegQueryValueEx(key.get(), nullptr, nullptr, nullptr, nullptr,
            &size));

        m_defaultProgId.resize(size / sizeof(wchar_t));
        THROW_IF_WIN32_ERROR(::RegQueryValueEx(key.get(), nullptr, nullptr, nullptr,
            reinterpret_cast<LPBYTE>(m_defaultProgId.data()), &size));
    }

    void FileType::Save()
    {
        std::wstring key_path{ get_association_path(m_extension.c_str()) };
        wil::unique_hkey key;

        THROW_IF_WIN32_ERROR(::RegCreateKeyEx(HKEY_CURRENT_USER, key_path.c_str(), 0, nullptr, 0,
            KEY_WRITE, nullptr, key.put(), nullptr));

        THROW_IF_WIN32_ERROR(::RegSetValueEx(key.get(), nullptr, 0, REG_SZ,
            reinterpret_cast<BYTE const*>(m_defaultProgId.c_str()),
            static_cast<uint32_t>((m_defaultProgId.size() + 1) * sizeof(wchar_t))));
    }
}
