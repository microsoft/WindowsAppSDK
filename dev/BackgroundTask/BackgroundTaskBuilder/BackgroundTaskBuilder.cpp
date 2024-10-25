// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "BackgroundTaskBuilder.h"
#include "Microsoft.Windows.ApplicationModel.Background.BackgroundTaskBuilder.g.cpp"
#include <winrt/Windows.ApplicationModel.Activation.h>

namespace winrt
{
    using namespace winrt::Windows::ApplicationModel::Background;
    using namespace Windows::Storage;
}

namespace winrt::Microsoft::Windows::ApplicationModel::Background::implementation
{
    void BackgroundTaskBuilder::SetTaskEntryPointClsId(winrt::guid clsId)
    {
        m_taskEntryPointClsId = clsId;
    }

    void BackgroundTaskBuilder::Name(winrt::hstring name)
    {
        m_name = name;
    }

    void BackgroundTaskBuilder::SetTrigger(winrt::IBackgroundTrigger trigger)
    {
        m_trigger = trigger;
    }

    winrt::BackgroundTaskRegistration BackgroundTaskBuilder::Register()
    {
        winrt::BackgroundTaskBuilder builder;
        builder.Name(m_name);
        builder.SetTrigger(m_trigger);
        builder.TaskEntryPoint(L"Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.Task");
        winrt::BackgroundTaskRegistration taskRegistration = builder.Register();

        winrt::ApplicationDataContainer localSettings = winrt::ApplicationData::Current().LocalSettings();
        auto values = localSettings.Values();
        winrt::hstring lookupId = winrt::to_hstring(taskRegistration.TaskId());
        IInspectable obj = winrt::box_value(m_taskEntryPointClsId);
        values.Insert(lookupId, obj);

        return taskRegistration;
    }

    winrt::BackgroundTaskRegistration BackgroundTaskBuilder::Register(winrt::hstring taskName)
    {
        Name(taskName);
        return Register();
    }

}
