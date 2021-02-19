// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

namespace winrt::Microsoft::ApplicationModel::Activation::implementation
{
    // Association registry key values.
    static LPCWSTR c_openWithProgIdsKeyName{ L"OpenWithProgids" };
    static LPCWSTR c_softwareClassesKeyPath{ LR"(Software\Classes\)" };
    static LPCWSTR c_applicationKeyName{ L"Application" };
    static LPCWSTR c_applicationNameValueName{ L"ApplicationName" };
    static LPCWSTR c_defaultIconKeyName{ L"DefaultIcon" };
    static LPCWSTR c_appUserModelIdValueName{ L"AppUserModelId" };
    static LPCWSTR c_applicationsKeyPath{ LR"(Software\Microsoft\ReunionApplications\)" };
    static LPCWSTR c_capabilitiesKeyPath{ LR"(\Capabilties)" };
    static LPCWSTR c_registeredApplicationsKeyPath{ LR"(Software\RegisteredApplications\)" };
    static LPCWSTR c_shellKeyName{ L"shell" };
    static LPCWSTR c_commandKeyName{ L"command" };
    static LPCWSTR c_delegateExecuteValueName{ L"DelegateExecute" };
    static LPCWSTR c_urlProtocolValueName{ L"URL Protocol" };
    static LPCWSTR c_urlDefaultValuePrefix{ L"URL:" };
    static LPCWSTR c_openVerbName{ L"open" };

    // ProgId generation values.
    static LPCWSTR c_progIdPrefix{ L"App." };
    static LPCWSTR c_fileTypeProgIdSuffix{ L".File" };
    static LPCWSTR c_protocolProgIdSuffix{ L".Protocol" };

    enum AssociationType
    {
        File,
        Protocol
    };

    bool IsFileExtension(const std::wstring& extension);
    std::wstring GetFullIdentityString();
    bool HasIdentity();
    std::wstring GetModulePath();
    std::wstring ComputeAppId(const std::wstring& customSeed = L"");
    std::wstring ComputeProgId(AssociationType type);
    std::wstring ComputeProgId(const std::wstring& appId, AssociationType type);
    std::wstring CreateAssocKeyPath(const std::wstring& assoc);
    wil::unique_hkey CreateAssocKey(const std::wstring& assoc, REGSAM samDesired = KEY_WRITE);
    wil::unique_hkey OpenAssocKey(const std::wstring& assoc, REGSAM samDesired = KEY_READ);
    void DeleteAssocKey(const std::wstring& assoc);
    wil::unique_hkey RegisterProgId(const std::wstring& progId, const std::wstring& defaultValue = L"",
        const std::wstring& appUserModelId = L"", const std::wstring& applicationDisplayName = L"",
        const std::wstring& logo = L"");
    void UnregisterProgId(const std::wstring& progId);
    std::wstring CreateApplicationKeyPath();
    wil::unique_hkey CreateApplicationKey(const std::wstring& progId, REGSAM samDesired = KEY_WRITE);
    wil::unique_hkey OpenApplicationKey(const std::wstring& progId, REGSAM samDesired = KEY_READ);
    void RegisterApplication(const std::wstring& appId);
    void UnregisterApplication(const std::wstring& appId);
    void RegisterVerb(const std::wstring& progId, const std::wstring& verb, const std::wstring& command,
        _In_opt_ const GUID* delegateExecute = nullptr);
    void UnregisterVerb(const std::wstring& progId, const std::wstring& verb);
    void RegisterProtocol(const std::wstring& scheme);
    void UnregisterProtocol(const std::wstring& scheme);
    void RegisterFileExtension(const std::wstring& extension);
    void UnregisterFileExtension(const std::wstring& extension);
    void RegisterAssociationHandler(const std::wstring& handlerAppId, const std::wstring& association,
        AssociationType type);
    void UnregisterAssociationHandler(const std::wstring& handlerAppId, const std::wstring& association,
        AssociationType type);
}
