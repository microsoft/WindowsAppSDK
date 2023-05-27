// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include <winrt/Windows.Data.Xml.Dom.h>

// Including this file once per binary will automatically opt WIL error handling macros into calling RoOriginateError when they
// begin logging a new error.  This greatly improves the debuggability of errors that propagate before a failfast.
#include <wil/result_originate.h>

#include <KozaniManager_h.h>
#include "winrt/Microsoft.Kozani.ManagerRuntime.h"

#include "Logging.h"

using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::ApplicationModel;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::Data::Xml::Dom;

constexpr PCWSTR c_aumidSwitch{ L"-aumid" };
constexpr PCWSTR c_kozaniSettingsFolderName{ L"KozaniSettings" };
constexpr PCWSTR c_rdpFileName{ L"connection.rdp" };
constexpr PCWSTR c_additionalSettingsFileName{ L"AdditionalSettings.txt" };
constexpr PCWSTR c_manifestFileName{ L"AppxManifest.xml" };

enum KozaniStatus
{
    None = 0,
    Activated = 1,
    Failed = 2,
    Closed = 3
};

struct KozaniStatusCallbackHandler : winrt::implements<KozaniStatusCallbackHandler, IKozaniStatusCallback, winrt::Windows::Foundation::IInspectable>
{
    KozaniStatusCallbackHandler(PCWSTR aumid) : m_aumid(aumid)
    {
        m_eventExitProcess.create();
    }

#pragma region IKozaniStatusCallback_methods
    STDMETHODIMP OnActivated(DWORD pid, boolean isNewInstance)
    {
        LOG_HR_MSG(KOZANI_E_INFO, "[ActivationSuccess] IKozaniStausCallback::OnActivated is called. Remote app aumid = %s, pid = %u, isNewInstance = %s",
            m_aumid.c_str(), pid, isNewInstance ? "true" : "false");

        m_remoteAppProcessId = pid;
        m_status = KozaniStatus::Activated;

        if (!isNewInstance)
        {
            // This activation does not launch a new app process. Exit this process as there is already another one tracking the remote process.
            // Example: Calculator app has single process for multiple app windows.
            m_eventExitProcess.SetEvent();
        }
        return S_OK;
    }

    STDMETHODIMP OnActivationFailed(
        DWORD errorCode,
        PCWSTR errorMessage)
    {
        LOG_HR_MSG(KOZANI_E_INFO, "[ActivationFailed] IKozaniStausCallback::OnActivationFailed is called. Remote app aumid = %s, errorCode = 0x%x, errorMessage: %s",
                m_aumid.c_str(), errorCode, errorMessage);

        m_status = KozaniStatus::Failed;
        m_eventExitProcess.SetEvent();
        return S_OK;
    }

    STDMETHODIMP OnClosed()
    {
        LOG_HR_MSG(KOZANI_E_INFO, "[App Terminated] IKozaniStausCallback::OnClosed is called. Remote app aumid = %s, pid=%u",
                m_aumid.c_str(), m_remoteAppProcessId);

        m_status = KozaniStatus::Closed;
        m_eventExitProcess.SetEvent();
        return S_OK;
    }
#pragma endregion IKozaniStatusCallback_methods

    bool WaitForExitProcessEvent(DWORD timeout)
    {
        return m_eventExitProcess.wait(timeout);
    }

    KozaniStatus GetStatus()
    {
        return m_status;
    }

private:
    std::wstring m_aumid;
    DWORD m_remoteAppProcessId{};
    KozaniStatus m_status{};
    wil::unique_event m_eventExitProcess;
};

void LogArgs(int argc, PWSTR* argv)
{
    TraceLoggingWrite(Microsoft_Kozani_HostRuntime_TraceLogger::Provider(), "argc",
        TraceLoggingValue(argc, "argc"));
    for (int i = 0; i < argc; i++)
    {
        TraceLoggingWrite(Microsoft_Kozani_HostRuntime_TraceLogger::Provider(), "argv",
            TraceLoggingValue(i, "index"),
            TraceLoggingValue(argv[i], "argv"));
    }
}

std::wstring GetRemoteAumidFromCommandLineArgs(PCWSTR commandLine)
{
    int argc{};
    const wil::unique_hlocal_ptr<PWSTR[]> argv{ CommandLineToArgvW(commandLine, &argc) };
    LogArgs(argc, argv.get());

    for (int i = 0; i < argc; i++)
    {
        // Find "-aumid" switch
        if (_wcsicmp(argv[i], c_aumidSwitch) == 0)
        {
            // The argv[i+1] is the aumid. Make sure it does not overflow, or the command line input args are incorrect.
            THROW_HR_IF(E_INVALIDARG, i + 1 == argc);
            return argv[i + 1];
        }
    }

    THROW_HR_MSG(E_INVALIDARG, "-aumid switch not found in command line arguments");
}

