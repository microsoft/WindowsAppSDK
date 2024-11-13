// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "Task.h"
#include "Task.g.cpp"

using namespace winrt;
using namespace winrt::Windows::ApplicationModel::Background;
using namespace winrt::Windows::Storage;

namespace winrt::Microsoft::Windows::ApplicationModel::Background::UniversalBGTask::implementation
{
    inline constexpr CLSID IID_IBackgroundTask{ 2098451764, 64786, 17358, 140, 34, 234, 31, 241, 60, 6, 223 };

    void Task::Run(winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance taskInstance)
    {
        winrt::hstring lookupKey{ winrt::to_hstring(taskInstance.Task().TaskId()) };
        ApplicationDataContainer localSettings{ ApplicationData::Current().LocalSettings() };
        auto values{ localSettings.Values() };
        auto lookupValue{ values.Lookup(lookupKey) };
        winrt::guid comClsId{ winrt::unbox_value<winrt::guid>(lookupValue) };

        winrt::Windows::ApplicationModel::Background::IBackgroundTask bgTask;
        winrt::hresult hr{ CoCreateInstance(comClsId, nullptr, CLSCTX_LOCAL_SERVER, IID_IBackgroundTask, reinterpret_cast<void**>(&bgTask)) };
        bgTask.Run(taskInstance);
    }
}
