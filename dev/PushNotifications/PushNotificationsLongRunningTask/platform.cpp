#include "pch.h"

#include <NotificationsLongRunningProcess_h.h>

#include "platform.h"
#include "platformfactory.h"
#include <FrameworkUdk/PushNotifications.h>

void NotificationsLongRunningPlatformImpl::Initialize()
{
    auto lock = m_lock.lock_exclusive();
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);

    if (m_initialized)
    {
        return;
    }

    // Schedule event signaling after 5 seconds. This is in case we don't have any apps to track in the LRP.
    // If we realize that we need to persist the LRP, timer should be canceled.
    m_shutdownTimerManager = std::make_unique<PlatformLifetimeTimerManager>();
    m_shutdownTimerManager->Setup();

    /* TODO: Verify registry and UDK list and make sure we have apps to be tracked */

    /* TODO: Load platform components */

    m_initialized = true;
}

void NotificationsLongRunningPlatformImpl::Shutdown() noexcept
{
    auto lock = m_lock.lock_exclusive();
    if (m_shutdown)
    {
        return;
    }

    /* TODO: Shut down your components */

    m_shutdown = true;
}

void NotificationsLongRunningPlatformImpl::WaitForWinMainEvent()
{
    THROW_HR_IF_NULL(E_UNEXPECTED, m_shutdownTimerManager.get());
    m_shutdownTimerManager->Wait();
}

void NotificationsLongRunningPlatformImpl::AddToRegistry(const std::wstring& processName, std::wstring appId)
{
    std::wstring subkey = L"Software\\Microsoft\\Windows\\CurrentVersion\\PushNotifications\\LongRunningProcess";

    wil::unique_hkey hKeyResult;

    THROW_IF_WIN32_ERROR(RegCreateKeyEx(
        HKEY_CURRENT_USER,
        subkey.c_str(),
        0,
        nullptr,
        REG_OPTION_NON_VOLATILE,
        KEY_ALL_ACCESS,
        nullptr,
        &hKeyResult,
        nullptr));

    THROW_IF_WIN32_ERROR(RegSetKeyValue(
        hKeyResult.get(),
        nullptr,
        appId.c_str(),
        REG_SZ,
        processName.c_str(),
        static_cast<DWORD>(sizeof(WCHAR) * processName.size())));
}

void NotificationsLongRunningPlatformImpl::GetAppIdentifier(const std::wstring processName)
{
    if (m_appIdMap.find(processName) == m_appIdMap.end())
    {
        GUID guidReference;
        THROW_IF_FAILED(CoCreateGuid(&guidReference));

        wil::unique_cotaskmem_string guidStr;
        THROW_IF_FAILED(StringFromCLSID(guidReference, &guidStr));

        AddToRegistry(processName, guidStr.get());
        m_appIdMap[processName] = guidStr.get();
    }
}

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::RegisterFullTrustApplication(
    _In_ PCWSTR processName, GUID remoteId, _Out_ PWSTR* appId) noexcept try
{
    auto lock = m_lock.lock_shared();

    GetAppIdentifier(processName);

    THROW_IF_FAILED(PushNotifications_RegisterFullTrustApplication(m_appIdMap[processName].c_str(), remoteId));

    *appId = wil::make_unique_string<wil::unique_cotaskmem_string>(m_appIdMap[processName].c_str()).get();

    return S_OK;
}
CATCH_RETURN()