// Get the remote app AUMID from Local Variant Package (LVP)'s manifest xml. 
// Example:
// <Application Id="App" uap10:HostId="KozaniHostRuntime" uap10:Parameters="-aumid AbcInc.AbcApp_oiuanmryvpj1y!App">
std::wstring GetRemoteAumidFromManifest()
{
    AppInfo appInfo{ AppInfo::Current() };
    auto appId{ appInfo.Id() };

    auto manifestFile{ appInfo.Package().InstalledLocation().GetFileAsync(c_manifestFileName).get()};
    XmlDocument xmlDocument{ XmlDocument::LoadFromFileAsync(manifestFile).get() };

    std::wstring xpath{ L"/*[local-name()='Package']/*[local-name()='Applications']/*[local-name()='Application' and @Id='" };
    xpath += appId.c_str();
    xpath += L"'][1]";

    LOG_HR_MSG(KOZANI_E_INFO, "appId=%ls, xpath=%ls", appId.c_str(), xpath.c_str());

    auto applicationNode{ xmlDocument.SelectSingleNode(xpath) };
    THROW_HR_IF_NULL_MSG(HRESULT_FROM_WIN32(ERROR_INVALID_DATA), applicationNode,
            "Invalid LVP manifest - cannot find Application node with Id=%ls. Manifest xml: %ls",
            appId.c_str(), xmlDocument.GetXml().c_str());

    auto attributeMap{ applicationNode.Attributes() };
    auto uap10NS{ winrt::Windows::Foundation::PropertyValue::CreateString(L"http://schemas.microsoft.com/appx/manifest/uap/windows10/10") };
    auto paramAttributeNode{ attributeMap.GetNamedItemNS(uap10NS, L"Parameters")};
    THROW_HR_IF_NULL_MSG(HRESULT_FROM_WIN32(ERROR_INVALID_DATA), paramAttributeNode,
            "Invalid LVP manifest - missing uap10:Parameters attribute in Application element with Id=%ls. Application element xml: %ls",
            appId.c_str(), applicationNode.GetXml().c_str());

    // The uap10:Parameters attribute value contains command line args with remote app aumid. Example: 
    // uap10:Parameters="-aumid AbcInc.AbcApp_oiuanmryvpj1y!App"
    auto commandLineArgs{ winrt::unbox_value<winrt::hstring>(paramAttributeNode.NodeValue()) };
    LOG_HR_MSG(KOZANI_E_INFO, "commandLineArgs=%ls", commandLineArgs.c_str());
    return GetRemoteAumidFromCommandLineArgs(commandLineArgs.c_str());
}

void GetConfigurationFiles(std::wstring& rdpFilePath, std::wstring& additionalSettingsFilePath)
{
    StorageFolder localFolder{ ApplicationData::Current().LocalFolder() };
    // This hostRuntime exe should run with the identity of the hosted app (localvariant) package that activated
    // Logging the AppData local folder path thus indicates the identity of the hosted app.
    TraceLoggingWrite(Microsoft_Kozani_HostRuntime_TraceLogger::Provider(), "localFolder",
        TraceLoggingValue(localFolder.Path().c_str(), "path"));

    auto settingsFolder{ localFolder.GetFolderAsync(c_kozaniSettingsFolderName).get() };
    auto rdpFile{ settingsFolder.GetFileAsync(c_rdpFileName).get() };
    THROW_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_DATA), !rdpFile.IsOfType(StorageItemTypes::File));

    rdpFilePath = rdpFile.Path();

    auto additionalSettingsFile{ settingsFolder.TryGetItemAsync(c_additionalSettingsFileName).get() };
    if (additionalSettingsFile)
    {
        THROW_HR_IF(HRESULT_FROM_WIN32(ERROR_INVALID_DATA), !additionalSettingsFile.IsOfType(StorageItemTypes::File));
        additionalSettingsFilePath = additionalSettingsFile.Path();
    }
    else
    {
        additionalSettingsFilePath.clear();
    }
}

int APIENTRY wWinMain(
    HINSTANCE /*hInstance*/,
    HINSTANCE /*hPrevInstance*/,
    PWSTR pCmdLine,
    int /*nCmdShow*/) try
{
    wil::SetResultLoggingCallback(&TraceFailureFromProvider<Microsoft_Kozani_HostRuntime_TraceLogger>);
    winrt::init_apartment();

    auto activatedEventArgs{ AppInstance::GetActivatedEventArgs() };
    std::wstring remoteAumid;
    if (activatedEventArgs.Kind()== winrt::Windows::ApplicationModel::Activation::ActivationKind::Launch)
    {
        // For launch activation, we can simply get the AUMID from command line arguments.
        remoteAumid = GetRemoteAumidFromCommandLineArgs(pCmdLine);
    }
    else
    {
        remoteAumid = GetRemoteAumidFromManifest();
    }
    LOG_HR_MSG(KOZANI_E_INFO, "remoteAumid=%ls", remoteAumid.c_str());

    std::wstring rdpFilePath;
    std::wstring additionalSettingsFilePath;
    GetConfigurationFiles(rdpFilePath, additionalSettingsFilePath);
    LOG_HR_MSG(KOZANI_E_INFO, "rdpFilePath=%ls, additionalSettingsFilePath=%ls", rdpFilePath.c_str(), additionalSettingsFilePath.c_str());

    auto runtimeManager{ winrt::Microsoft::Kozani::ManagerRuntime::ManagerRuntimeManager::Create() };

    auto statusCallback{ winrt::make_self<KozaniStatusCallbackHandler>(remoteAumid.c_str()) };

    runtimeManager.ActivateRemoteApplication(
        activatedEventArgs.Kind(),
        remoteAumid.c_str(),
        rdpFilePath.c_str(),
        GetCurrentProcessId(),
        activatedEventArgs,
        statusCallback.as<winrt::Windows::Foundation::IInspectable>(),
        additionalSettingsFilePath.c_str());

    statusCallback->WaitForExitProcessEvent(INFINITE);

    TraceLoggingWrite(Microsoft_Kozani_HostRuntime_TraceLogger::Provider(), "Exiting instance");
    return S_OK;
}
CATCH_RETURN()
