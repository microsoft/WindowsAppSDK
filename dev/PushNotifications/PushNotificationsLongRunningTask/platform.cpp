#include "pch.h"

#include <NotificationsLongRunningProcess_h.h>

#include "platform.h"
#include "platformfactory.h"

void NotificationsLongRunningPlatformImpl::Initialize()
{
    auto lock = m_lock.lock_exclusive();
    THROW_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);

    if (m_initialized)
    {
        return;
    }

    // Schedule event signaling after 30 seconds. This is in case we don't have any apps to track in the LRP.
    // If we realize that we need to persist the LRP, timer should be canceled.
    SetupTimer();

    PopulateAppList();
    if (m_appList.size() > 0)
    {
        CancelTimer();

        /* TODO: Load platform components */
    }

    m_initialized = true;
}

// TODO: Verify UDK list and make sure we have apps to be tracked
void NotificationsLongRunningPlatformImpl::PopulateAppList()
{
    /* TODO: Call the UDK to retrieve the list of valid apps from Notifications platform */

    wil::unique_hkey appListRootKey;

    THROW_IF_WIN32_ERROR(RegOpenKeyEx(
        HKEY_CURRENT_USER,
        L"",
        0,
        KEY_READ,
        &appListRootKey));

    DWORD appCount = 0;
    DWORD maximumSubkeyLength = 0;
    THROW_IF_WIN32_ERROR(RegQueryInfoKeyW(
        appListRootKey.get(), nullptr, nullptr, nullptr,
        &appCount, &maximumSubkeyLength, nullptr, nullptr,
        nullptr, nullptr, nullptr, nullptr));

    if (appCount > 0)
    {
        for (ULONG index = 0; index < appCount; index++)
        {
            WCHAR appId[1024] = {};

            THROW_IF_WIN32_ERROR(RegEnumKeyExW(
                appListRootKey.get(),
                index,
                appId,
                &maximumSubkeyLength,
                nullptr,
                nullptr,
                nullptr,
                nullptr));

            wil::unique_hkey appIdKey;

            THROW_IF_WIN32_ERROR(RegOpenKeyEx(
                HKEY_CURRENT_USER,
                L"" /* + appId */,
                0,
                KEY_READ,
                &appIdKey));

            DWORD valueType = REG_SZ;

            THROW_IF_WIN32_ERROR(RegQueryValueExW(
                appIdKey.get(),
                L"ProcessName",
                nullptr,
                &valueType,
                nullptr, // byte ptr
                0)); // byte ptr size

            // Convert appIdKey into guid
            winrt::guid appIdAsGuid = winrt::guid(std::wstring_view(L""));
            AppInfo appInfo = { appIdAsGuid, nullptr };
        }
    }
}

void NotificationsLongRunningPlatformImpl::Shutdown()
{
    auto lock = m_lock.lock_exclusive();
    if (m_shutdown)
    {
        return;
    }

    /* TODO: Shut down your components */

    m_shutdown = true;
}

void NotificationsLongRunningPlatformImpl::SignalEvent()
{
    m_event.SetEvent();
}

void NotificationsLongRunningPlatformImpl::WaitForEvent()
{
    m_event.wait();
}

void NotificationsLongRunningPlatformImpl::SetupTimer()
{
    // Already guarded by the lock in Initialize()
    m_timer.reset(CreateThreadpoolTimer(
        [](PTP_CALLBACK_INSTANCE, _Inout_ PVOID platform, _Inout_ PTP_TIMER)
        {
            NotificationsLongRunningPlatformImpl* platformImpl = reinterpret_cast<NotificationsLongRunningPlatformImpl*>(platform);

            if (platformImpl != nullptr)
            {
                platformImpl->SignalEvent();
            }
        },
        this,
        nullptr));

    THROW_LAST_ERROR_IF_NULL(m_timer);

    // Negative times in SetThreadpoolTimer are relative. Allow 30 seconds to fire.
    FILETIME dueTime{};
    *reinterpret_cast<PLONGLONG>(&dueTime) = -static_cast<LONGLONG>(30000 * 10000);

    SetThreadpoolTimer(m_timer.get(), &dueTime, 0, 0);
}

void NotificationsLongRunningPlatformImpl::CancelTimer()
{
    // Already guarded by the lock in Initialize()
    m_timer.reset();
}

// Example of one function. We will add more as we need them.
STDMETHODIMP_(HRESULT __stdcall) NotificationsLongRunningPlatformImpl::RegisterFullTrustApplication(_In_ PCWSTR /*processName*/, _In_ GUID /*remoteId*/, _Out_ GUID* /*appId*/) noexcept
{
    auto lock = m_lock.lock_shared();
    RETURN_HR_IF(WPN_E_PLATFORM_UNAVAILABLE, m_shutdown);
    
    return E_NOTIMPL;
}

