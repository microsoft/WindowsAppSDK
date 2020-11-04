// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include "Shared.h"

namespace winrt::Microsoft::ApplicationModel::Activation::implementation
{
    std::wstring GetFullIdentityString()
    {
        std::wstring identityString;
        WCHAR idNameBuffer[PACKAGE_FULL_NAME_MAX_LENGTH+1];
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

    std::wstring CreateAssocKeyPath(const std::wstring& assocName)
    {
        std::wstring path{ LR"(SOFTWARE\Classes\)" };
        path += assocName;
        return path;
    }

    // Generate a stable progId.
    std::wstring GenerateProgId()
    {
        // TODO: Generate progIds based on the path of the executable and possibly more data.
        return std::wstring(L"ScoDarGenerated1");
    }

    void RegisterFileExtension(const std::wstring& extension)
    {
        if (extension.at(0) != L'.')
        {
            throw winrt::hresult_invalid_argument();
        }

        auto key_path = CreateAssocKeyPath(extension.c_str());
        wil::unique_hkey key;

        THROW_IF_WIN32_ERROR(::RegCreateKeyEx(HKEY_CURRENT_USER, key_path.c_str(), 0, nullptr, 0,
            KEY_WRITE, nullptr, key.put(), nullptr));
    }

    // TODO: Make sure we only remove if no other handlers exist than our own.
    void UnregisterFileExtension(const std::wstring& extension)
    {

    }

    void RegisterFileHandler(const std::wstring& extension, const std::wstring& verb, _In_opt_ const GUID* delegateExecute)
    {
        auto progId = GenerateProgId();
        auto key_path = CreateAssocKeyPath(progId);
        wil::unique_hkey key;

        THROW_IF_WIN32_ERROR(::RegCreateKeyEx(HKEY_CURRENT_USER, key_path.c_str(), 0, nullptr, 0,
            KEY_WRITE, nullptr, key.put(), nullptr));

        key_path += LR"(\shell\)" + verb + LR"(\command)";
        key.reset();
        THROW_IF_WIN32_ERROR(::RegCreateKeyEx(HKEY_CURRENT_USER, key_path.c_str(), 0, nullptr, 0,
            KEY_WRITE, nullptr, key.put(), nullptr));

        auto command = GetModulePath();
        command += L" ----" + c_fileArgumentString + L":" + verb + L",%1";
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

        // Link the progId as a handler for the extension.
        auto extension_path = CreateAssocKeyPath(extension.c_str()) + LR"(\OpenWithProgids)";
        wil::unique_hkey extension_key;

        THROW_IF_WIN32_ERROR(::RegCreateKeyEx(HKEY_CURRENT_USER, extension_path.c_str(), 0, nullptr,
            0, KEY_WRITE, nullptr, extension_key.put(), nullptr));

        THROW_IF_WIN32_ERROR(::RegSetValueEx(extension_key.get(), progId.c_str(), 0, REG_SZ,
            nullptr, 0));
    }

    void UnregisterFileHandler(const std::wstring& extension)
    {

    }

    // TODO: Handle the scenario where the protocol already exists.
    void RegisterProtocol(const std::wstring& scheme, const std::wstring& displayName, _In_opt_ const GUID* delegateExecute)
    {
        auto key_path = CreateAssocKeyPath(scheme);
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
        command += L" ----" + c_protocolArgumentString + L":%1";
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

    void UnregisterProtocol(const std::wstring& scheme)
    {
        auto key_path = CreateAssocKeyPath(scheme);
        ::RegDeleteTree(HKEY_CURRENT_USER, key_path.c_str());
    }
}
