// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <pch.h>
#include <AppInstance.h>
#include <Microsoft.Windows.AppLifecycle.AppInstance.g.cpp>

#include "ActivationRegistrationManager.h"
#include "LaunchActivatedEventArgs.h"
#include "ProtocolActivatedEventArgs.h"
#include "FileActivatedEventArgs.h"
#include "Association.h"
#include "ExtensionContract.h"
#include "GetRawNotificationEventArgs.h"

using namespace winrt;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::ApplicationModel::Activation;

namespace winrt::Microsoft::Windows::AppLifecycle::implementation
{
    INIT_ONCE AppInstance::s_initOnce{};
    winrt::com_ptr<AppInstance> AppInstance::s_current;

    std::tuple<std::wstring, std::wstring> ParseCommandLine(const std::wstring& commandLine)
    {
        auto argsStart = commandLine.rfind(c_argumentPrefix);
        if (argsStart == std::wstring::npos)
        {
            return { L"", L"" };
        }

        // Push past the '----' commandline argument prefix.
        argsStart += 4;

        auto argsEnd = commandLine.find_first_of(L" ", argsStart);

        // Separate the argument from any behind it on the command-line.
        std::wstring argument;
        if (argsEnd == std::wstring::npos)
        {
            argument = commandLine.substr(argsStart);
        }
        else
        {
            if (argsStart > argsEnd)
            {
                throw std::invalid_argument("commandLine");
            }

            argument = commandLine.substr(argsStart, (argsEnd - argsStart));
        }

        // We explicitly use find_first_of here, so that the resulting data may contain : as a valid character.
        auto argsDelim = argument.find_first_of(L":");
        if (argsDelim == std::wstring::npos)
        {
            return { argument, L"" };
        }

        return { argument.substr(0, argsDelim), argument.substr(argsDelim + 1) };
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
            auto onInstanceTerminated = [weak_this]
            {
                auto strong_this{ weak_this.get() };
                if (strong_this)
                {
                    strong_this->OnInstanceTerminated();
                }
            };

            m_terminationWatcher.create(m_instanceHandle.get(), onInstanceTerminated);
        }

        m_redirectionArgs.Init(m_processName + L"_RedirectionQueue");
    }

    void AppInstance::OnInstanceTerminated()
    {
        auto releaseOnExit = m_dataMutex.acquire();
        m_instances.Remove(m_processId);
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
            cleanupEvent.open(eventName.c_str());
            if (cleanupEvent)
            {
                // If the event is missing, it means the waiter gave up.  Ignore the error.
                cleanupEvent.SetEvent();
            }
        }
    }

    IAsyncAction AppInstance::QueueRequest(AppLifecycle::AppActivationArguments args)
    {
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

        // Enqueue the request and signal the other instance.
        EnqueueRedirectionRequestId(id);
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
        // Try to register and return the current instance.  If we fail to do that, then
        // search and find the correct instance.
        if (s_current->TrySetKey(key.c_str()))
        {
            // Register the class as owning the key, and return it.
            return s_current.as<AppLifecycle::AppInstance>();
        }

        return s_current->FindForKey(key.c_str());
    }

    void AppInstance::UnregisterKey()
    {
        auto releaseOnExit = m_dataMutex.acquire();
        m_key.Reset();
        m_keyCreationMutex.reset();
    }

    AppLifecycle::AppActivationArguments AppInstance::GetActivatedEventArgs()
    {
        ExtendedActivationKind kind = ExtendedActivationKind::Launch;
        IInspectable data;
        bool foundArgs = false;

        // For packaged, try to get platform args first.
        if (HasIdentity())
        {
            if (auto args = winrt::Windows::ApplicationModel::AppInstance::GetActivatedEventArgs())
            {
                data = args;
                kind = static_cast<ExtendedActivationKind>(args.Kind());
                foundArgs = true;
            }
        }

        // Handle all Reunion types next (both packaged and unpackaged).
        std::wstring commandLine = std::wstring(GetCommandLine());
        if (!foundArgs)
        {
            auto [contractArgument, contractData] = ParseCommandLine(commandLine);

            // All specific launch types are encoded as a URI and transported as a
            // protocol, except the catch-all LaunchActivatedEventArgs case.
            if (!contractArgument.empty())
            {
                if (contractData.empty())
                {
                    // If the contractData is empty, handle any aliased encoded launches.
                    if (CompareStringOrdinal(contractArgument.data(), static_cast<int>(contractArgument.size()), L"ReunionPushServer", -1, TRUE) == CSTR_EQUAL)
                    {
                        contractData = GenerateEncodedLaunchUri(L"App", c_pushContractId);
                        contractArgument = c_protocolArgumentString;
                    }
                }

                if (CompareStringOrdinal(contractArgument.c_str(), -1, c_protocolArgumentString, -1, TRUE) == CSTR_EQUAL)
                {
                    kind = ExtendedActivationKind::Protocol;
                    auto args = make<ProtocolActivatedEventArgs>(contractData);
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

                    foundArgs = true;
                }
            }
        }

        // All scenarios should just be marked as Launch.
        if (!foundArgs)
        {
            kind = ExtendedActivationKind::Launch;
            data = make<LaunchActivatedEventArgs>(commandLine);
        }

        return make<AppActivationArguments>(kind, data);
    }

    hstring AppInstance::Key()
    {
        return winrt::hstring(m_key.Get());
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
        std::wstring mutexName = m_moduleName + L"_Mutex";

        // We keep the mutex as a live member to ensure all other instances continue
        // to get an 'open' instead of a 'create' due to it already existing.
        m_keyCreationMutex.create(mutexName.c_str(), 0, MUTEX_ALL_ACCESS);

        bool currentIsKeyOwner = (GetLastError() != ERROR_ALREADY_EXISTS);
        if (currentIsKeyOwner)
        {
            // m_keyCreationMutex is only used to synchronize the owner of the key.  Data access
            // is still protected by m_dataMutex.
            auto releaseOnExit = m_dataMutex.acquire();

            m_key.Resize((key.length() + 1) * sizeof(key.data()[0]));
            THROW_IF_FAILED(StringCchCopy(m_key.Get(), (m_key.Size() / sizeof(wchar_t)), key.c_str()));
        }
        return currentIsKeyOwner;
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
