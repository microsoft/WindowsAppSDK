// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License.

#pragma once
#include "Microsoft.Windows.BadgeNotifications.BadgeNotificationManager.g.h"
#include "externs.h"

namespace winrt::Microsoft::Windows::BadgeNotifications::implementation
{
    struct BadgeNotificationManager : BadgeNotificationManagerT<BadgeNotificationManager>
    {
        BadgeNotificationManager();

        static winrt::Microsoft::Windows::BadgeNotifications::BadgeNotificationManager Current();

        void SetBadgeAsCount(_In_ uint32_t notificationCount);
        void SetBadgeAsCount(_In_ uint32_t notificationCount, _In_ winrt::Windows::Foundation::DateTime expiration);

        void SetBadgeAsGlyph(_In_ winrt::Microsoft::Windows::BadgeNotifications::BadgeNotificationGlyph glyphValue);
        void SetBadgeAsGlyph(_In_ winrt::Microsoft::Windows::BadgeNotifications::BadgeNotificationGlyph glyphValue, _In_ winrt::Windows::Foundation::DateTime expiration);

        void ClearBadge();

    private:
        std::wstring GetBadgeNotificationGlyphToString(_In_ winrt::Microsoft::Windows::BadgeNotifications::BadgeNotificationGlyph glyphValue);
        void SetBadge(_In_ const std::wstring& value, _In_opt_ const winrt::Windows::Foundation::DateTime* expiration);
        std::wstring m_processName;
        std::wstring m_appId;
    };

    struct BadgeNotificationManagerFactory : winrt::implements<BadgeNotificationManagerFactory, IClassFactory>
    {
        STDMETHODIMP CreateInstance(_In_opt_ IUnknown* aggregateInterface, _In_ REFIID interfaceId, _Outptr_ VOID** object) noexcept final try
        {
            RETURN_HR_IF(CLASS_E_NOAGGREGATION, aggregateInterface != nullptr);
            return BadgeNotificationManager::Current().as(interfaceId, object);
        }
        CATCH_RETURN()

            STDMETHODIMP LockServer(BOOL fLock) noexcept final
        {
            if (fLock)
            {
                ++winrt::get_module_lock();
            }
            else
            {
                --winrt::get_module_lock();
            }
            return S_OK;
        }
    };
}
namespace winrt::Microsoft::Windows::BadgeNotifications::factory_implementation
{
    struct BadgeNotificationManager : BadgeNotificationManagerT<BadgeNotificationManager, implementation::BadgeNotificationManager>
    {
    };
}
