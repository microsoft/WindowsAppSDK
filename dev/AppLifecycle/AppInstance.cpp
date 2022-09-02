// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>
#include <AppInstance.h>
#include <Microsoft.Windows.AppLifecycle.AppInstance.g.cpp>

#include "AppLifecycleTelemetry.h"
#include "ActivationRegistrationManager.h"
#include "LaunchActivatedEventArgs.h"
#include "ProtocolActivatedEventArgs.h"
#include "FileActivatedEventArgs.h"
#include "Association.h"
#include "ExtensionContract.h"
#include "PushNotificationManager.h"
#include "AppNotificationManager.h"

using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::ApplicationModel::Activation;
using winrt::Windows::ApplicationModel::Core::AppRestartFailureReason;

using namespace AppModel::Identity;

using namespace std::filesystem;

namespace winrt::Microsoft::Windows::AppLifecycle::implementation
{
    static PCWSTR c_pushPayloadAttribute{ L"-Payload:" };

    INIT_ONCE AppInstance::s_initOnce{};
    winrt::com_ptr<AppInstance> AppInstance::s_current;

    std::tuple<std::wstring, std::wstring> GetActivationArguments(PWSTR argv[], int argc, PCWSTR activationKind)
    {
        for (int index = 0; index < argc; index++)
        {
            std::wstring_view fullArgument = argv[index];
            auto protocolQualifier = wil::str_printf<std::wstring>(L"%s%s%s", c_argumentPrefix, activationKind, c_argumentSuffix);

            auto argStart = fullArgument.find(protocolQualifier);
            if (argStart == std::wstring::npos)
            {
                continue;
            }

            // Push past the '----' commandline argument prefix.
            argStart += 4;

            std::wstring argument{ fullArgument.substr(argStart) };

            // We explicitly use find_first_of here, so that the resulting data may contain : as a valid character.
            auto argsDelim = argument.find_first_of(L':');
            if (argsDelim == std::wstring::npos)
            {
                return { argument, L"" };
            }

            return { argument.substr(0, argsDelim), argument.substr(argsDelim + 1) };
        }

        return { L"", L""};
    }

    std::tuple<std::wstring, std::wstring> ParseCommandLine(const std::wstring& commandLine)
    {
        int argc{};

        wil::unique_hlocal_ptr<PWSTR[]> argv{ CommandLineToArgvW(commandLine.c_str(), &argc) };

        PCWSTR activationKinds[] = { c_msProtocolArgumentString, c_pushProtocolArgumentString, c_appNotificationProtocolArgumentString };

        for (auto activationKind : activationKinds)
        {
            auto [ kind, data ] = GetActivationArguments(argv.get(), argc, activationKind);
            if (kind != L"")
            {
                return { kind, data };
            }
        }

        return { L"", L"" };
    }

    std::tuple<ExtendedActivationKind, winrt::Windows::Foundation::IInspectable> GetEncodedLaunchActivatedEventArgs(IProtocolActivatedEventArgs const& args)
    {
        auto [kind, data] = DecodeActivatedEventArgs(args.Uri());

        // Let the caller args pass through if nothing was determined here.
        if (data == nullptr)
        {
            data = args;
        }

        return { kind, data };
    }

