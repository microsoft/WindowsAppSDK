// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "platform.h"
#include <wrl/implements.h>
#include <wrl/module.h>
#include "platformfactory.h"

using namespace Microsoft::WRL;

HRESULT NotificationsLongRunningProcessFactory::RuntimeClassInitialize() noexcept try
{
    m_platform = winrt::make_self<NotificationsLongRunningPlatformImpl>();
    m_platform->Initialize();

    return S_OK;
}
CATCH_RETURN()

IFACEMETHODIMP NotificationsLongRunningProcessFactory::CreateInstance(
    _In_opt_ IUnknown* /*outer*/,
    _In_ REFIID /*riid*/,
    _COM_Outptr_ void** obj)
{
    *obj = m_platform.get();
    // Add one ref per platform instance request. Deref occurs automatically.
    m_platform->AddRef();

    return S_OK;
}
