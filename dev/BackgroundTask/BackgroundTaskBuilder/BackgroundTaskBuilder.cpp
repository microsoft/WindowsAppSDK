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
    void BackgroundTaskBuilder::SetTaskEntryPointClsid(winrt::guid clsId)
    {
        m_taskEntryPointClsid = clsId;
    }

    void BackgroundTaskBuilder::Name(winrt::hstring name)
    {
        m_name = name;
    }

    void BackgroundTaskBuilder::TaskGroup(winrt::BackgroundTaskRegistrationGroup TaskGroup)
    {
        m_builder.TaskGroup(TaskGroup);
    }

    winrt::BackgroundTaskRegistrationGroup BackgroundTaskBuilder::TaskGroup()
    {
        return m_builder.TaskGroup();
    }

    void BackgroundTaskBuilder::SetTrigger(winrt::IBackgroundTrigger trigger)
    {
        m_builder.SetTrigger(trigger);
    }

    void BackgroundTaskBuilder::AddCondition(winrt::IBackgroundCondition condition)
    {
        m_builder.AddCondition(condition);
    }

    winrt::BackgroundTaskRegistration BackgroundTaskBuilder::Register()
    {
        m_builder.Name(m_name);
        m_builder.TaskEntryPoint(L"Microsoft.Windows.ApplicationModel.Background.UniversalBGTask.Task");
        winrt::BackgroundTaskRegistration taskRegistration = m_builder.Register();

        winrt::ApplicationDataContainer localSettings = winrt::ApplicationData::Current().LocalSettings();
        auto values = localSettings.Values();
        winrt::hstring lookupId = winrt::to_hstring(taskRegistration.TaskId());
        IInspectable obj = winrt::box_value(m_taskEntryPointClsid);
        values.Insert(lookupId, obj);

        return taskRegistration;
    }

    winrt::BackgroundTaskRegistration BackgroundTaskBuilder::Register(winrt::hstring taskName)
    {
        Name(taskName);
        return Register();
    }

}
