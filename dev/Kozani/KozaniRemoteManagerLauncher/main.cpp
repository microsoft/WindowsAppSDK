// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include <filesystem>

// Including this file once per binary will automatically opt WIL error handling macros into calling RoOriginateError when they
// begin logging a new error.  This greatly improves the debuggability of errors that propagate before a failfast.
#include <wil/result_originate.h>
#include <wrl\module.h>
#include <Shlobj.h>
#include <tlhelp32.h>

#include <KozaniRemoteManager_h.h>
#include "KozaniDvc-Constants.h"

using namespace Microsoft::WRL;
using namespace winrt::Windows::Foundation;
using namespace Microsoft::Kozani::DVC;

wil::unique_event g_exitProcess;

struct KozaniApplicationLauncher : winrt::implements<KozaniApplicationLauncher, IKozaniApplicationLauncher>
{
private:
    enum AssociationType
    {
        File = 0,
        Protocol
    };

    const PCWSTR c_registeredPackagedApplicationsPath{ L"SOFTWARE\\RegisteredApplications\\PackagedApps" };
    const PCWSTR c_fileAssociationsKeyName{ L"FileAssociations" };
    const PCWSTR c_protocolAssociationsKeyName{ L"URLAssociations" };

public:
    STDMETHODIMP Launch(_In_ PCWSTR appUserModelId, _In_opt_ PCWSTR arguments, _Out_ DWORD* processId) noexcept try
    {
        RETURN_HR_IF_NULL(E_INVALIDARG, appUserModelId);
        RETURN_HR_IF_NULL(E_INVALIDARG, processId);

        *processId = 0;

#ifdef MEASURE_PERF
        DWORD startTime = GetTickCount();
#endif

        wil::com_ptr<IApplicationActivationManager> aam;
        RETURN_IF_FAILED(CoCreateInstance(CLSID_ApplicationActivationManager, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&aam)));
        RETURN_IF_FAILED(aam->ActivateApplication(appUserModelId, arguments, AO_NONE, processId));

#ifdef MEASURE_PERF
        MessageBox(nullptr, std::format(L"Activation costs - aam: {}ms", GetTickCount() - startTime).c_str(), L"Perf", MB_OK);
#endif