    AppInstance::AppInstance(uint32_t processId)
    {
        m_processId = processId;
        m_isCurrent = (GetCurrentProcessId() == processId);

        m_moduleName = ComputeAppId();
        m_processName = wil::str_printf<std::wstring>(L"%s_%d", m_moduleName.c_str(), processId);

        m_instances.Init(m_moduleName + L"_Module");

        // Wire up the Activated event.
        std::wstring eventName = m_processName + c_activatedEventNameSuffix;
        m_innerActivated.create(wil::EventOptions::ManualReset, eventName.c_str());

        // This mutex should always be created first by the process it's associated with.
        std::wstring mutexName = m_processName + L"_Mutex";
        m_dataMutex.create(mutexName.c_str(), CREATE_MUTEX_INITIAL_OWNER, MUTEX_ALL_ACCESS);

        wil::mutex_release_scope_exit releaseOnExit;
        auto weak_this = get_weak();
        if (m_isCurrent)
        {
            releaseOnExit = m_dataMutex.ReleaseMutex_scope_exit();

            auto onInnerActivated = [weak_this]
            {
                // If this weak ref doesn't resolve it means the process is heading toward a terminal state.
                // If that happens just ignore any redirections as they can't be serviced.
                auto strong_this{ weak_this.get() };
                if (strong_this)
                {
                    strong_this->ProcessRedirectionRequests();
                }
            };

            m_activationWatcher.create(m_innerActivated.get(), onInnerActivated);
        }
        else
        {
            releaseOnExit = m_dataMutex.acquire();
        }

        m_key.Open(m_processName + L"_Key");

        if (m_isCurrent)
        {
            m_instances.Insert(processId);
        }
        else
        {
            m_instanceHandle.reset(OpenProcess(SYNCHRONIZE, FALSE, processId));

            // Create a monitor thread to handle cleaning up this instance if the backing process terminates.
            auto onInstanceTerminated = [](_In_ void* context, _In_ BOOLEAN /*reason*/) -> void
            {
                uint32_t processId{ static_cast<uint32_t>(reinterpret_cast<size_t>(context)) };
                GetCurrent().as<AppInstance>()->RemoveInstance(processId);
            };

            THROW_IF_WIN32_BOOL_FALSE(RegisterWaitForSingleObject(&m_terminationWatcherWaitHandle, m_instanceHandle.get(), onInstanceTerminated,
                reinterpret_cast<void*>(static_cast<size_t>(m_processId)), INFINITE, WT_EXECUTEONLYONCE));
        }

        m_redirectionArgs.Init(m_processName + L"_RedirectionQueue");
    }

    void AppInstance::RemoveInstance(uint32_t processId)
    {
        auto releaseOnExit = m_dataMutex.acquire();
        m_instances.Remove(processId);
    }

    GUID AppInstance::DequeueRedirectionRequestId()
    {
        auto releaseOnExit = m_dataMutex.acquire();
        auto id = m_redirectionArgs.Dequeue();
        return id;
    }

    void AppInstance::EnqueueRedirectionRequestId(GUID id)
    {
        auto releaseOnExit = m_dataMutex.acquire();
        m_redirectionArgs.Enqueue(id);
    }

    void AppInstance::ProcessRedirectionRequests()
    {
        m_innerActivated.ResetEvent();

        GUID id;
        while ((id = DequeueRedirectionRequestId()) != GUID_NULL)
        {
            wil::unique_cotaskmem_string idString;
            THROW_IF_FAILED(StringFromCLSID(id, &idString));

            auto name = wil::str_printf<std::wstring>(c_requestPacketNameFormat, m_processName.c_str(), idString.get());

            RedirectionRequest request;
            request.Open(name);
            auto args = request.UnmarshalArguments();

            // Notify the app that the redirection request is here.
            m_activatedEvent(*this, args);

            std::wstring eventName = name + c_activatedEventNameSuffix;
            wil::unique_event cleanupEvent;
            if (cleanupEvent.try_open(eventName.c_str()))
            {
                // If the event is missing, it means the waiter gave up.  Ignore the error.
                cleanupEvent.SetEvent();
            }
        }
    }

