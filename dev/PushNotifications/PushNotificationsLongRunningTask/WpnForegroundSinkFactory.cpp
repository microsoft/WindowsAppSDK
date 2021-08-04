#include "pch.h"
#include <PushNotificationsLRP_h.h>
#include <wrl/implements.h>
#include "WpnForegroundSinkWrapper.h"
#include "WpnForegroundSinkFactory.h"

using namespace Microsoft::WRL;

IFACEMETHODIMP WpnForegroundSinkWrapperFactory::CreateInstance(
    _In_opt_ IUnknown* /*outer*/,
    _In_ REFIID /*riid*/,
    _COM_Outptr_ void** obj) noexcept
{
    *obj = Microsoft::WRL::Make<WpnForegroundSinkWrapperImpl>().Get();
    return S_OK;
}
