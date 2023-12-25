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

// Uncomment to enable wait for debugger when the local variant app is launched. We can attach debugger to the KozaniHostRuntime.exe while it is waiting.
//#define WAIT_FOR_DEBUGGER

using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Storage;
using namespace winrt::Windows::ApplicationModel;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::Data::Xml::Dom;

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
        LOG_HR_MSG(KOZANI_E_INFO, "[ActivationSuccess] IKozaniStausCallback::OnActivated is called. Remote app aumid = %ls, pid = %u, isNewInstance = %u",
            m_aumid.c_str(), pid, isNewInstance);

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
        LOG_HR_MSG(KOZANI_E_INFO, "[ActivationFailed] IKozaniStausCallback::OnActivationFailed is called. Remote app aumid = %ls, errorCode = 0x%x, errorMessage: %s",
                m_aumid.c_str(), errorCode, errorMessage);

        m_status = KozaniStatus::Failed;
        m_eventExitProcess.SetEvent();
        return S_OK;
    }

    STDMETHODIMP OnClosed()
    {
        LOG_HR_MSG(KOZANI_E_INFO, "[App Terminated] IKozaniStausCallback::OnClosed is called. Remote app aumid = %ls, pid=%u",
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

// Remote app AUMID is stored in an app extension of the local variant package (LVP). The app extension name is formatted as:
//     com.microsoft.kozani.localvariant.remoteapp.<Converted LVP package family name>
// and the app extension Id is the package-relative application identifier (PRAID) of the LVP app being activated.
// <Converted LVP package family name>: we replace the '_' character in the package family name with '-' as '_' is not allowed in the app extension name.
//
// For example:
// <uap3:Extension Category="windows.appExtension">
//   <uap3:AppExtension Name = "com.microsoft.kozani.localvariant.remoteapp.Calculator-fy70fzsv57rkp"
//     Id = "App"
//     DisplayName = "Remote app AUMID"
//     Description = "The App User Mode ID of the remote app this local variant app represents">
//     <uap3:Properties>
//       <RemoteAppAumid>Microsoft.WindowsCalculator_8wekyb3d8bbwe!App</RemoteAppAumid>
//     </uap3:Properties>
//   </uap3:AppExtension>
// </uap3:Extension>
winrt::hstring GetRemoteAumid()
{
    WCHAR lvpAumid[APPLICATION_USER_MODEL_ID_MAX_LENGTH + 1]{};
    UINT32 lvpAumidLength{ ARRAYSIZE(lvpAumid) };
    THROW_IF_WIN32_ERROR(::GetCurrentApplicationUserModelId(&lvpAumidLength, lvpAumid));

    WCHAR lvpFamilyName[PACKAGE_FAMILY_NAME_MAX_LENGTH + 1]{};
    WCHAR lvpPraid[PACKAGE_RELATIVE_APPLICATION_ID_MAX_LENGTH + 1]{};
    UINT32 lvpFamilyNameLength{ ARRAYSIZE(lvpFamilyName) };
    UINT32 lvpPraidLength{ ARRAYSIZE(lvpPraid) };
    THROW_IF_WIN32_ERROR(ParseApplicationUserModelId(lvpAumid, &lvpFamilyNameLength, lvpFamilyName, &lvpPraidLength, lvpPraid));

    // Replace '_' in the family name with '-' as '_' cannot be used in the app extension name.
    for (UINT32 i = 0; i < lvpFamilyNameLength; i++)
    {
        if (lvpFamilyName[i] == L'_')
        {
            lvpFamilyName[i] = L'-';
            break;
        }
    }

    std::wstring appExtensionName{ L"com.microsoft.kozani.localvariant.remoteapp." };
    appExtensionName += lvpFamilyName;

    auto catalog{ AppExtensions::AppExtensionCatalog::Open(appExtensionName.c_str()) };
    IVectorView<AppExtensions::AppExtension> appExtensions{ catalog.FindAllAsync().get() };
    for (const auto appExtension : appExtensions)
    {
        if (appExtension.Id() == lvpPraid)
        {
            const auto properties{ appExtension.GetExtensionPropertiesAsync().get() };
            const auto property{ properties.Lookup(L"RemoteAppAumid").as<IMap<winrt::hstring, winrt::Windows::Foundation::IInspectable>>() };
            const auto remoteAumid{ winrt::unbox_value<winrt::hstring>(property.Lookup(L"#text")) };
            return remoteAumid;
        }
    }

    THROW_WIN32_MSG(ERROR_NOT_FOUND, "Cannot find remote app aumid from app extension with name: %ls, Id: %ls", appExtensionName.c_str(), lvpPraid);
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

#ifdef WAIT_FOR_DEBUGGER
void WaitForDebugger()
{
    while (!IsDebuggerPresent())
    {
        Sleep(3000);
    }
}
#endif

int APIENTRY wWinMain(
    HINSTANCE /*hInstance*/,
    HINSTANCE /*hPrevInstance*/,
    PWSTR /*pCmdLine*/,
    int /*nCmdShow*/) try
{
    wil::SetResultLoggingCallback(&TraceFailureFromProvider<Microsoft_Kozani_HostRuntime_TraceLogger>);
    winrt::init_apartment();

#ifdef WAIT_FOR_DEBUGGER
    WaitForDebugger();
#endif

    winrt::hstring remoteAumid{ GetRemoteAumid() };
    LOG_HR_MSG(KOZANI_E_INFO, "remoteAumid=%ls", remoteAumid.c_str());

    std::wstring rdpFilePath;
    std::wstring additionalSettingsFilePath;
    GetConfigurationFiles(rdpFilePath, additionalSettingsFilePath);
    LOG_HR_MSG(KOZANI_E_INFO, "rdpFilePath=%ls, additionalSettingsFilePath=%ls", rdpFilePath.c_str(), additionalSettingsFilePath.c_str());

    auto activatedEventArgs{ AppInstance::GetActivatedEventArgs() };
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

    // Release the IManagerRuntimeManager object so the host runtime does not hold on to it while waiting for process termination event.
    // In case this process is killed by the user (i.e., from Task Manager), holding the IManagerRuntimeManager object will leak the ref count
    // and prevent KozaniManager.exe from exiting after all remote apps are closed.
    runtimeManager = nullptr;

    statusCallback->WaitForExitProcessEvent(INFINITE);

    TraceLoggingWrite(Microsoft_Kozani_HostRuntime_TraceLogger::Provider(), "Exiting instance");
    winrt::uninit_apartment();
    return S_OK;
}
CATCH_RETURN()
