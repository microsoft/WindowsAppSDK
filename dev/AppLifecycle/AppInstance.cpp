// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <pch.h>
#include <AppInstance.h>
#include <Microsoft.ApplicationModel.Activation.AppInstance.g.cpp>

#include "ActivationRegistrationManager.h"
#include "ActivationArguments.h"
#include "LaunchActivatedEventArgs.h"
#include "ProtocolActivatedEventArgs.h"
#include "FileActivatedEventArgs.h"
#include "Association.h"
#include "ExtensionContract.h"

using namespace winrt;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::ApplicationModel::Activation;

namespace winrt::Microsoft::ApplicationModel::Activation::implementation
{
    INIT_ONCE AppInstance::s_initInstance{};
    winrt::com_ptr<AppInstance> AppInstance::s_instance;

    std::tuple<std::wstring, std::wstring> ParseCommandLine(std::wstring commandLine)
    {
        auto argsStart = commandLine.rfind(c_argumentPrefix);
        if (argsStart == std::wstring::npos)
        {
            return { L"", L"" };
        }

        argsStart += 4;

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

    bool IsEncodedLaunch(IProtocolActivatedEventArgs const& args)
    {
        return CompareStringOrdinal(args.Uri().SchemeName().c_str(), -1, c_encodedLaunchSchemeName,
            -1, TRUE) == CSTR_EQUAL;
    }

    IActivatedEventArgs GetEncodedLaunchActivatedEventArgs(IProtocolActivatedEventArgs const& args)
    {
        for (auto const& pair : args.Uri().QueryParsed())
        {
            if (CompareStringOrdinal(pair.Name().c_str(), -1, c_contractIdKeyName, -1, TRUE)
                == CSTR_EQUAL)
            {
                for (int index = 0; index < _countof(c_extensionMap); index++)
                {
                    std::wstring contractId = pair.Value().c_str();
                    if (CompareStringOrdinal(contractId.c_str(), -1,
                        c_extensionMap[index].contractId.c_str(), -1, TRUE) == CSTR_EQUAL)
                    {
                        return c_extensionMap[index].factory(args);
                    }
                }
            }
        }

        // Let the caller args pass through if nothing was determined here.
        return args;
    }

    AppInstance::AppInstance(uint32_t processId)
    {
        std::wstring moduleScopedName = ComputeAppId();
        std::wstring processScopedName = wil::str_printf<std::wstring>(L"%s_%d", moduleScopedName.c_str(), processId);

        // Wire up the Activated event.
        std::wstring eventName = processScopedName + L"_ActivatedEvent";
        m_innerActivated.create(wil::EventOptions::ManualReset, eventName.c_str());

        std::wstring mutexName = processScopedName + L"_Mutex";
        m_dataMutex.create(mutexName.c_str(), CREATE_MUTEX_INITIAL_OWNER, MUTEX_ALL_ACCESS);

        m_isCurrent = (GetLastError() != ERROR_ALREADY_EXISTS);
        assert(m_isCurrent == (!!(GetCurrentProcessId() == processId))); // TODO: Consider throwing here instead?

        wil::mutex_release_scope_exit releaseOnExit;
        if (m_isCurrent)
        {
            releaseOnExit = m_dataMutex.ReleaseMutex_scope_exit();

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
        else
        {
            releaseOnExit = m_dataMutex.acquire();
        }

        m_data.open(processScopedName + L"_Process");
        m_processIds.init(moduleScopedName + L"_Module");

        if (m_isCurrent)
        {
            m_data->processId = processId;
            m_processIds.insert(processId);
        }

        // m_key is a view ontop of the data in m_data->key.
        m_key = m_data->key;
    }

    void AppInstance::Activate()
    {
        m_innerActivated.ResetEvent();
        auto args = UnmarshalArguments();
        m_activatedEvent(*this, args);
    }

    Microsoft::ApplicationModel::Activation::AppInstance AppInstance::GetCurrent()
    {
        auto initInstance = []
        {
            s_instance = winrt::make_self<AppInstance>(GetCurrentProcessId());
        };

        wil::init_once(s_initInstance, initInstance);

        return s_instance.as<Microsoft::ApplicationModel::Activation::AppInstance>();
    }

    IVector<Microsoft::ApplicationModel::Activation::AppInstance> AppInstance::GetInstances()
    {
        IVector<Microsoft::ApplicationModel::Activation::AppInstance> instances{ winrt::single_threaded_vector<Microsoft::ApplicationModel::Activation::AppInstance>() };

        for (uint32_t index = 0; index < s_instance->m_processIds.size(); index++)
        {
            auto pid = s_instance->m_processIds[index];
            if (pid == 0)
            {
                continue;
            }

            if (GetCurrentProcessId() == s_instance->m_processIds[index])
            {
                instances.Append(AppInstance::GetCurrent());
            }
            else
            {
                instances.Append(make<AppInstance>(pid));
            }
        }

        return instances;
    }

    Microsoft::ApplicationModel::Activation::AppInstance AppInstance::FindOrRegisterForKey(hstring const& key)
    {
        // Try to register and return the current instance.  If we fail to do that, then
        // search and find the correct instance.
        if (s_instance->TrySetKey(key.c_str()))
        {
            // Register the class as owning the key, and return it.
            return s_instance.as<Microsoft::ApplicationModel::Activation::AppInstance>();
        }

        return s_instance->FindForKey(key.c_str());
    }

    void AppInstance::UnregisterKey(hstring const& key)
    {
        throw hresult_not_implemented();
    }

    void AppInstance::RedirectTo(Microsoft::ApplicationModel::Activation::ActivationArguments const& args)
    {
        if (!m_isCurrent)
        {
            MarshalArguments(args);
            m_innerActivated.SetEvent();
        }
    }

    ApplicationModel::Activation::ActivationArguments AppInstance::GetActivatedEventArgs()
    {
        ExtendedActivationKind kind = ExtendedActivationKind::Launch;
        IInspectable data;

        if (HasIdentity())
        {
            auto args = Windows::ApplicationModel::AppInstance::GetActivatedEventArgs();
            data = args.as<IInspectable>();
            kind = static_cast<ExtendedActivationKind>(args.Kind());
        }
        else
        {
            // Generate IActivatedEventArgs for non-Packaged applications.
            std::wstring contractId;
            std::wstring contractData;
            auto commandLine = std::wstring(GetCommandLine());
            std::tie(contractId, contractData) = ParseCommandLine(commandLine);

            // All specific launch types are encoded as a URI and transported as a
            // protocol, except the catch-all LaunchActivatedEventArgs case.
            if (!contractId.empty() && (CompareStringOrdinal(contractId.c_str(), -1,
                c_protocolArgumentString, -1, TRUE) == CSTR_EQUAL))
            {
                kind = ExtendedActivationKind::Protocol;
                auto args = make<ProtocolActivatedEventArgs>(contractData);
                data = args.as<IInspectable>();
                
                // Encoded launch is a protocol launch where the argument data is
                // encapsulated in the Uri Query data.  We handle that here and
                // try to return the correct IActivatedEventArgs type that is
                // encoded in the data rather than the IProtocolActivatedEventArgs
                // itself.
                auto protocolArgs = args.as<IProtocolActivatedEventArgs>();
                if (IsEncodedLaunch(protocolArgs))
                {
                    data = GetEncodedLaunchActivatedEventArgs(protocolArgs).as<IInspectable>();
                }
            }

            // Haven't set the kind yet, and so let's default to Launch.
            if (kind == ExtendedActivationKind::Launch)
            {
                data = make<LaunchActivatedEventArgs>(commandLine).as<IInspectable>();
            }
        }

        return make<ActivationArguments>(kind, data);
    }

    event_token AppInstance::Activated(EventHandler<Microsoft::ApplicationModel::Activation::ActivationArguments> const& handler)
    {
        return m_activatedEvent.add(handler);
    }

    void AppInstance::Activated(event_token const& token) noexcept
    {
        m_activatedEvent.remove(token);
    }

    bool AppInstance::TrySetKey(std::wstring const& key)
    {
        std::wstring mutexName = wil::str_printf<std::wstring>(L"%s_%s_Mutex",
            ComputeAppId().c_str(), key.c_str());

        m_keyMutex.create(mutexName.c_str(), 0, MUTEX_ALL_ACCESS);
        bool currentIsKeyOwner = (GetLastError() != ERROR_ALREADY_EXISTS);
        if (currentIsKeyOwner)
        {
            // m_keyMutex is only used to synchronize the owner of the key.  Data access
            // is still protected by m_dataMutex.
            auto releaseOnExit = m_dataMutex.acquire();
            THROW_IF_FAILED(StringCchCopy(m_data->key, _countof(m_data->key), key.c_str()));

            // m_key is a view ontop of the data in m_data->key.
            m_key = m_data->key;
        }
        return currentIsKeyOwner;
    }

    Microsoft::ApplicationModel::Activation::AppInstance AppInstance::FindForKey(std::wstring const& key)
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

    void AppInstance::MarshalArguments(Microsoft::ApplicationModel::Activation::ActivationArguments const& args)
    {
        com_ptr<IStream> stream;
        THROW_IF_FAILED(CreateStreamOnHGlobal(nullptr, TRUE, stream.put()));

        com_ptr<::IUnknown> unk{ args.as<::IUnknown>() };
        THROW_IF_FAILED(CoMarshalInterface(stream.get(), guid_of<ActivationArguments>(), unk.get(), MSHCTX_LOCAL, nullptr, MSHLFLAGS_NORMAL));

        const LARGE_INTEGER headOffset{};
        auto resetStreamOnExit = wil::scope_exit([&stream, &headOffset]
            {
                stream->Seek(headOffset, STREAM_SEEK_SET, nullptr);
                CoReleaseMarshalData(stream.get());
            });

        THROW_IF_FAILED(stream->Seek(headOffset, STREAM_SEEK_SET, nullptr));

        // Protect the shared memory while we use it.
        auto releaseOnExit = m_dataMutex.acquire();

        STATSTG stats{};
        THROW_IF_FAILED(stream->Stat(&stats, STATFLAG_NONAME));
        THROW_HR_IF(E_FAIL, static_cast<ULONG>(stats.cbSize.QuadPart) > sizeof(m_data->stream));

        ULONG bytesRead{ 0 };
        THROW_IF_FAILED(stream->Read(m_data->stream, static_cast<ULONG>(stats.cbSize.QuadPart), &bytesRead));
        resetStreamOnExit.release();
    }

    Microsoft::ApplicationModel::Activation::ActivationArguments AppInstance::UnmarshalArguments()
    {
        com_ptr<IStream> stream;
        THROW_IF_FAILED(CreateStreamOnHGlobal(nullptr, TRUE, stream.put()));

        // Protect the shared memory while we use it.
        auto releaseOnExit = m_dataMutex.acquire();

        ULONG bytesWritten = 0;
        THROW_IF_FAILED(stream->Write(m_data->stream, sizeof(m_data->stream), &bytesWritten));

        const LARGE_INTEGER headOffset{};
        THROW_IF_FAILED(stream->Seek(headOffset, STREAM_SEEK_SET, nullptr));

        com_ptr<::IUnknown> unk;
        THROW_IF_FAILED(CoUnmarshalInterface(stream.get(), guid_of<ActivationArguments>(), unk.put_void()));

        return unk.as<Microsoft::ApplicationModel::Activation::ActivationArguments>();
    }
}
