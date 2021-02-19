// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include <AppLifecycle.g.h>
#include "shared_memory.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct AppInstanceList
    {
        unsigned long count = 0;
    };

    struct AppInstanceData
    {
        DWORD processId = 0;
        BYTE stream[1024];
    };

    struct AppLifecycle
    {
        // No interface public methods.
        AppLifecycle() = default;
        AppLifecycle(winrt::hstring key);
        void Activate();

        // IAppLifecycleStatics.
        static Windows::ApplicationModel::Activation::IActivatedEventArgs GetActivatedEventArgs();
        static Microsoft::ProjectReunion::AppLifecycle FindOrRegisterInstanceForKey(hstring const& key);
        static Windows::Foundation::Collections::IVector<Microsoft::ProjectReunion::AppLifecycle> GetRegisteredInstances();
        static void UnregisterInstanceForRedirection();

        // IAppLifecycle.
        void RedirectActivationTo(Windows::ApplicationModel::Activation::IActivatedEventArgs const& args);

        winrt::event_token Activated(Windows::Foundation::EventHandler<Windows::ApplicationModel::Activation::IActivatedEventArgs> const& handler);
        void Activated(winrt::event_token const& token) noexcept;

        bool IsCurrentInstance();
        hstring Key();

    private:
        void MarshalArguments(Windows::ApplicationModel::Activation::IActivatedEventArgs const& args);
        Windows::ApplicationModel::Activation::IActivatedEventArgs UnmarshalArguments();

        static INIT_ONCE s_initArgs;
        static Windows::ApplicationModel::Activation::IActivatedEventArgs s_args;

        winrt::event<Windows::Foundation::EventHandler<Windows::ApplicationModel::Activation::IActivatedEventArgs>> m_activatedEvent;

        bool m_isCurrentInstance;
        std::wstring m_key;
        wil::unique_mutex m_mutex;
        wil::unique_event m_innerActivated;
        wil::unique_event_watcher m_activationWatcher;
        shared_memory<AppInstanceData> m_shared;
        shared_memory<AppInstanceList> m_instanceList;
    };
}

namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct AppLifecycle : AppLifecycleT<AppLifecycle, implementation::AppLifecycle>
    {
    };
}
