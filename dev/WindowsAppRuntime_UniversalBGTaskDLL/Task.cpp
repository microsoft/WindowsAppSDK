// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "Task.h"
#if __has_include("Task.g.cpp")
#include "Task.g.cpp"
#endif
#include <wil/result_macros.h>

using namespace winrt;
using namespace winrt::Windows::ApplicationModel::Background;
using namespace winrt::Windows::Storage;

namespace winrt::Microsoft::Windows::ApplicationModel::Background::UniversalBGTask::implementation
{
    void Task::Run(winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance taskInstance)
    {
        winrt::hstring lookupStr = winrt::to_hstring(taskInstance.Task().TaskId());
        ApplicationDataContainer localSettings = ApplicationData::Current().LocalSettings();
        auto values = localSettings.Values();
        auto lookupobj = values.Lookup(lookupStr);
        winrt::guid comClsId = winrt::unbox_value<winrt::guid>(lookupobj);

        THROW_IF_FAILED(CoCreateInstance(comClsId, nullptr, CLSCTX_LOCAL_SERVER, winrt::guid_of<winrt::Windows::ApplicationModel::Background::IBackgroundTask>(), winrt::put_abi(m_bgTask)));
        m_bgTask.Run(taskInstance);
    }
}