        return S_OK;
    }
    CATCH_RETURN()

    STDMETHODIMP LaunchFiles(
        _In_ PCWSTR appUserModelId,
        _In_ PCWSTR verb,
        UINT32 fileCount,
        _In_count_(fileCount) PCWSTR* filePaths,
        _Inout_ KozaniAppType* appType,
        _Out_ DWORD* processId) noexcept try
    {
        RETURN_HR_IF_NULL(E_INVALIDARG, appUserModelId);
        RETURN_HR_IF_NULL(E_INVALIDARG, processId);
        RETURN_HR_IF_NULL(E_INVALIDARG, filePaths);
        RETURN_HR_IF(E_INVALIDARG, fileCount == 0);

        *processId = 0;

#ifdef MEASURE_PERF
        DWORD aamCost{};
        DWORD shellExeCost{};
        DWORD findProcessCost{};
        DWORD startTime = GetTickCount();
#endif

        // If appType is KozaniAppType_Unknown, we try to activate it as KozaniAppType_PackagedDesktopApp. If we activate a PackagedDesktopApp
        // using IApplicationActivationManager, it will fail and try to repair the registration of the app unnecessarily, also causing forced 
        // shutdown of the app if it is already running.
        if (*appType == KozaniAppType_Unknown || *appType == KozaniAppType_PackagedDesktopApp)
        {
            RETURN_IF_FAILED(ShellExecuteAssociationHandler(appUserModelId, AssociationType::File, filePaths[0], verb, processId));

#ifdef MEASURE_PERF
            shellExeCost = GetTickCount() - startTime;
#endif

            if (*processId == 0)
            {
                // If the app is UWP, ShellExecute will not return its process handle and pid will be 0. Correct the appType so the next time
                // it is launched, we will use the IApplicationActivationManager API, which will return pid for UWPs.
                *appType = KozaniAppType_UWP;

#ifdef MEASURE_PERF
                DWORD findProcessStartTime = GetTickCount();
#endif

                // Try to find the process Id of the process that has the same AUMID as the app we just launched, from all running processes.
                // Best effort only and will not fail the call if we fail to find the pid.
                LOG_IF_FAILED(FindProcessIdFromSnapshot(appUserModelId, processId));

#ifdef MEASURE_PERF
                findProcessCost = GetTickCount() - findProcessStartTime;
#endif
            }
            else if (*appType == KozaniAppType_Unknown)
            {
                *appType = KozaniAppType_PackagedDesktopApp;
            }
        }
        else if (*appType == KozaniAppType_UWP)
        {
            // IApplicationActivationManager file activation only works for UWP apps.
            if (FAILED_LOG(LaunchFilesByActivationManager(appUserModelId, verb, fileCount, filePaths, processId)))
            {
#ifdef MEASURE_PERF
                DWORD aamTime = GetTickCount();
                aamCost = aamTime - startTime;
#endif

                // The incoming appType may not be correct. Fall back to using ShellExecute if LaunchFilesByActivationManager fails.
                // ShellExecute can only launch one file a time. 
                RETURN_IF_FAILED(ShellExecuteAssociationHandler(appUserModelId, AssociationType::File, filePaths[0], verb, processId));
                if (*processId != 0)
                {
                    *appType = KozaniAppType_PackagedDesktopApp;
                }
                else
                {
                    LOG_IF_FAILED(FindProcessIdFromSnapshot(appUserModelId, processId));
                }

#ifdef MEASURE_PERF
                shellExeCost = GetTickCount() - aamTime;
#endif
            }
            else
            {
#ifdef MEASURE_PERF
                aamCost = GetTickCount() - startTime;
#endif
            }
        }
        else
        {
            // Invalid KozaniAppType enum value.
            RETURN_HR(E_INVALIDARG);
        }

#ifdef MEASURE_PERF
        MessageBox(nullptr, std::format(L"Activation costs - aam: {}ms, shellexec: {}ms, FindProcess: {}ms, pid: {}", 
            aamCost, shellExeCost, findProcessCost, *processId).c_str(), L"Perf", MB_OK);
#endif
        return S_OK;
    }
    CATCH_RETURN()

    STDMETHODIMP LaunchUri(_In_ PCWSTR appUserModelId, _In_ PCWSTR uri, _Inout_ KozaniAppType* appType, _Out_ DWORD* processId) noexcept try
    {
        RETURN_HR_IF_NULL(E_INVALIDARG, appUserModelId);
        RETURN_HR_IF_NULL(E_INVALIDARG, uri);
        RETURN_HR_IF_NULL(E_INVALIDARG, processId);

        *processId = 0;

#ifdef MEASURE_PERF
        DWORD aamCost{};
        DWORD shellExeCost{};
        DWORD startTime = GetTickCount();
#endif

        // If appType is KozaniAppType_Unknown, we try to activate it as KozaniAppType_PackagedDesktopApp. If we activate a PackagedDesktopApp
        // using IApplicationActivationManager, it will fail and try to repair the registration of the app unnecessarily, also causing forced 
        // shutdown of the app if it is already running.
        if (*appType == KozaniAppType_Unknown || *appType == KozaniAppType_PackagedDesktopApp)
        {
            RETURN_IF_FAILED(ShellExecuteAssociationHandler(appUserModelId, AssociationType::Protocol, uri, nullptr /* verb */, processId));

#ifdef MEASURE_PERF
            shellExeCost = GetTickCount() - startTime;
#endif

            if (*processId == 0)
            {
                // If the app is UWP, ShellExecute will not return its process handle and pid will be 0. Correct the appType so the next time
                // it is launched, we will use the IApplicationActivationManager API, which will return pid for UWPs.
                *appType = KozaniAppType_UWP;

                // Try to find the process Id of the process that has the same AUMID as the app we just launched, from all running processes.
                // Best effort only and will not fail the call if we fail to find the pid.
                LOG_IF_FAILED(FindProcessIdFromSnapshot(appUserModelId, processId));
            }
        }
        else if (*appType == KozaniAppType_UWP)
        {
            // IApplicationActivationManager protocol activation only works for UWP apps. The reason we don't try IApplicationActivationManager first
            // when the app type is unknown is it will crash the existing running app process if it is not UWP.
            if (FAILED_LOG(LaunchUriByActivationManager(appUserModelId, uri, processId)))
            {
#ifdef MEASURE_PERF
                DWORD aamTime = GetTickCount();
                aamCost = aamTime - startTime;
#endif

                // The incoming appType may not be correct. Fall back to using ShellExecute if LaunchFilesByActivationManager fails.
                RETURN_IF_FAILED(ShellExecuteAssociationHandler(appUserModelId, AssociationType::Protocol, uri, nullptr /* verb */, processId));
                if (*processId != 0)
                {
                    *appType = KozaniAppType_PackagedDesktopApp;
                }
                else
                {
                    LOG_IF_FAILED(FindProcessIdFromSnapshot(appUserModelId, processId));
                }

#ifdef MEASURE_PERF
                shellExeCost = GetTickCount() - aamTime;
#endif
            }
            else
            {
#ifdef MEASURE_PERF
                aamCost = GetTickCount() - startTime;
#endif
            }
        }
        else
        {
            // Invalid KozaniAppType enum value.
            RETURN_HR(E_INVALIDARG);
        }

#ifdef MEASURE_PERF
        MessageBox(nullptr, std::format(L"Activation costs - aam: {}ms, shellexec: {}ms, pid: {}", aamCost, shellExeCost, *processId).c_str(), L"Perf", MB_OK);
#endif
        return S_OK;
    }
    CATCH_RETURN()

    ULONG Release() noexcept override
    {
        ULONG refCount{ winrt::implements<KozaniApplicationLauncher, IKozaniApplicationLauncher>::Release() };
        if (refCount == 0)
        {
            g_exitProcess.SetEvent();
        }
        return refCount;
    }

