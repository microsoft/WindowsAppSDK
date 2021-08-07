#include "pch.h"

#include <NotificationsLongRunningProcess_h.h>

#include "externs.h"
#include "platform.h"
#include <wrl/implements.h>
#include <wrl/module.h>
#include "platformfactory.h"

using namespace Microsoft::WRL;

IFACEMETHODIMP WpnLrpPlatformFactory::CreateInstance(
    _In_opt_ IUnknown* /*outer*/,
    _In_ REFIID /*riid*/,
    _COM_Outptr_ void** obj)
{
    *obj = nullptr;

    THROW_IF_FAILED(InitializePlatform());

    *obj = GetPlatform();

    return S_OK;
}
