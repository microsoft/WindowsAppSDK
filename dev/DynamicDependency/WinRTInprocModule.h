// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#if !defined(WINRTINPROCMODULE_H)
#define WINRTINPROCMODULE_H

#include <activationregistration.h>
#include <activation.h>

//TODO Components won't respect COM lifetime. workaround to get them in the COM list? See dev\UndockedRegFreeWinRT\catalog.cpp

//TODO Removing a PackageGraphNode destroys its WinRTInprocModule objects. BadMojo(TM) if in use when destroyed. Update to handle

namespace MddCore
{
class WinRTInprocModule
{
public:
    WinRTInprocModule() = default;

    WinRTInprocModule(WinRTInprocModule&& other) :
        m_dll(std::move(other.m_dll)),
        m_dllGetActivationFactory(std::move(m_dllGetActivationFactory))
    {
    }

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

        //TODO optimize for IActivationFactory? See GetActivationFactory() in dev\UndockedRegFreeWinRT\catalog.cpp
        const auto hr{ ifactory->QueryInterface(iid, factory) };
        ifactory->Release();
        return hr;
    }

public:
    const std::wstring& Path() const
    {
        return m_path;
    }

    void Path(const std::wstring& path)
    {
        m_path = path;
    }

    const std::unordered_map<std::wstring, ThreadingModel>& InprocServers() const
    {
        return m_inprocServers;
    }

    void AddInprocServer(
        const std::wstring& activatableClassId,
        ThreadingModel threadingModel)
    {
        // No dupes allowed
        auto iterator{ m_inprocServers.find(activatableClassId) };
        if (iterator != m_inprocServers.end())
        {
            THROW_HR_MSG(HRESULT_FROM_WIN32(ERROR_OBJECT_ALREADY_EXISTS), "%ls", activatableClassId.c_str());
        }

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
