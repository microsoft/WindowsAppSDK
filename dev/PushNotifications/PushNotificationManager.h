// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "Microsoft.Windows.PushNotifications.PushNotificationManager.g.h"
#include <windows.foundation.h>
#include <NotificationsLongRunningProcess_h.h>
#include <frameworkudk/pushnotificationsRT.h>
#include <winrt/Windows.ApplicationModel.background.h>
#include "externs.h"

constexpr PCWSTR c_pushContractId = L"Windows.Push";

namespace winrt::Microsoft::Windows::PushNotifications::implementation
{
    typedef winrt::Windows::Foundation::TypedEventHandler<
        winrt::Microsoft::Windows::PushNotifications::PushNotificationManager,
        winrt::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs> PushNotificationEventHandler;

    struct PushNotificationManager : PushNotificationManagerT<PushNotificationManager, 
                                                                    IWpnForegroundSink,
                                                                    IWpnForegroundSink2,
                                                                    ABI::Microsoft::Internal::PushNotifications::INotificationListener,
                                                                    ABI::Microsoft::Internal::PushNotifications::INotificationListener2,
                                                                    winrt::Windows::ApplicationModel::Background::IBackgroundTask, 
                                                                    INotificationManagerDeserializer>
    {
        PushNotificationManager();
        ~PushNotificationManager();
        static bool IsSupported();
        static winrt::Microsoft::Windows::PushNotifications::PushNotificationManager Default();
        static winrt::Windows::Foundation::IInspectable PushDeserialize(winrt::Windows::Foundation::Uri const& uri);
        void Register();
        void Unregister();
        void UnregisterAll();

        winrt::Windows::Foundation::IAsyncOperationWithProgress<winrt::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelResult, winrt::Microsoft::Windows::PushNotifications::PushNotificationCreateChannelStatus> CreateChannelAsync(winrt::guid const remoteId);

        winrt::event_token PushReceived(winrt::Windows::Foundation::TypedEventHandler<Microsoft::Windows::PushNotifications::PushNotificationManager, Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs> handler);
        void PushReceived(winrt::event_token const& token) noexcept;

        // IWpnForegroundSink
        IFACEMETHODIMP InvokeAll(_In_ ULONG length, _In_ byte* payload, _Out_ BOOL* foregroundHandled) noexcept;

        // IWpnForegroundSink2
        IFACEMETHODIMP InvokeAllWithCorrelationVector(
            ULONG length,
            _In_ byte* payload,
            _In_ PCWSTR correlationVector,
            _Out_ BOOL* foregroundHandled) noexcept;

        // IBackgroundTask
        void Run(winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance const& taskInstance);

        void OnCanceled(
            [[maybe_unused]] winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance const&,
            [[maybe_unused]] winrt::Windows::ApplicationModel::Background::BackgroundTaskCancellationReason const&)
        {
        }

        // INotificationManagerDeserializer
        winrt::Windows::Foundation::IInspectable Deserialize(winrt::Windows::Foundation::Uri const& uri);
        
        // INotificationListener
        IFACEMETHODIMP OnRawNotificationReceived(unsigned int payloadLength, _In_ byte* payload, _In_ HSTRING correlationVector) noexcept;

        // INotificationListener2
        IFACEMETHODIMP OnToastNotificationReceived(ABI::Microsoft::Internal::ToastNotifications::INotificationProperties* notificationProperties,
            ABI::Microsoft::Internal::ToastNotifications::INotificationTransientProperties*) noexcept;
    private:
        bool IsBackgroundTaskRegistered(winrt::hstring const& backgroundTaskFullName);
        void InvokeAllInternal(
            ULONG length,
            _In_ byte* payload,
            _In_ PCWSTR correlationVector,
            _Out_ BOOL* foregroundHandled);

        bool m_firstNotificationReceived{ false };
        winrt::event<PushNotificationEventHandler> m_foregroundHandlers;
        winrt::Windows::ApplicationModel::Background::IBackgroundTaskRegistration m_pushTriggerRegistration{ nullptr };
        wil::unique_com_class_object_cookie m_comActivatorRegistration;
        bool m_singletonLongRunningSinkRegistration{ false };   // Defines if the long running singleton process has registered a sink with the platform for a given app
        bool m_singletonForegroundRegistration{ false };   // Defines if the app has registered a foreground sink with the Long running process singleton
        bool m_sinkRegisteredWithPlatform{ false }; // Defines if PushNotificationManager has directly registered a sink with the platform, only used if PackagedAppScenario() == true
        bool m_registering{ false };
        wil::srwlock m_lock;
        std::wstring m_processName;
        winrt::guid m_registeredClsid{ GUID_NULL };
        winrt::Microsoft::Windows::PushNotifications::PushNotificationChannel m_channel{ nullptr };
        wil::unique_event m_waitHandleForArgs;
        winrt::Microsoft::Windows::PushNotifications::PushNotificationReceivedEventArgs m_backgroundTaskArgs{ nullptr };
    };

    struct PushNotificationManagerFactory : winrt::implements<PushNotificationManagerFactory, IClassFactory>
    {
        STDMETHODIMP CreateInstance(_In_opt_ IUnknown* aggregateInterface, _In_ REFIID interfaceId, _Outptr_ VOID** object) noexcept final try
        {
            RETURN_HR_IF(CLASS_E_NOAGGREGATION, aggregateInterface != nullptr);
            return PushNotificationManager::Default().as(interfaceId, object);
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

namespace winrt::Microsoft::Windows::PushNotifications::factory_implementation
{
    struct PushNotificationManager : PushNotificationManagerT<PushNotificationManager, implementation::PushNotificationManager>
    {
    };
}
