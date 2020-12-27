// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#if !defined(WINRTINPROCMODULE_H)
#define WINRTINPROCMODULE_H

#include <activationregistration.h>
#include <activation.h>

namespace MddCore
{
class WinRTInprocModule
{
public:
    WinRTInprocModule() = default;

    ~WinRTInprocModule() = default;

    enum class ThreadingModel
    {
        Unknown,
        Both,
        STA,
        MTA
    };

    ThreadingModel Find(const std::wstring& activatableClassId)
    {
        auto iterator = m_inprocServers.find(activatableClassId);
        if (iterator != m_inprocServers.end())
        {
            return iterator->second;
        }
        return ThreadingModel::Unknown;
    }

    HRESULT GetActivationFactory(HSTRING className, REFIID iid, void** factory)
    {
        RETURN_IF_FAILED(Load());

        IActivationFactory* ifactory{};
        THROW_IF_FAILED(m_dllGetActivationFactory(className, &ifactory));

        //TODO optimize for IActivationFactory?
        const auto hr{ ifactory->QueryInterface(iid, factory) };
        ifactory->Release();
        return hr;
    }

public:
    void path(const std::wstring& path)
    {
        m_path = path;
    }

    void AddInprocServer(
        const std::wstring& activatableClassId,
        ThreadingModel threadingModel)
    {
        m_inprocServers[activatableClassId] = threadingModel;
    }

private:
    HRESULT Load()
    {
        if (!m_dll)
        {
            wil::unique_hmodule dll{ LoadLibraryExW(m_path.c_str(), nullptr, LOAD_WITH_ALTERED_SEARCH_PATH) };
            RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), dll);

            auto dllGetActivationFactory{ reinterpret_cast<DllGetActivationFactory>(GetProcAddress(dll.get(), "DllGetActivationFactory")) };
            RETURN_HR_IF_NULL(HRESULT_FROM_WIN32(GetLastError()), dllGetActivationFactory);

            m_dll = std::move(dll);
            m_dllGetActivationFactory = std::move(dllGetActivationFactory);
        }
        return S_OK;
    }


private:
    std::wstring m_path;
    std::unordered_map<std::wstring, ThreadingModel> m_inprocServers;

private:
    wil::unique_hmodule m_dll;

    typedef HRESULT(__stdcall* DllGetActivationFactory)(HSTRING, IActivationFactory**);
    DllGetActivationFactory m_dllGetActivationFactory{};
};
}

#endif // WINRTINPROCMODULE_H
