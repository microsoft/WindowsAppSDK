#include "pch.h"

#include <PushNotificationsLRP_h.h>

#include "externs.h"
#include "platform.h"
#include <wrl/implements.h>
#include <wrl/module.h>
#include "platformfactory.h"

using namespace Microsoft::WRL;

IFACEMETHODIMP WpnLrpPlatformFactory::CreateInstance(
    _In_opt_ IUnknown* /*outer*/,
    _In_ REFIID /*riid*/,
    _COM_Outptr_ void** obj) noexcept
{
    *obj = nullptr;

    THROW_IF_FAILED(InitializePlatform());

    *obj = GetPlatform();
    reinterpret_cast<IUnknown*>(obj)->AddRef();

    return S_OK;
}
