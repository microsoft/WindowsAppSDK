#include "pch.h"

#include <NotificationsLongRunningProcess_h.h>

#include "platform.h"
#include <wrl/implements.h>
#include <wrl/module.h>
#include "platformfactory.h"

using namespace Microsoft::WRL;

HRESULT NotificationsLongRunningProcessFactory::MakeAndInitialize()
{
     return S_OK;
}

IFACEMETHODIMP NotificationsLongRunningProcessFactory::CreateInstance(
    _In_opt_ IUnknown* /*outer*/,
    _In_ REFIID /*riid*/,
    _COM_Outptr_ void** obj)
{
    *obj = nullptr;

    std::call_once(m_platformInitializedFlag,
        [&] {
            m_platform = Microsoft::WRL::Make<NotificationsLongRunningPlatformImpl>();
            m_platform->Initialize();            
        });

    *obj = m_platform.Get();
    // Add one ref per platform instance request. Deref occurs automatically.
    m_platform->AddRef();

    return S_OK;
}
