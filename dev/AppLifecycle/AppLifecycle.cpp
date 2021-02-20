// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <pch.h>
#include <AppLifecycle.h>
#include <AppLifecycle.g.cpp>

#include "LaunchActivatedEventArgs.h"
#include "ProtocolActivatedEventArgs.h"
#include "FileActivatedEventArgs.h"
#include "Association.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::ApplicationModel::Activation;

namespace winrt::Microsoft::ProjectReunion::implementation
{
    std::tuple<std::wstring, std::wstring> ParseCommandLine(std::wstring commandLine)
    {
        auto argsStart = commandLine.rfind(L"----") + 4;
        if (argsStart == std::wstring::npos)
        {
            return { L"", L"" };
        }

        // We explicitly use find_first_of here, so that the resulting data may contain : as a valid character.
        auto argsEnd = commandLine.find_first_of(L":", argsStart);
        if (argsEnd == std::wstring::npos)
        {
            return { L"", L"" };
        }

        if (argsStart > argsEnd)
        {
            throw std::overflow_error("commandLine");
        }

        auto argsLength = argsEnd - argsStart;
        auto dataStart = argsEnd + 1;

        return { commandLine.substr(argsStart, argsLength), commandLine.substr(dataStart) };
    }

    INIT_ONCE AppLifecycle::s_initArgs{};
    IActivatedEventArgs AppLifecycle::s_args;

    AppLifecycle::AppLifecycle(hstring key)
    {
        std::wstring name = key.c_str();

        std::wstring mutexName = name + L"_Mutex";
        m_mutex.create(mutexName.c_str(), CREATE_MUTEX_INITIAL_OWNER, MUTEX_ALL_ACCESS); // TODO: Make sure we release the mutex after initialization.
        m_isCurrentInstance = (GetLastError() != ERROR_ALREADY_EXISTS);

        wil::mutex_release_scope_exit releaseMutexOnExit;
        if (m_isCurrentInstance)
        {
            releaseMutexOnExit = m_mutex.ReleaseMutex_scope_exit();
        }
        else
        {
            releaseMutexOnExit = m_mutex.acquire();
        }

        std::wstring eventName = name + L"_ActivatedEvent";
        m_innerActivated.create(wil::EventOptions::ManualReset, eventName.c_str());

        if (m_isCurrentInstance)
        {
            auto weak_this = get_weak();
            auto onInnerActivated = [weak_this]
            {
                auto strong_this{ weak_this.get() };
                if (strong_this)
                {
                    strong_this->Activate();
                }
            };

            m_activationWatcher.create(m_innerActivated.get(), onInnerActivated);
        }

        std::wstring sharedMemName = name + L"_SharedMemory";
        m_shared.open(sharedMemName);

        if (m_isCurrentInstance)
        {
            m_shared->processId = GetCurrentProcessId();
        }

        printf("Main ProcessId: %d\n", m_shared->processId);

        m_instanceList.open(L"InstanceList"); // TODO: Design a way to have a unique name for the memory of each app that spans all possible keys.

        m_instanceList->count++;
        auto count = m_instanceList->count;

        printf("InstanceCount: %d\n", count);
    }

    void AppLifecycle::Activate()
    {
        m_innerActivated.ResetEvent();
        auto args = UnmarshalArguments();
        m_activatedEvent(*this, args);
    }

    IActivatedEventArgs AppLifecycle::GetActivatedEventArgs()
    {
        if (HasIdentity())
        {
            return Windows::ApplicationModel::AppInstance::GetActivatedEventArgs();
        }
        else
        {
            // Generate IActivatedEventArgs for non-Packaged applications.
            std::wstring contractId;
            std::wstring contractData;
            auto commandLine = std::wstring(GetCommandLine());
            std::tie(contractId, contractData) = ParseCommandLine(commandLine);

            if (!contractId.empty())
            {
                if (contractId == c_protocolArgumentString)
                {
                    return make<ProtocolActivatedEventArgs>(contractData);
                }
                else if (contractId == c_fileArgumentString)
                {
                    return make<FileActivatedEventArgs>(contractData);
                }
            }

            return make<LaunchActivatedEventArgs>(commandLine);
        }
    }

    Microsoft::ProjectReunion::AppLifecycle AppLifecycle::FindOrRegisterInstanceForKey(hstring const& key)
    {
        return make_self<AppLifecycle>(key).as<Microsoft::ProjectReunion::AppLifecycle>();
    }

    IVector<Microsoft::ProjectReunion::AppLifecycle> AppLifecycle::GetRegisteredInstances()
    {
        throw hresult_not_implemented();
    }

    void AppLifecycle::UnregisterInstanceForRedirection()
    {
        throw hresult_not_implemented();
    }

    void AppLifecycle::RedirectActivationTo(IActivatedEventArgs const& args)
    {
        if (!m_isCurrentInstance)
        {
            auto releaseMutexOnExit = m_mutex.acquire();
            MarshalArguments(args);
            m_innerActivated.SetEvent();
        }
    }

    event_token AppLifecycle::Activated(EventHandler<IActivatedEventArgs> const& handler)
    {
        return m_activatedEvent.add(handler);
    }

    void AppLifecycle::Activated(event_token const& token) noexcept
    {
        m_activatedEvent.remove(token);
    }

    bool AppLifecycle::IsCurrentInstance()
    {
        return m_isCurrentInstance;
    }

    hstring AppLifecycle::Key()
    {
        return m_key.c_str();
    }

    void AppLifecycle::MarshalArguments(IActivatedEventArgs const& args)
    {
        com_ptr<IStream> stream;
        THROW_IF_FAILED(CreateStreamOnHGlobal(nullptr, TRUE, stream.put()));

        com_ptr<::IUnknown> unk{ args.as<::IUnknown>() };
        THROW_IF_FAILED(CoMarshalInterface(stream.get(), guid_of<IActivatedEventArgs>(), unk.get(), MSHCTX_LOCAL, nullptr, MSHLFLAGS_NORMAL));

        const LARGE_INTEGER headOffset{};
        auto resetStreamOnExit = wil::scope_exit([&stream, &headOffset]
            {
                stream->Seek(headOffset, STREAM_SEEK_SET, nullptr);
                CoReleaseMarshalData(stream.get());
            });

        THROW_IF_FAILED(stream->Seek(headOffset, STREAM_SEEK_SET, nullptr));

        STATSTG stats{};
        THROW_IF_FAILED(stream->Stat(&stats, STATFLAG_NONAME));
        THROW_HR_IF(E_FAIL, static_cast<ULONG>(stats.cbSize.QuadPart) > sizeof(m_shared->stream));

        ULONG bytesRead{ 0 };
        THROW_IF_FAILED(stream->Read(m_shared->stream, static_cast<ULONG>(stats.cbSize.QuadPart), &bytesRead));
        resetStreamOnExit.release();
    }

    IActivatedEventArgs AppLifecycle::UnmarshalArguments()
    {
        com_ptr<IStream> stream;
        THROW_IF_FAILED(CreateStreamOnHGlobal(nullptr, TRUE, stream.put()));

        ULONG bytesWritten = 0;
        THROW_IF_FAILED(stream->Write(m_shared->stream, sizeof(m_shared->stream), &bytesWritten));

        const LARGE_INTEGER headOffset{};
        THROW_IF_FAILED(stream->Seek(headOffset, STREAM_SEEK_SET, nullptr));

        com_ptr<::IUnknown> unk;
        THROW_IF_FAILED(CoUnmarshalInterface(stream.get(), guid_of<IActivatedEventArgs>(), unk.put_void()));

        return unk.as<IActivatedEventArgs>();
    }
}
