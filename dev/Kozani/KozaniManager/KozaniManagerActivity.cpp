// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"
#include <wrl\module.h>
#include <KozaniManager_h.h>

#include "..\KozaniManager\KozaniManager-Constants.h"
#include "KozaniManagerActivity.h"

using namespace Microsoft::WRL;

class KozaniDvcCallback : public Microsoft::WRL::RuntimeClass<
    Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::ClassicCom>,
    IWTSVirtualChannelCallback>
{
public:
    KozaniDvcCallback(
        IWTSVirtualChannel* pChannel,
        IWTSVirtualChannelManager* pChannelMgr)
        : m_spChannel(pChannel), m_spChannelMgr(pChannelMgr)
    {
    }


    //
    // IWTSVirtualChannelCallback
    //
    HRESULT STDMETHODCALLTYPE OnDataReceived(
        ULONG cbSize,
        _In_reads_(cbSize) BYTE* pBuffer) override
    {
        LogDebugMessage("IWTSVirtualChannelCallback::OnDataReceived(), cbSize = %u, pChannelMgr=0x%I64x, pChannel=0x%I64x\n",
            cbSize, (UINT64)m_spChannelMgr.Get(), (UINT64)m_spChannel.Get());
        return S_OK;
    }

    HRESULT STDMETHODCALLTYPE OnClose() override
    {
        LogDebugMessage("IWTSVirtualChannelCallback::OnClose() - pChannelMgr=0x%I64x, pChannel=0x%I64x\n",
            (UINT64)m_spChannelMgr.Get(), (UINT64)m_spChannel.Get());
        return S_OK;
    }

private:

    Microsoft::WRL::ComPtr<IWTSVirtualChannelManager> m_spChannelMgr;
    Microsoft::WRL::ComPtr<IWTSVirtualChannel> m_spChannel;
    Microsoft::WRL::ComPtr<IWTSBitmapRenderer> m_spRenderer;
};

struct __declspec(uuid(PR_KOZANIDVC_CLSID_STRING)) KozaniDvcImpl WrlFinal : RuntimeClass<RuntimeClassFlags<ClassicCom>, IWTSPlugin, IWTSListenerCallback>
{
    //
    // IWTSPlugin
    //
    STDMETHODIMP Initialize(
        IWTSVirtualChannelManager* pChannelMgr) override
    {
        // Called early in MSRDC launch, before a connection to a new remote session.
        LogDebugMessage("IWTSPlugin::Initialize() - pChannelMgr=0x%I64x\n", (UINT64)pChannelMgr);

        m_spChannelMgr = pChannelMgr;

        ComPtr<IWTSListener> listener;
        // Attach the callback to the "DVC_InstantApp" endpoint.
        HRESULT hr = (m_spChannelMgr->CreateListener(
            "KozaniDvc", //InstantAppDvcRpc::DVC_NAME,
            0,
            this,
            &listener));

        LogDebugMessage("_spChannelMgr->CreateListener result: 0x%x\n", hr);
        return S_OK;
    }

    STDMETHODIMP Connected() override
    {
        LogDebugMessage("IWTSPlugin::Connected() - pChannelMgr=0x%I64x\n", (UINT64)m_spChannelMgr.Get());
        return S_OK;
    }

    STDMETHODIMP Disconnected(DWORD dwDisconnectCode) override
    {
        LogDebugMessage("IWTSPlugin::Disconnected() - pChannelMgr=0x%I64x, dwDisconnectCode = %u\n", (UINT64)m_spChannelMgr.Get(), dwDisconnectCode);
        return S_OK;
    }

    STDMETHODIMP Terminated() override
    {
        LogDebugMessage("IWTSPlugin::Terminated() - pChannelMgr=0x%I64x\n", (UINT64)m_spChannelMgr.Get());
        return S_OK;
    }

    //
    // IWTSListenerCallback
    //
    STDMETHODIMP OnNewChannelConnection(
        IWTSVirtualChannel* pChannel,
        _In_opt_ BSTR data,
        _Out_ BOOL* pbAccept,
        _Out_ IWTSVirtualChannelCallback** ppCallback) override
    {
        LogDebugMessage("IWTSListenerCallback::OnNewChannelConnection is called! pChannelMgr=0x%I64x, pChannel=0x%I64x\n",
            (UINT64)m_spChannelMgr.Get(), (UINT64)pChannel);

        auto pConnection = Make<KozaniDvcCallback>(pChannel, m_spChannelMgr.Get());
        *ppCallback = pConnection.Detach();
        *pbAccept = TRUE;

        /*
        if (m_n < 1000)
        {
            m_n++;
            ComPtr<IWTSListener> listener;
            std::string dvcName = "KozaniDvc" + std::to_string(m_n);
            HRESULT hr = (m_spChannelMgr->CreateListener(
                dvcName.c_str(), //InstantAppDvcRpc::DVC_NAME,
                0,
                this,
                &listener));

            LogDebugMessage("_spChannelMgr->CreateListener with channel name %s result: 0x%x", dvcName.c_str(), hr);
        }
        */
        return S_OK;
    }

private:
    Microsoft::WRL::ComPtr<IWTSVirtualChannelManager> m_spChannelMgr;
    int m_n{};

};
CoCreatableClass(KozaniDvcImpl);
