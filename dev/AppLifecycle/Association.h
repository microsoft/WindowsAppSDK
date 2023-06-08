// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.
#pragma once

namespace winrt::Microsoft::Windows::AppLifecycle::implementation
{
    // Association registry key values.
    static PCWSTR c_openWithProgIdsKeyName{ L"OpenWithProgids" };
    static PCWSTR c_softwareClassesKeyPath{ LR"(Software\Classes\)" };
    static PCWSTR c_applicationKeyName{ L"Application" };
    static PCWSTR c_applicationNameValueName{ L"ApplicationName" };
    static PCWSTR c_defaultIconKeyName{ L"DefaultIcon" };
    static PCWSTR c_appUserModelIdValueName{ L"AppUserModelId" };
    static PCWSTR c_applicationsKeyPath{ LR"(Software\Microsoft\WindowsAppRuntimeApplications\)" };
    static PCWSTR c_capabilitiesKeyPath{ LR"(\Capabilties)" };
    static PCWSTR c_registeredApplicationsKeyPath{ LR"(Software\RegisteredApplications\)" };
    static PCWSTR c_shellKeyName{ L"shell" };
    static PCWSTR c_commandKeyName{ L"command" };
    static PCWSTR c_delegateExecuteValueName{ L"DelegateExecute" };
    static PCWSTR c_urlProtocolValueName{ L"URL Protocol" };
    static PCWSTR c_urlDefaultValuePrefix{ L"URL:" };
    static PCWSTR c_openVerbName{ L"open" };
    static PCWSTR c_commandLineArgumentFormat{ L"%1" };

    // ProgId generation values.
    static PCWSTR c_progIdPrefix{ L"App." };
    static PCWSTR c_fileTypeProgIdSuffix{ L".File" };
    static PCWSTR c_protocolProgIdSuffix{ L".Protocol" };

    enum AssociationType
    {
        File,
        Protocol
    };

    bool IsFileExtension(const std::wstring& extension);
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
    void NotifyShellAssocChanged();
}
