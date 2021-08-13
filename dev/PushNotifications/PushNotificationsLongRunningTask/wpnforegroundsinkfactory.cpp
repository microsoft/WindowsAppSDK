#include "pch.h"

#include <NotificationsLongRunningProcess_h.h>

#include "wpnforegroundsink.h"
#include <wrl/implements.h>
#include <wrl/module.h>
#include "wpnforegroundsinkfactory.h"

using namespace Microsoft::WRL;

IFACEMETHODIMP WpnForegroundSinkFactory::CreateInstance(
    _In_opt_ IUnknown* /*outer*/,
    _In_ REFIID /*riid*/,
    _COM_Outptr_ void** obj)
{
    *obj = nullptr;

    *obj = Microsoft::WRL::Make<WpnForegroundSinkImpl>().Get();

    return S_OK;
}
