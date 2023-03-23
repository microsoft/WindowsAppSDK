// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "pch.h"
#include <wrl\module.h>
#include <KozaniManager_h.h>
#include "ConnectionManager.h"

#include "..\KozaniManager\KozaniManager-Constants.h"
#include "KozaniManagerActivity.h"

using namespace Microsoft::WRL;
using namespace Microsoft::Kozani::DvcProtocol;

extern volatile LONG g_newConnectionCount;
extern Microsoft::Kozani::Manager::ConnectionManager g_connectionManager;

class KozaniDvcCallback : public Microsoft::WRL::RuntimeClass<
    Microsoft::WRL::RuntimeClassFlags<Microsoft::WRL::ClassicCom>,
    IWTSVirtualChannelCallback>
{
public:
    KozaniDvcCallback(
        IWTSVirtualChannel* pChannel,
        IWTSVirtualChannelManager* pChannelMgr)
        : m_channel(pChannel), m_channelManager(pChannelMgr)
    {
    }

    //
    // IWTSVirtualChannelCallback
    //
    HRESULT STDMETHODCALLTYPE OnDataReceived(
        ULONG size,
        _In_reads_(size) BYTE* data) override try
    {
        LogDebugMessage("IWTSVirtualChannelCallback::OnDataReceived(), cbSize = %u, pChannelMgr=0x%I64x, pChannel=0x%I64x\n",
            size, (UINT64)m_channelManager.get(), (UINT64)m_channel.get());

        g_connectionManager.ProcessProtocolDataUnit(data, size, m_channelManager.get(), m_channel.get());
        return S_OK;
    }
    CATCH_RETURN()

    HRESULT STDMETHODCALLTYPE OnClose() override try
    {
        LogDebugMessage("IWTSVirtualChannelCallback::OnClose() - pChannelMgr=0x%I64x, pChannel=0x%I64x\n",
            (UINT64)m_channelManager.get(), (UINT64)m_channel.get());
        
        g_connectionManager.OnDvcChannelClose(m_channel.get());
        return S_OK;
    }
    CATCH_RETURN()

private:

    wil::com_ptr<IWTSVirtualChannelManager> m_channelManager;
    wil::com_ptr<IWTSVirtualChannel> m_channel;
};

struct __declspec(uuid(PR_KOZANIDVC_CLSID_STRING)) KozaniDvcImpl WrlFinal : RuntimeClass<RuntimeClassFlags<ClassicCom>, IWTSPlugin, IWTSListenerCallback>
{
    //
    // IWTSPlugin
    //
    STDMETHODIMP Initialize(
        IWTSVirtualChannelManager* pChannelMgr) override try
    {
        // Called early in MSRDC launch, before a connection to a new remote session.
        LogDebugMessage("IWTSPlugin::Initialize() - pChannelMgr=0x%I64x\n", (UINT64)pChannelMgr);

        m_channelManager = pChannelMgr;

        wil::com_ptr<IWTSListener> listener;
        // Attach the callback to the "KozaniDvc" endpoint.
        RETURN_IF_FAILED(m_channelManager->CreateListener(
            DvcChannelName,
            0,  // uFlags - reserved and must be set to zero
            this,
            &listener));

        g_connectionManager.OnRemoteDesktopInitializeConnection(pChannelMgr);
        InterlockedIncrement(&g_newConnectionCount);
        return S_OK;
    }
    CATCH_RETURN()

    STDMETHODIMP Connected() override try
    {
        LogDebugMessage("IWTSPlugin::Connected() - pChannelMgr=0x%I64x\n", (UINT64)m_channelManager.get());
        return S_OK;
    }
    CATCH_RETURN()

    STDMETHODIMP Disconnected(DWORD dwDisconnectCode) override try
    {
        LogDebugMessage("IWTSPlugin::Disconnected() - pChannelMgr=0x%I64x, dwDisconnectCode = %u\n", (UINT64)m_channelManager.get(), dwDisconnectCode);
        g_connectionManager.OnRemoteDesktopDisconnect(m_channelManager.get());
        return S_OK;
    }
    CATCH_RETURN()

    STDMETHODIMP Terminated() override try
    {
        LogDebugMessage("IWTSPlugin::Terminated() - pChannelMgr=0x%I64x\n", (UINT64)m_channelManager.get());
        g_connectionManager.OnRemoteDesktopDisconnect(m_channelManager.get());
        return S_OK;
    }
    CATCH_RETURN()

    //
    // IWTSListenerCallback
    //
    STDMETHODIMP OnNewChannelConnection(
        IWTSVirtualChannel* pChannel,
        _In_opt_ BSTR data,
        _Out_ BOOL* pbAccept,
        _Out_ IWTSVirtualChannelCallback** ppCallback) override try
    {
        // Per MSDN, the data parameter "is not implemented and is reserved for future use".
        UNREFERENCED_PARAMETER(data);

        LogDebugMessage("IWTSListenerCallback::OnNewChannelConnection is called! pChannelMgr=0x%I64x, pChannel=0x%I64x\n",
            (UINT64)m_channelManager.get(), (UINT64)pChannel);

        auto pConnection = Make<KozaniDvcCallback>(pChannel, m_channelManager.get());
        *ppCallback = pConnection.Detach();
        *pbAccept = TRUE;

        return S_OK;
    }
    CATCH_RETURN()

private:
    wil::com_ptr<IWTSVirtualChannelManager> m_channelManager;
};
CoCreatableClass(KozaniDvcImpl);