    IAsyncAction AppInstance::QueueRequest(AppLifecycle::AppActivationArguments args)
    {
        // Report feature usage.
        static bool featureUsageReported{ false };
        if (!featureUsageReported)
        {
            AppLifecycleTelemetry::RedirectActivationToAsync();
            featureUsageReported = true;
        }

        auto strongThis{ get_strong() };

        // Push this work onto a background thread.
        co_await resume_background();

        auto uninitOnExit = wil::CoInitializeEx();

        GUID id;
        THROW_IF_FAILED(CoCreateGuid(&id));

        wil::unique_cotaskmem_string idString;
        THROW_IF_FAILED(StringFromCLSID(id, &idString));
        auto name = wil::str_printf<std::wstring>(c_requestPacketNameFormat, m_processName.c_str(), idString.get());

        RedirectionRequest request;
        request.Open(name);
        request.MarshalArguments(args);

        std::wstring eventName = name + c_activatedEventNameSuffix;
        wil::unique_event cleanupEvent;
        cleanupEvent.create(wil::EventOptions::ManualReset, eventName.c_str());

        // Enqueue the request and transfer foreground rights.
        EnqueueRedirectionRequestId(id);
        AllowSetForegroundWindow(m_processId);

        // Signal the activation.
        m_innerActivated.SetEvent();

        // Wait for the other instance to open the memory mapped file before exiting and cleaning our interest in it.
        cleanupEvent.wait();
        co_return;
    }

    IAsyncAction AppInstance::RedirectActivationToAsync(AppLifecycle::AppActivationArguments const& args)
    {
        if (!m_isCurrent)
        {
            co_await QueueRequest(args);
        }
    }

    Microsoft::Windows::AppLifecycle::AppInstance AppInstance::GetCurrent()
    {
        auto initInstance = []
        {
            s_current = winrt::make_self<AppInstance>(GetCurrentProcessId());
        };

        wil::init_once(s_initOnce, initInstance);

        return s_current.as<Microsoft::Windows::AppLifecycle::AppInstance>();
    }

    IVector<Microsoft::Windows::AppLifecycle::AppInstance> AppInstance::GetInstances()
    {
        // Force the singleton init.
        GetCurrent();

        IVector<Microsoft::Windows::AppLifecycle::AppInstance> instances{ winrt::single_threaded_vector<Microsoft::Windows::AppLifecycle::AppInstance>() };

        // Grab the list of processes while under the lock, and then drop it since we'll be calling out to other code.
        std::list<DWORD> pids;
        {
            auto releaseOnExit = s_current->m_dataMutex.acquire();

            for (uint32_t index = 0; index < s_current->m_instances.Size(); index++)
            {
                auto pid = s_current->m_instances[index];
                if (pid == 0)
                {
                    continue;
                }

                pids.push_back(pid);
            }
        }

        // Create the associated AppInstance objects while removing orphaned entries we find.
        for (const auto& pid : pids)
        {
            if (GetCurrentProcessId() == pid)
            {
                instances.Append(AppInstance::GetCurrent());
            }
            else
            {
                wil::unique_handle process(::OpenProcess(PROCESS_QUERY_LIMITED_INFORMATION, FALSE, pid));
                if (process != nullptr)
                {
                    instances.Append(make<AppInstance>(pid));
                }
                else
                {
                    // Remove orphan.
                    auto releaseOnExit = s_current->m_dataMutex.acquire();
                    s_current->m_instances.Remove(pid);
                }
            }
        }

        return instances;
    }

    AppLifecycle::AppInstance AppInstance::FindOrRegisterForKey(hstring const& key)
    {
        // Force the singleton init.
        GetCurrent();

        // Try to register and return the current instance.  If we fail to do that, then
        // search and find the correct instance.
        if (s_current->TrySetKey(key.c_str()))
        {
            return GetCurrent();
        }

        return s_current->FindForKey(key.c_str());
    }

    std::wstring AppInstance::GenerateRestartAgentPath()
    {
        // Calculate the path to the restart agent as being in the same directory as the current module.
        wil::unique_hmodule module;
        THROW_IF_WIN32_BOOL_FALSE(GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, reinterpret_cast<PCWSTR>(AppInstance::GenerateRestartAgentPath), &module));

