// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "Task.h"
#if __has_include("Task.g.cpp")
#include "Task.g.cpp"
#endif

using namespace winrt;
using namespace winrt::Windows::ApplicationModel::Background;
using namespace winrt::Windows::Storage;

namespace winrt::Microsoft::Windows::ApplicationModel::Background::UniversalBGTask::implementation
{
    inline constexpr CLSID IID_IBackgroundTask = { 2098451764, 64786, 17358, 140, 34, 234, 31, 241, 60, 6, 223 };
    void Task::Run(winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance taskInstance)
    {
        winrt::hstring lookupStr = winrt::to_hstring(taskInstance.Task().TaskId());
        ApplicationDataContainer localSettings = ApplicationData::Current().LocalSettings();
        auto values = localSettings.Values();
        auto lookupobj = values.Lookup(lookupStr);
        winrt::guid comClsId = winrt::unbox_value<winrt::guid>(lookupobj);

        winrt::Windows::ApplicationModel::Background::IBackgroundTask bgTask = nullptr;
        winrt::hresult hr = CoCreateInstance(comClsId, nullptr, CLSCTX_LOCAL_SERVER, IID_IBackgroundTask, reinterpret_cast<void**>(&bgTask));
        bgTask.Run(taskInstance);
    }
}
