// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#include <pch.h>
#include "Association.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    HKEY GetRegistrationRoot()
    {
        return HKEY_CURRENT_USER;
    }

    bool IsFileExtension(const std::wstring& extension)
    {
        return (extension.at(0) == L'.');
    }

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

    std::wstring ComputeAppId()
    {
        // PRF = Project Reunion Framework.  A simple prefix to help identify ProgIds we compute here.
        // AppId = Prefix + Hash(modulePath)
        auto modulePath = GetModulePath();
        std::hash<std::wstring> hasher;
        auto hash = hasher(modulePath);
;
        wchar_t hashString[17]{}; // 16 + 1 characters for 64bit value represented as a string with a null terminator.
        THROW_IF_FAILED(StringCchPrintf(hashString, _countof(hashString), L"%I64x", hash));

        std::wstring result{ c_progIdPrefix };
        result += hashString;
        return result;
    }

    // Compute a stable progId.
    std::wstring ComputeProgId(AssociationType type)
    {
        return ComputeProgId(ComputeAppId(), type);
    }

    std::wstring ComputeProgId(const std::wstring& appId, AssociationType type)
    {
        std::wstring typeSuffix;
        if (type == AssociationType::File)
        {
            typeSuffix = c_fileTypeProgIdSuffix;
        }
        else if (type == AssociationType::Protocol)
        {
            typeSuffix = c_protocolProgIdSuffix;
        }

        return std::wstring(appId + typeSuffix.c_str());
    }

    std::wstring CreateAssocKeyPath(const std::wstring& assoc)
    {
        // Example: Software\Classes\<assoc>
        std::wstring path = c_softwareClassesKeyPath + assoc;
        return path;
    }

    wil::unique_hkey CreateAssocKey(const std::wstring& assoc, REGSAM samDesired)
    {
        auto path = CreateAssocKeyPath(assoc.c_str());
        wil::unique_hkey key;

        THROW_IF_WIN32_ERROR(::RegCreateKeyEx(GetRegistrationRoot(), path.c_str(), 0, nullptr, 0,
            samDesired, nullptr, key.put(), nullptr));
        return key;
    }

    wil::unique_hkey OpenAssocKey(const std::wstring& assoc, REGSAM samDesired)
    {
        auto path = CreateAssocKeyPath(assoc.c_str());
        wil::unique_hkey key;

        THROW_IF_WIN32_ERROR(::RegOpenKeyEx(GetRegistrationRoot(), path.c_str(), 0, samDesired,
            key.put()));
        return key;
    }

    bool AssocExists(const std::wstring& assoc)
    {
        auto path = CreateAssocKeyPath(assoc.c_str());
        wil::unique_hkey key;
        if (::RegOpenKeyEx(GetRegistrationRoot(), path.c_str(), 0, KEY_READ,
            key.put()) == ERROR_SUCCESS)
        {
            return true;
        }
        return false;
    }

    bool AssocValueExists(const std::wstring& assoc, const std::wstring& value)
    {
        auto path = CreateAssocKeyPath(assoc.c_str());
        wil::unique_hkey key;
        if (::RegOpenKeyEx(GetRegistrationRoot(), path.c_str(), 0, KEY_READ, key.put())
            == ERROR_SUCCESS)
        {
            if (::RegQueryValueEx(key.get(), value.c_str(), 0, nullptr, nullptr, nullptr)
                == ERROR_SUCCESS)
            {
                return true;
            }
        }
        return false;
    }

    void DeleteAssocKey(const std::wstring& assoc)
    {
        auto path = CreateAssocKeyPath(assoc);
        ::RegDeleteTree(GetRegistrationRoot(), path.c_str());
    }

    // Registers a ProgId definition under the classes root in the registry.
    wil::unique_hkey RegisterProgId(const std::wstring& progId, const std::wstring& defaultValue,
        const std::wstring& appUserModelId, const std::wstring& applicationDisplayName,
        const std::wstring& logo)
    {
        // Example: HKEY_CURRENT_USER\Software\Classes\<progId>
        auto key = CreateAssocKey(progId, KEY_WRITE);

        if (!defaultValue.empty())
        {
            // Example: HKEY_CURRENT_USER\Software\Classes\<progId>\(Default)
            THROW_IF_WIN32_ERROR(::RegSetValueEx(key.get(), nullptr, 0, REG_SZ,
                reinterpret_cast<BYTE const*>(defaultValue.c_str()),
                static_cast<uint32_t>((defaultValue.size() + 1) * sizeof(wchar_t))));
        }

        if (!applicationDisplayName.empty())
        {
            // Example: HKEY_CURRENT_USER\Software\Classes\<progId>\Application\ApplicationName
            wil::unique_hkey applicationKey;
            THROW_IF_WIN32_ERROR(::RegCreateKeyEx(key.get(), c_applicationKeyName.c_str(), 0,
                nullptr, 0, KEY_WRITE, nullptr, applicationKey.put(), nullptr));
            THROW_IF_WIN32_ERROR(::RegSetValueEx(applicationKey.get(),
                c_applicationNameValueName.c_str(), 0, REG_SZ,
                reinterpret_cast<BYTE const*>(applicationDisplayName.c_str()),
                static_cast<uint32_t>((applicationDisplayName.size() + 1) * sizeof(wchar_t))));
        }

        if (!logo.empty())
        {
            // Example: HKEY_CURRENT_USER\Software\Classes\<progId>\DefaultIcon\(Default)
            wil::unique_hkey defaultIconKey;
            THROW_IF_WIN32_ERROR(::RegCreateKeyEx(key.get(), c_defaultIconKeyName.c_str(), 0,
                nullptr, 0, KEY_WRITE, nullptr, defaultIconKey.put(), nullptr));
            THROW_IF_WIN32_ERROR(::RegSetValueEx(defaultIconKey.get(), nullptr, 0, REG_SZ,
                reinterpret_cast<BYTE const*>(logo.c_str()),
                static_cast<uint32_t>((logo.size() + 1) * sizeof(wchar_t))));
        }

        if (!appUserModelId.empty())
        {
            // Example: HKEY_CURRENT_USER\Software\Classes\<progId>\AppUserModelId
            THROW_IF_WIN32_ERROR(::RegSetValueEx(key.get(), c_appUserModelIdValueName.c_str(), 0,
                REG_SZ, reinterpret_cast<BYTE const*>(appUserModelId.c_str()),
                static_cast<uint32_t>((appUserModelId.size() + 1) * sizeof(wchar_t))));
        }
        return key;
    }

    void UnregisterProgId(const std::wstring& progId)
    {
        DeleteAssocKey(progId);
    }

    std::wstring CreateApplicationKeyPath(const std::wstring& appId)
    {
        // Example: HKEY_CURRENT_USER\Software\Microsoft\ReunionApplications\<appId>
        return std::wstring(c_applicationsKeyPath + appId + c_capabilitiesKeyPath);
    }

    // Creates application defined capabilities key, and registers it as a RegisteredApplication.
    wil::unique_hkey CreateApplicationKey(const std::wstring& appId, REGSAM samDesired)
    {
        // Example: HKEY_CURRENT_USER\Software\RegisterApplications\<appId>
        wil::unique_hkey registeredAppsKey;
        THROW_IF_WIN32_ERROR(::RegCreateKeyEx(GetRegistrationRoot(), c_registeredApplicationsKeyPath.c_str(),
            0, nullptr, 0, samDesired, nullptr, registeredAppsKey.put(), nullptr));

        std::wstring applicationKeyPath = CreateApplicationKeyPath(appId);
        wil::unique_hkey applicationKey;
        THROW_IF_WIN32_ERROR(::RegCreateKeyEx(GetRegistrationRoot(), applicationKeyPath.c_str(),
            0, nullptr, 0, samDesired, nullptr, applicationKey.put(), nullptr));

        THROW_IF_WIN32_ERROR(::RegSetValueEx(registeredAppsKey.get(), appId.c_str(), 0, REG_SZ,
            reinterpret_cast<BYTE const*>(applicationKeyPath.c_str()),
            static_cast<uint32_t>((applicationKeyPath.size() + 1) * sizeof(wchar_t))));

        return applicationKey;
    }

    // Looks up and opens a RegisteredApplication's capability key based on the AppId.
    wil::unique_hkey OpenApplicationKey(const std::wstring& appId, REGSAM samDesired)
    {
        wil::unique_hkey registeredAppsKey;
        THROW_IF_WIN32_ERROR(::RegOpenKeyEx(GetRegistrationRoot(), c_registeredApplicationsKeyPath.c_str(),
            0, samDesired, registeredAppsKey.put()));

        DWORD pathSize{ 0 };
        THROW_IF_WIN32_ERROR(::RegQueryValueEx(registeredAppsKey.get(), appId.c_str(), 0, nullptr,
            nullptr, &pathSize));

        std::wstring applicationKeyPath(pathSize, L'\0');
        THROW_IF_WIN32_ERROR(::RegQueryValueEx(registeredAppsKey.get(), appId.c_str(), 0, nullptr,
            reinterpret_cast<BYTE*>(applicationKeyPath.data()),
            &pathSize));

        wil::unique_hkey applicationKey;
        THROW_IF_WIN32_ERROR(::RegOpenKeyEx(GetRegistrationRoot(), applicationKeyPath.c_str(),
            0, samDesired, applicationKey.put()));

        return applicationKey;
    }

    void RegisterApplication(const std::wstring& appId)
    {
        CreateApplicationKey(appId);
    }

    void UnregisterApplication(const std::wstring& appId)
    {
        // Example: HKEY_CURRENT_USER\Software\Microsoft\ReunionApplications\<appId>\Capabilities
        std::wstring capabilitiesKeyPath = c_applicationsKeyPath + appId + c_capabilitiesKeyPath;
        ::RegDeleteTree(GetRegistrationRoot(), capabilitiesKeyPath.c_str());

        wil::unique_hkey registeredAppsKey;
        if (::RegOpenKeyEx(GetRegistrationRoot(), c_registeredApplicationsKeyPath.c_str(), 0,
            KEY_WRITE, registeredAppsKey.put()) == ERROR_SUCCESS)
        {
            ::RegDeleteValue(registeredAppsKey.get(), appId.c_str());
        }
    }

    void RegisterVerb(const std::wstring& progId, const std::wstring& verb, const std::wstring& command,
        _In_opt_ const GUID* delegateExecute)
    {
        // Example: HKEY_CURRENT_USER\Software\Classes\<progId>\shell\<verb>\command
        auto assocKey = OpenAssocKey(progId, KEY_WRITE);
        auto key_path = c_shellKeyName + L"\\" + verb + L"\\" + c_commandKeyName;
        wil::unique_hkey key;

        THROW_IF_WIN32_ERROR(::RegCreateKeyEx(assocKey.get(), key_path.c_str(), 0, nullptr, 0,
            KEY_WRITE, nullptr, key.put(), nullptr));

        THROW_IF_WIN32_ERROR(::RegSetValueEx(key.get(), nullptr, 0, REG_SZ,
            reinterpret_cast<BYTE const*>(command.c_str()),
            static_cast<uint32_t>((command.size() + 1) * sizeof(wchar_t))));

        if (delegateExecute)
        {
            std::wstring delegateClsid{ LR"({????????-????-????-????-????????????})" };
            ::StringFromGUID2(*delegateExecute, delegateClsid.data(), 39);

            THROW_IF_WIN32_ERROR(::RegSetValueEx(key.get(), c_delegateExecuteValueName.c_str(), 0, REG_SZ,
                reinterpret_cast<BYTE const*>(delegateClsid.c_str()),
                static_cast<uint32_t>((delegateClsid.size() + 1) * sizeof(wchar_t))));
        }
    }

    void UnregisterVerb(const std::wstring& progId, const std::wstring& verb)
    {
        // Example: HKEY_CURRENT_USER\Software\Classes\<progId>\shell\<verb>\command
        auto key_path = CreateAssocKeyPath(progId) + L"\\" + c_shellKeyName + L"\\" + verb +
            L"\\" + c_commandKeyName;
        ::RegDeleteTree(GetRegistrationRoot(), key_path.c_str());
    }

    void RegisterProtocol(const std::wstring& scheme)
    {
        if (AssocExists(scheme) && AssocValueExists(scheme, c_urlProtocolValueName))
        {
            // Protocol already exists.
            return;
        }

        if (AssocExists(scheme))
        {
            // ProgId exists, but isn't a protocol.
            throw std::invalid_argument("scheme");
        }

        // A protocol is defined as a special progId that contains a value at the root named
        // "URL Protocol".  This is similar to how file types are defined in the same location,
        // but always start with a period.

        // Example: HKEY_CURRENT_USER\Software\Classes\<scheme>
        std::wstring defaultValue = c_urlDefaultValuePrefix + scheme;
        auto key = RegisterProgId(scheme, defaultValue);

        // Example: HKEY_CURRENT_USER\Software\Classes\<scheme>\URL Protocol
        std::wstring emptyValue{ L"" };
        THROW_IF_WIN32_ERROR(::RegSetValueEx(key.get(), c_urlProtocolValueName.c_str(), 0,
            REG_SZ, reinterpret_cast<BYTE const*>(emptyValue.c_str()),
            static_cast<uint32_t>((emptyValue.size() + 1) * sizeof(wchar_t))));
    }

    void UnregisterProtocol(const std::wstring& scheme)
    {
        DeleteAssocKey(scheme);
    }

    void RegisterFileExtension(const std::wstring& extension)
    {
        if (!IsFileExtension(extension))
        {
            throw winrt::hresult_invalid_argument();
        }

        CreateAssocKey(extension, KEY_WRITE);
    }

    void UnregisterFileExtension(const std::wstring& extension)
    {
        if (!IsFileExtension(extension))
        {
            throw winrt::hresult_invalid_argument();
        }

        DeleteAssocKey(extension);
    }

    std::wstring CreateCapabilitySubKeyPath(AssociationType type)
    {
        std::wstring subKeyPath;
        if (type == AssociationType::File)
        {
            subKeyPath = L"FileAssociations";
        }
        else if (type == AssociationType::Protocol)
        {
            subKeyPath = L"UrlAssociations";
        }
        else
        {
            throw winrt::hresult_illegal_method_call();
        }

        return subKeyPath;
    }

    void RegisterAssociationHandler(const std::wstring& handlerAppId, const std::wstring& association,
        AssociationType type)
    {
        if (type == AssociationType::File && !IsFileExtension(association))
        {
            throw std::invalid_argument("association");
        }

        if (!AssocExists(association))
        {
            throw std::invalid_argument("association");
        }

        // Enable the handler to be a part of user choice.
        auto subKeyPath = CreateCapabilitySubKeyPath(type);
        auto applicationKey = OpenApplicationKey(handlerAppId, KEY_READ | KEY_WRITE);

        // Example: HKEY_CURRENT_USER\Software\Microsoft\ReunionApplications\<appId>\Capabilities\[URLAssociations/FileAssociations]
        wil::unique_hkey subKey;
        THROW_IF_WIN32_ERROR(::RegCreateKeyEx(applicationKey.get(), subKeyPath.c_str(), 0, nullptr,
            0, KEY_WRITE, nullptr, subKey.put(), nullptr));

        // The entries here link a file extension or protocol scheme to a specific ProgId that handles the activation.
        // Example: Name: <association>
        // Example: Value: <progId>
        auto progId = ComputeProgId(handlerAppId, type);
        THROW_IF_WIN32_ERROR(::RegSetValueEx(subKey.get(), association.c_str(), 0, REG_SZ,
            reinterpret_cast<BYTE const*>(progId.c_str()),
            static_cast<uint32_t>((progId.size() + 1) * sizeof(wchar_t))));

        // If it's a file type handler, it needs additional entries in order to be enumerated.
        if (type == AssociationType::File)
        {
            wil::unique_hkey openWithKey;
            auto assocKey = OpenAssocKey(association, KEY_WRITE);

            // Example: HKEY_CURRENT_USER\Software\Classes\<association>\OpenWithProgids
            THROW_IF_WIN32_ERROR(::RegCreateKeyEx(assocKey.get(), c_openWithProgIdsKeyName.c_str(),
                0, nullptr, 0, KEY_WRITE, nullptr, openWithKey.put(), nullptr));

            // Example: Name: <progId>
            // Value is unused.
            THROW_IF_WIN32_ERROR(::RegSetValueEx(openWithKey.get(), progId.c_str(), 0, REG_SZ,
                nullptr, 0));
        }
    }

    void UnregisterAssociationHandler(const std::wstring& handlerAppId, const std::wstring& association,
        AssociationType type)
    {
        if (type == AssociationType::File && !IsFileExtension(association))
        {
            throw std::invalid_argument("association");
        }

        // Example: HKEY_CURRENT_USER\Software\Microsoft\ReunionApplications\<appId>\Capabilities\[URLAssociations/FileAssociations]\<association>
        auto subKeyPath = CreateCapabilitySubKeyPath(type);
        auto applicationKey = OpenApplicationKey(handlerAppId, KEY_READ | KEY_WRITE);
        wil::unique_hkey subKey;
        if (::RegOpenKeyEx(applicationKey.get(), subKeyPath.c_str(), 0, KEY_WRITE,
            subKey.put()) == ERROR_SUCCESS)
        {
            ::RegDeleteValue(subKey.get(), association.c_str());
        }

        // Remove file type handler specific values.
        if (type == AssociationType::File)
        {
            // Example: HKEY_CURRENT_USER\Software\Classes\<association>\OpenWithProgids
            wil::unique_hkey openWithKey;
            auto assocKey = OpenAssocKey(association, KEY_WRITE);
            if (::RegOpenKeyEx(assocKey.get(), c_openWithProgIdsKeyName.c_str(), 0, KEY_WRITE,
                openWithKey.put()) == ERROR_SUCCESS)
            {
                auto progId = ComputeProgId(handlerAppId, type);
                ::RegDeleteValue(openWithKey.get(), progId.c_str());
            }
        }
    }
}
