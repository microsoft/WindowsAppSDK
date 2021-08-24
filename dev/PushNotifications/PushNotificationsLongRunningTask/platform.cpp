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

void NotificationsLongRunningPlatformImpl::GetAppIdentifier(PCWSTR processName, PWSTR* appId)
{
    wil::unique_hkey hKeyResult;

    auto result = RegOpenKeyEx(
        HKEY_CURRENT_USER,
        processName,
        0,
        KEY_ALL_ACCESS,
        &hKeyResult);

    if (result == ERROR_SUCCESS)
    {
        // return the value for the key
        DWORD appUserModelIdSize = APPLICATION_USER_MODEL_ID_MAX_LENGTH;
        auto regStatus = RegGetValue(hKeyResult.get(), NULL, processName, RRF_RT_REG_SZ, nullptr, *appId, &appUserModelIdSize);
        THROW_IF_WIN32_ERROR(regStatus);
    }
    else if (result == ERROR_FILE_NOT_FOUND)
    {
        // create a new entry and set its value
        THROW_IF_WIN32_ERROR(RegCreateKeyEx(
            HKEY_CURRENT_USER,
            processName,
            0,
            nullptr,
            REG_OPTION_NON_VOLATILE,
            KEY_ALL_ACCESS,
            nullptr,
            &hKeyResult,
            nullptr));

        GUID guidReference;
        THROW_IF_FAILED(CoCreateGuid(&guidReference));

        THROW_IF_FAILED(StringFromCLSID(guidReference, appId));

        THROW_IF_WIN32_ERROR(RegSetValueExW(
            hKeyResult.get(),
            *appId,
            0,
            REG_SZ,
            reinterpret_cast<const BYTE*>(*appId),
            sizeof(*appId)));
    }
    else
    {
        THROW_IF_WIN32_ERROR(result);
    }
}

STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::RegisterFullTrustApplication(
    _In_ PCWSTR processName, GUID remoteId, _Out_ PWSTR* appId) noexcept try
{
    auto lock = m_lock.lock_shared();

    GetAppIdentifier(processName, appId);

    THROW_IF_FAILED(PushNotifications_RegisterFullTrustApplication(*appId, remoteId));

    return S_OK;
}
CATCH_RETURN()
