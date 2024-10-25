// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include <winrt/Windows.ApplicationModel.Background.h>
#include "Microsoft.Windows.ApplicationModel.Background.BackgroundTaskBuilder.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::Background::implementation
{
    struct BackgroundTaskBuilder : BackgroundTaskBuilderT<BackgroundTaskBuilder>
    {
        BackgroundTaskBuilder() = default;
        void SetTaskEntryPointClsId(winrt::guid clsId);

        void
            SetTrigger(
                winrt::Windows::ApplicationModel::Background::IBackgroundTrigger trigger
            );


        void Name(winrt::hstring Name);
        winrt::hstring Name() { return m_name; }

        winrt::Windows::ApplicationModel::Background::BackgroundTaskRegistration Register();
        winrt::Windows::ApplicationModel::Background::BackgroundTaskRegistration Register(winrt::hstring taskName);

    private:
        winrt::guid m_taskEntryPointClsId;
        winrt::hstring m_name;
        winrt::Windows::ApplicationModel::Background::IBackgroundTrigger m_trigger;
    };
}

namespace winrt::Microsoft::Windows::ApplicationModel::Background::factory_implementation
{
    struct BackgroundTaskBuilder : BackgroundTaskBuilderT<BackgroundTaskBuilder, implementation::BackgroundTaskBuilder>
    {
    };
}
