#include "pch.h"

// FIX REF!!!
#include "..\..\PushNotificationsLongRunningTask.ProxyStub\x64\Debug\PushNotificationsLRP_h.h"
//#include <PushNotificationsLRP_h.h>

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
    *obj = GetPlatform();

    if (!GetPlatform()->IsPlatformInitialized())
    {
        THROW_IF_FAILED(InitializePlatform());
    }

    return S_OK;
}
