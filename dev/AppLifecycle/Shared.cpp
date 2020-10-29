// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include "Shared.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    std::wstring GetFullIdentityString()
    {
        std::wstring identityString;
        WCHAR idNameBuffer[PACKAGE_FULL_NAME_MAX_LENGTH];
        UINT32 idNameBufferLen = ARRAYSIZE(idNameBuffer);
        if (::GetCurrentPackageFullName(&idNameBufferLen, idNameBuffer) == ERROR_SUCCESS)
        {
            identityString = idNameBuffer;
        }

        return identityString;
    }

    bool HasIdentity()
    {
        return !(GetFullIdentityString()).empty();
    }

    std::wstring GetModulePath()
    {
        std::wstring path(100, L'?');
        uint32_t path_size{};
        DWORD actual_size{};

        do
        {
            path_size = static_cast<uint32_t>(path.size());
            actual_size = ::GetModuleFileName(nullptr, path.data(), path_size);

            if (actual_size + 1 > path_size)
            {
                path.resize(path_size * 2, L'?');
            }
        } while (actual_size + 1 > path_size);

        path.resize(actual_size);
        return path;
    }

    std::wstring CreateAssocKeyPath(PCWSTR assocName)
    {
        std::wstring path{ LR"(SOFTWARE\Classes\)" };
        path += assocName;
        return path;
    }

    void RegisterProtocol(PCWSTR scheme, PCWSTR displayName, _In_opt_ const GUID* delegateExecute)
    {
        std::wstring key_path{ CreateAssocKeyPath(scheme) };
        wil::unique_hkey key;

        THROW_IF_WIN32_ERROR(::RegCreateKeyEx(HKEY_CURRENT_USER, key_path.c_str(), 0, nullptr, 0,
            KEY_WRITE, nullptr, key.put(), nullptr));

        std::wstring defaultValue{ L"URL:" };
        defaultValue += displayName;
        THROW_IF_WIN32_ERROR(::RegSetValueEx(key.get(), nullptr, 0, REG_SZ,
            reinterpret_cast<BYTE const*>(defaultValue.c_str()),
            static_cast<uint32_t>((defaultValue.size() + 1) * sizeof(wchar_t))));

        std::wstring urlProtocolValue{ L"" };
        defaultValue += displayName;
        THROW_IF_WIN32_ERROR(::RegSetValueEx(key.get(), L"URL Protocol", 0, REG_SZ,
            reinterpret_cast<BYTE const*>(urlProtocolValue.c_str()),
            static_cast<uint32_t>((urlProtocolValue.size() + 1) * sizeof(wchar_t))));

        key_path += LR"(\shell\open\command)";
        key.reset();
        THROW_IF_WIN32_ERROR(::RegCreateKeyEx(HKEY_CURRENT_USER, key_path.c_str(), 0, nullptr, 0,
            KEY_WRITE, nullptr, key.put(), nullptr));

        auto command = GetModulePath();
        command += L" ----" MS_PROTOCOL_ARG_STR ":%1";
        THROW_IF_WIN32_ERROR(::RegSetValueEx(key.get(), nullptr, 0, REG_SZ,
            reinterpret_cast<BYTE const*>(command.c_str()),
            static_cast<uint32_t>((command.size() + 1) * sizeof(wchar_t))));

        if (delegateExecute)
        {
            std::wstring delegateClsid{ LR"({????????-????-????-????-????????????})" };
            ::StringFromGUID2(*delegateExecute, delegateClsid.data(), 39);

            THROW_IF_WIN32_ERROR(::RegSetValueEx(key.get(), L"DelegateExecute", 0, REG_SZ,
                reinterpret_cast<BYTE const*>(delegateClsid.c_str()),
                static_cast<uint32_t>((delegateClsid.size() + 1) * sizeof(wchar_t))));
        }
    }

    void UnregisterProtocol(PCWSTR scheme)
    {
        std::wstring key_path{ CreateAssocKeyPath(scheme) };
        ::RegDeleteTree(HKEY_CURRENT_USER, key_path.c_str());
    }
}
