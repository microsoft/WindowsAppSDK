#include "pch.h"

#include <winrt/base.h>
#include <winrt/Windows.ApplicationModel.background.h>
#include <winrt/Windows.ApplicationModel.activation.h>
#include <winrt/Windows.Storage.Streams.h>
#include <winrt/Windows.Networking.PushNotifications.h>

#include "PushNotificationActivatedEventArgs.h"
#include "PushNotificationActivatedEventArgs.g.cpp"

#include <wil/resource.h>

using namespace winrt::Windows::ApplicationModel::Background;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::Networking::PushNotifications;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Storage::Streams;

extern wil::unique_handle g_waitHandleForArgs;
extern winrt::Microsoft::ProjectReunion::PushNotificationActivatedEventArgs g_activatedEventArgs;

namespace winrt::Microsoft::ProjectReunion::implementation
{
    std::mutex PushNotificationActivatedEventArgs::s_mutex;
    std::unique_lock<std::mutex> PushNotificationActivatedEventArgs::s_lock(s_mutex, std::defer_lock); // Avoid locking during the constructor call

    PushNotificationActivatedEventArgs::PushNotificationActivatedEventArgs(Windows::ApplicationModel::Background::IBackgroundTaskInstance const& backgroundTask) :
        m_backgroundTaskInstance(nullptr),
        m_backgroundTaskDeferral(nullptr),
        m_payload()
    {
        // PushNotificationActivatedEventArgs will manage task lifetime
        m_backgroundTaskInstance = backgroundTask;

        auto triggerDetails = m_backgroundTaskInstance.TriggerDetails();
        RawNotification rawNotification = triggerDetails.as<RawNotification>();

        IBuffer rawContentAsBuffer = rawNotification.ContentBytes();
        DataReader dataReader = DataReader::FromBuffer(rawContentAsBuffer);

        m_payload = winrt::com_array<uint8_t>(rawContentAsBuffer.Length());
        dataReader.ReadBytes(m_payload);
    }

    PushNotificationActivatedEventArgs::PushNotificationActivatedEventArgs() :
        m_backgroundTaskInstance(nullptr),
        m_backgroundTaskDeferral(nullptr),
        m_payload()
    {
    }

    PushNotificationActivatedEventArgs::~PushNotificationActivatedEventArgs()
    {
        CompleteDeferral();
    }

    com_array<uint8_t> PushNotificationActivatedEventArgs::Payload()
    {
        s_lock.lock();
        return winrt::com_array<uint8_t>(m_payload.begin(), m_payload.end());
    }
    void PushNotificationActivatedEventArgs::GetDeferral()
    {
        s_lock.lock();
        m_backgroundTaskDeferral = m_backgroundTaskInstance.GetDeferral();
    }
    void PushNotificationActivatedEventArgs::CompleteDeferral()
    {
        s_lock.lock();
        m_backgroundTaskDeferral.Complete();
    }
    winrt::event_token PushNotificationActivatedEventArgs::Canceled(Windows::ApplicationModel::Background::BackgroundTaskCanceledEventHandler const& handler)
    {
        s_lock.lock();
        return m_backgroundTaskInstance.Canceled(handler);
    }
    void PushNotificationActivatedEventArgs::Canceled(winrt::event_token const& token) noexcept
    {
        s_lock.lock();
        m_backgroundTaskInstance.Canceled(token);
    }
    uint32_t PushNotificationActivatedEventArgs::SuspendedCount() // We don't need this API though
    {
        return m_backgroundTaskInstance.SuspendedCount(); 
    }

    // go away of these functions
    Windows::ApplicationModel::Activation::ActivationKind PushNotificationActivatedEventArgs::Kind()
    {
        // Return some default value for now, we can discuss about this
        return ActivationKind::Launch;
    }
    Windows::ApplicationModel::Activation::ApplicationExecutionState PushNotificationActivatedEventArgs::PreviousExecutionState()
    {
        // App has to be running to access the EventArgs
        return ApplicationExecutionState::Running;
    }
    Windows::ApplicationModel::Activation::SplashScreen PushNotificationActivatedEventArgs::SplashScreen()
    {
        return nullptr; // return either nullptr or empty object
    }

    winrt::Microsoft::ProjectReunion::PushNotificationActivatedEventArgs PushNotificationActivatedEventArgs::GetPushNotificationActivatedEventArgs()
    {
        if (g_waitHandleForArgs == nullptr)
        {
            winrt::throw_hresult(E_UNEXPECTED);
        }

        DWORD waitResult = WaitForSingleObject(g_waitHandleForArgs.get(), 1000);

        //if (waitResult != WAIT_OBJECT_0)
        //{
        //    winrt::throw_hresult(E_UNEXPECTED);
        //}

        return g_activatedEventArgs;
    }
}