private:
    HRESULT LaunchFilesByActivationManager(
        _In_ PCWSTR appUserModelId,
        _In_ PCWSTR verb,
        UINT32 fileCount,
        _In_count_(fileCount) PCWSTR* filePaths,
        _Out_ DWORD* processId) noexcept try
    {
        wil::com_ptr<IApplicationActivationManager> aam;
        RETURN_IF_FAILED(CoCreateInstance(CLSID_ApplicationActivationManager, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&aam)));

        wistd::unique_ptr<PIDLIST_ABSOLUTE> filePathList(new PIDLIST_ABSOLUTE[fileCount]);
        RETURN_IF_NULL_ALLOC(filePathList);

        PIDLIST_ABSOLUTE* pidlistFilePaths{ filePathList.get() };
        ZeroMemory(pidlistFilePaths, sizeof(PIDLIST_ABSOLUTE)* fileCount);

        auto freeFilePathList{ wil::scope_exit([&]()
        {
            for (UINT32 i = 0; i < fileCount; i++)
            {
                if (pidlistFilePaths[i])
                {
                    CoTaskMemFree(pidlistFilePaths[i]);
                }
            }
        }) };

        for (UINT32 i = 0; i < fileCount; i++)
        {
            RETURN_IF_FAILED(SHParseDisplayName(filePaths[i], nullptr, &pidlistFilePaths[i], 0, nullptr));
        }

        wil::com_ptr<IShellItemArray> filePathArray;
        RETURN_IF_FAILED(SHCreateShellItemArrayFromIDLists(fileCount, const_cast<LPCITEMIDLIST*>(pidlistFilePaths), &filePathArray));

        RETURN_IF_FAILED(aam->ActivateForFile(appUserModelId, filePathArray.get(), verb, processId));
        return S_OK;
    }
    CATCH_RETURN()

    HRESULT LaunchUriByActivationManager(_In_ PCWSTR appUserModelId, _In_ PCWSTR uri, _Out_ DWORD* processId) noexcept try
    {
        wil::com_ptr<IApplicationActivationManager> aam;
        RETURN_IF_FAILED(CoCreateInstance(CLSID_ApplicationActivationManager, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&aam)));

        wil::com_ptr<IShellItem> shellItem;
        RETURN_IF_FAILED(SHCreateItemFromParsingName(uri, nullptr, IID_PPV_ARGS(&shellItem)));

        wil::com_ptr<IShellItemArray> shellItemArray;
        RETURN_IF_FAILED(SHCreateShellItemArrayFromShellItem(shellItem.get(), IID_PPV_ARGS(&shellItemArray)));

        RETURN_IF_FAILED(aam->ActivateForProtocol(appUserModelId, shellItemArray.get(), processId));
        
        return S_OK;
    }
    CATCH_RETURN()

    std::wstring GetAppAssociationProgId(
        _In_ PCWSTR appUserModelId,
        AssociationType associationType,
        _In_ PCWSTR associationKeyword)
    {
        wil::unique_hkey appsKey;
        THROW_IF_WIN32_ERROR(RegOpenKeyEx(HKEY_CURRENT_USER, c_registeredPackagedApplicationsPath, 0, KEY_READ, wil::out_param(appsKey)));

        std::wstring stringValue;
        stringValue.resize(MAX_PATH);

        // The PackagedApps key contains AUMID -> AssociaitonInfoRegPath key/value pairs. We can look up the path to the registry key storing the 
        // app's association info by its AUMID. For example:
        // Microsoft.SkypeApp_kzf8qxf38zg5c!App = Software\Classes\Local Settings\Software\Microsoft\Windows\CurrentVersion\AppModel\Repository\Packages\Microsoft.SkypeApp_15.99.3202.0_x64__kzf8qxf38zg5c\App\Capabilities
        DWORD bufferSize{ static_cast<DWORD>(stringValue.size() * sizeof(wchar_t)) };
        THROW_IF_WIN32_ERROR(RegGetValue(appsKey.get(), nullptr, appUserModelId, RRF_RT_REG_SZ, nullptr, stringValue.data(), &bufferSize));

        // Under the association info key, there are subkeys based on association types. Each assocation type subkey contains AssociationKeyword -> ProgId key/value pairs.
        // For example:
        // ...\Capabilities
        //          \FileAssociations
        //                 .txt = AppX4ztfk9wxr86nxmzzq47px0nh0e58b8fw
        //          \URLAssociations
        //                  tel = AppX5mseefwz6s981bhyy79d4wwmcper2jyg
        wil::unique_hkey associationInfoKey;
        THROW_IF_WIN32_ERROR(RegOpenKeyEx(HKEY_CURRENT_USER, stringValue.c_str(), 0, KEY_READ, wil::out_param(associationInfoKey)));

        stringValue.clear();
        stringValue.resize(MAX_PATH);
        PCWSTR associationTypeKeyName{ (associationType == AssociationType::File) ? c_fileAssociationsKeyName : c_protocolAssociationsKeyName };
        THROW_IF_WIN32_ERROR(RegGetValue(associationInfoKey.get(), associationTypeKeyName, associationKeyword, RRF_RT_REG_SZ, nullptr, stringValue.data(), &bufferSize));
        
        return stringValue;
    }

    HRESULT ShellExecuteAssociationHandler(
        _In_ PCWSTR appUserModelId,
        AssociationType associationType,
        _In_ PCWSTR launchTarget,
        _In_opt_ PCWSTR verb,
        _Out_ DWORD* processId) noexcept try
    {
        std::wstring associationKeyword;
        if (associationType == AssociationType::File)
        {
            associationKeyword = std::filesystem::path(launchTarget).extension();
        }
        else
        {
            PCWSTR schemeEnd{ wcschr(launchTarget, L':') };
            RETURN_HR_IF_NULL_MSG(E_INVALIDARG, schemeEnd, "Invalid URI: %ls", launchTarget);

            associationKeyword.assign(launchTarget, schemeEnd - launchTarget);
        }

        std::wstring progId{ GetAppAssociationProgId(appUserModelId, associationType, associationKeyword.c_str()) };

        SHELLEXECUTEINFO shellExecuteInfo{};
        shellExecuteInfo.cbSize = sizeof(shellExecuteInfo);
        shellExecuteInfo.fMask = SEE_MASK_NOASYNC | SEE_MASK_NOCLOSEPROCESS | SEE_MASK_CLASSNAME;
        shellExecuteInfo.lpVerb = verb;
        shellExecuteInfo.lpFile = launchTarget;
        shellExecuteInfo.lpClass = progId.c_str();

        shellExecuteInfo.nShow = SW_SHOWNORMAL;

        RETURN_IF_WIN32_BOOL_FALSE(ShellExecuteEx(&shellExecuteInfo));
        if (shellExecuteInfo.hProcess != nullptr)
        {
            *processId = GetProcessId(shellExecuteInfo.hProcess);
            RETURN_LAST_ERROR_IF(*processId == 0);
        }

        return S_OK;
    }
    CATCH_RETURN()

    HRESULT FindProcessIdFromSnapshot(_In_ PCWSTR appUserModelId, _Out_ DWORD* processId) noexcept try
    {
        PROCESSENTRY32 entry;
        entry.dwSize = sizeof(PROCESSENTRY32);

        wil::unique_handle snapshot{ CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0) };
        RETURN_LAST_ERROR_IF(!snapshot);

        RETURN_IF_WIN32_BOOL_FALSE(Process32First(snapshot.get(), &entry));

        wchar_t aumidBuffer[APPLICATION_USER_MODEL_ID_MAX_LENGTH]{};
        do
        {
            wil::unique_handle process{ OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, entry.th32ProcessID) };
            if (process)
            {
                wil::unique_handle token;
                if (OpenProcessToken(process.get(), TOKEN_QUERY, &token))
                {
                    UINT32 aumidBufferLength = ARRAYSIZE(aumidBuffer);
                    if (ERROR_SUCCESS == GetApplicationUserModelIdFromToken(token.get(), &aumidBufferLength, aumidBuffer))
                    {
                        if (_wcsicmp(appUserModelId, aumidBuffer) == 0)
                        {
                            *processId = entry.th32ProcessID;
                            return S_OK;
                        }
                    }
                }
            }
        }
        while (Process32Next(snapshot.get(), &entry));

        RETURN_WIN32(ERROR_NOT_FOUND);
    }
    CATCH_RETURN()
};