        path modulePath = wil::GetModuleFileNameW<std::wstring>(module.get());
        return modulePath.parent_path() / c_restartAgentFilename;
    }

    AppRestartFailureReason AppInstance::Restart(hstring const& arguments)
    {
        // Report feature usage.
        static bool featureUsageReported{ false };
        if (!featureUsageReported)
        {
            AppLifecycleTelemetry::Restart();
            featureUsageReported = true;
        }

        // If a better way of detecting UWP is created in the future, this check should change.
        if (IsPackagedProcess() && wil::get_token_is_app_container())
        {
            // For UWP, redirect to the already existing API.  
            return winrt::Windows::ApplicationModel::Core::CoreApplication::RequestRestartAsync(arguments).get();
        }

        // Remaining scenarios that flow through this code should be only be win32 (including Desktop Bridge which is packaged).

        // Only one restart can happen at a time.
        auto mutexName = wil::str_printf<std::wstring>(L"%s_RequestRestartNowInProgress", ComputeAppId().c_str());
        wil::unique_mutex restartMutex;

        restartMutex.create(mutexName.c_str(), CREATE_MUTEX_INITIAL_OWNER, MUTEX_ALL_ACCESS);
        if (GetLastError() == ERROR_ALREADY_EXISTS)
        {
            return AppRestartFailureReason::RestartPending;
        }

        auto releaseOnExit{ restartMutex.ReleaseMutex_scope_exit() };

        // Use DuplicateHandle to get a real handle from the pseudo-handle returned by GetCurrentProcess().  A real handle
        // is required in order for it to be inherited 
        wil::unique_handle parentHandle;
        THROW_IF_WIN32_BOOL_FALSE(DuplicateHandle(GetCurrentProcess(), GetCurrentProcess(), GetCurrentProcess(), wil::out_param(parentHandle), 
            PROCESS_QUERY_LIMITED_INFORMATION | SYNCHRONIZE | PROCESS_TERMINATE, TRUE, 0));

        auto exePath = GenerateRestartAgentPath();

        // c:\currentdirectory\restartagent.exe <inherited handle id of calling process> <custom arguments passed by caller>
        auto cmdLine = wil::str_printf<wil::unique_cotaskmem_string>(L"\"%s\" %d %s", exePath.c_str(), parentHandle.get(), arguments.c_str());

        SIZE_T attributeListSize{ 0 };
        auto attributeCount{ 1 };

        if (IsPackagedProcess())
        {
            // Packaged scenarios have an additional attribute.
            attributeCount++;
        }

        THROW_HR_IF(E_UNEXPECTED, InitializeProcThreadAttributeList(nullptr, attributeCount, 0, &attributeListSize));
        THROW_LAST_ERROR_IF(GetLastError() != ERROR_INSUFFICIENT_BUFFER);

        wil::unique_process_heap_ptr<_PROC_THREAD_ATTRIBUTE_LIST> attributeList(reinterpret_cast<PPROC_THREAD_ATTRIBUTE_LIST> (HeapAlloc(GetProcessHeap(), 0, attributeListSize)));
        THROW_IF_NULL_ALLOC(attributeList);

        THROW_IF_WIN32_BOOL_FALSE(InitializeProcThreadAttributeList(attributeList.get(), attributeCount, 0, &attributeListSize));
        auto freeAttributeList = wil::scope_exit([&] { DeleteProcThreadAttributeList(attributeList.get()); });

        // Launch the restart agent and explicitly inherit the current process' handle to it.  This allows the restart agent to
        // sniff out the exact path of the caller executable in a sane way.
        size_t handlesToInheritCount{ 1 };
        HANDLE* handlesToInherit = reinterpret_cast<HANDLE*>(parentHandle.addressof());
        THROW_IF_WIN32_BOOL_FALSE(UpdateProcThreadAttribute(attributeList.get(), 0, PROC_THREAD_ATTRIBUTE_HANDLE_LIST, handlesToInherit, 
            handlesToInheritCount * sizeof(HANDLE), nullptr, nullptr));

        if (IsPackagedProcess())
        {
            // Desktop Bridge applications by default have their child processes break away from the parent process.  In order to recreate the calling process'
            // environment correctly, this code must prevent child breakaway semantics when calling the agent.  Additionally the agent must do the same when
            // restarting the caller.
            DWORD policy = PROCESS_CREATION_DESKTOP_APP_BREAKAWAY_OVERRIDE;
            THROW_IF_WIN32_BOOL_FALSE(UpdateProcThreadAttribute(attributeList.get(), 0, PROC_THREAD_ATTRIBUTE_DESKTOP_APP_POLICY, &policy, sizeof(policy), nullptr, nullptr));
        }

        STARTUPINFOEX info{};
        info.StartupInfo.cb = sizeof(info);
        info.lpAttributeList = attributeList.get();
        
        wil::unique_process_information processInfo;
        THROW_IF_WIN32_BOOL_FALSE(CreateProcess(exePath.c_str(), cmdLine.get(), nullptr, nullptr, TRUE, CREATE_SUSPENDED | EXTENDED_STARTUPINFO_PRESENT, nullptr, nullptr,
            &info.StartupInfo, &processInfo));

        // Transfer foreground rights to the new process before resuming it.
        AllowSetForegroundWindow(processInfo.dwProcessId);
        ResumeThread(processInfo.hThread);

        // This API is designed to only return to the caller on failure, otherwise block until process termination.
        // Wait for the agent to exit.  If the agent succeeds, it will terminate this process.  If the agent fails,
        // it can exit or crash.  This API will be able to detect the failure and return.
        wil::handle_wait(processInfo.hProcess);

        // We should never reach here if the API succeeds, as the agent should have terminated the current process.
        return AppRestartFailureReason::Other;
    }

    void AppInstance::UnregisterKey()
    {
        auto releaseOnExit = m_dataMutex.acquire();
        if (m_isCurrent)
        {
            m_key.Reset();
            m_keyCreationMutexLock.reset();
            m_keyCreationMutex.reset();
        }
    }

    AppLifecycle::AppActivationArguments AppInstance::GetActivatedEventArgs()
    {
        ExtendedActivationKind kind = ExtendedActivationKind::Launch;
        IInspectable data;

        // Report feature usage.
        static bool featureUsageReported{ false };
        if (!featureUsageReported)
        {
            AppLifecycleTelemetry::GetActivatedEventArgs();
            featureUsageReported = true;
        }

        // For packaged, try to get platform args first.
        if (IsPackagedProcess())
        {
            if (auto args = winrt::Windows::ApplicationModel::AppInstance::GetActivatedEventArgs())
            {
                data = args;
                kind = static_cast<ExtendedActivationKind>(args.Kind());
            }
        }

        // Handle all Windows App SDK types next (both packaged and unpackaged).
        std::wstring commandLine{ GetCommandLine() };
        if (data == nullptr)
        {
            auto [contractArgument, contractData] = ParseCommandLine(commandLine);

            // All specific launch types are encoded as a URI and transported as a
            // protocol, except the catch-all LaunchActivatedEventArgs case.
            if (!contractArgument.empty())
            {
                if (contractArgument == c_pushProtocolArgumentString || contractArgument == c_appNotificationProtocolArgumentString)
                {
                    // Generate a basic encoded launch Uri for Push/Toast activations
                    PCWSTR contractId = (contractArgument == c_pushProtocolArgumentString) ? c_pushContractId : c_appNotificationContractId;
                    std::wstring tempContractData = GenerateEncodedLaunchUri(L"App", contractId);

                    contractArgument = c_msProtocolArgumentString;

                    // A non-empty contractData means we have a payload.
                    // This contains a background notification. It is specific to unpackaged apps.
                    // It requires further processing to build PushNotificationReceivedEventArgs.
                    // For packaged apps we don't need extra processing. A basic encoded launch Uri is sufficient.
                    auto index = contractData.find(c_pushPayloadAttribute);

                    if (!contractData.empty() && index == 0)
                    {
                        tempContractData += L"&payload=";
                        // 9 -> the size of &payload= as quotes in the contrat data will
                        // have been tripped in the call to ParseCommandLine.
                        tempContractData += contractData.substr(9, contractData.size() - 9);
                    }

                    contractData = tempContractData;
                }

                if (CompareStringOrdinal(contractArgument.c_str(), static_cast<int>(contractArgument.size()), c_msProtocolArgumentString, -1, TRUE) == CSTR_EQUAL)
                {
                    kind = ExtendedActivationKind::Protocol;
                    auto args = make<ProtocolActivatedEventArgs>(contractData.c_str());
                    data = args;

                    // Encoded launch is a protocol launch where the argument data is
                    // encapsulated in the Uri Query data.  We handle that here and
                    // try to return the correct IActivatedEventArgs type that is
                    // encoded in the data rather than the IProtocolActivatedEventArgs
                    // itself.
                    if (IsEncodedLaunch(args.Uri()))
                    {
                        std::tie(kind, data) = GetEncodedLaunchActivatedEventArgs(args);
                    }
                }
            }
        }

        // All scenarios should just be marked as Launch.
        if (data == nullptr)
        {
            kind = ExtendedActivationKind::Launch;
            data = make<LaunchActivatedEventArgs>(commandLine.c_str());
        }

        return make<AppActivationArguments>(kind, data);
    }

    hstring AppInstance::Key()
    {
        auto releaseOnExit = m_dataMutex.acquire();

        if (m_key.IsValid())
        {
            return winrt::hstring(m_key.Get());
        }

        return winrt::hstring(L"");
    }


    event_token AppInstance::Activated(EventHandler<Microsoft::Windows::AppLifecycle::AppActivationArguments> const& handler)
    {
        return m_activatedEvent.add(handler);
    }

    void AppInstance::Activated(event_token const& token) noexcept
    {
        m_activatedEvent.remove(token);
    }

    bool AppInstance::TrySetKey(std::wstring const& key)
    {
        auto escapedKey = std::regex_replace(key, std::wregex(L"\\\\"), L"_");
        std::wstring mutexName = wil::str_printf<std::wstring>(L"%s_%s_Mutex", m_moduleName.c_str(), escapedKey.c_str());

        // m_keyCreationMutex is only used to synchronize the owner of the key.  Data access
        // is still protected by m_dataMutex.
        // Acquire m_dataMutex before creating m_keyCreationMutex to avoid
        // processes from seeing the mutex but not seeing the Key on the instance yet.
        auto releaseOnExit = m_dataMutex.acquire();

        // First caller creates the named mutex. All other instances continue
        // to get an 'open' instead of a 'create' due to it already existing.
        wil::unique_mutex keyCreationMutex;
        keyCreationMutex.create(mutexName.c_str(), 0, MUTEX_ALL_ACCESS);

        DWORD waitResult = 0;
        // Wait for 0 seconds. If the mutex is taken we don't own the mutex
        auto lock = keyCreationMutex.acquire(&waitResult, 0);

        if (waitResult != WAIT_TIMEOUT)
        {
            // We acquired the named mutex, store the mutex itself and the lock as a member.
            // We keep the mutex and lock as a live member to ensure it stays alive for
            // as long as we own the mutex
            // NOTE: Assigning the new mutex will release the old one if it exists.
            // Therefore make sure to release the lock first.
            m_keyCreationMutexLock = std::move(lock);
            m_keyCreationMutex = std::move(keyCreationMutex);

            m_key.Resize((key.length() + 1) * sizeof(key.data()[0]));
            THROW_IF_FAILED(StringCchCopy(m_key.Get(), (m_key.Size() / sizeof(wchar_t)), key.c_str()));

            return true;
        }
        return false;
    }

    Microsoft::Windows::AppLifecycle::AppInstance AppInstance::FindForKey(std::wstring const& key)
    {
        auto instances = GetInstances();
        for (const auto& instance : instances)
        {
            if (instance.Key() == key)
            {
                return instance;
            }
        }

        return nullptr;
    }
}