int main(int argc, char* argv[]) try
{
    // Hook up wil logging MACROs to trace provider.
    wil::SetResultLoggingCallback(&TraceFailureFromProvider<Microsoft_Kozani_RemoteManagerLauncher_TraceLogger>);

    if (argc < 3)
    {
        return E_INVALIDARG;
    }

    if (_stricmp(argv[1], Constants::ConnectionIdSwitch) != 0)
    {
        return E_INVALIDARG;
    }

    auto uninitOnExit = wil::CoInitializeEx();

    g_exitProcess.create();

    auto appLauncher{ winrt::make_self<KozaniApplicationLauncher>() };

    PCSTR connectionId = argv[2];
    auto remoteManager = wil::CoCreateInstance<KozaniRemoteManager, IKozaniRemoteManager>(CLSCTX_LOCAL_SERVER);
    RETURN_IF_FAILED(remoteManager->Connect(connectionId, appLauncher.get()));

    appLauncher = nullptr;

    // Wait up to 30s for KozaniRemoteManager to call back to activate app before exiting the process. 
    // If the KozaniApplicationLauncher object this process handed out is released earlier than that it will exit sooner.
    g_exitProcess.wait(30000);

    // If a debugger is attached to this process, wait forever so it does not terminate the process during debugging.
    if (IsDebuggerPresent())
    {
        g_exitProcess.wait(INFINITE);
    }

    return S_OK;
}
CATCH_RETURN()
