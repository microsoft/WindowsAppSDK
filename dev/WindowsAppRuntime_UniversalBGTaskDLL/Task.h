// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "Task.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::Background::UniversalBGTask::implementation
{
    struct Task : TaskT<Task>
    {
        Task() = default;

        void Run(winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance taskInstance);
        winrt::com_ptr<winrt::Windows::ApplicationModel::Background::IBackgroundTask> m_bgTask = nullptr;
    };
}

namespace winrt::Microsoft::Windows::ApplicationModel::Background::UniversalBGTask::factory_implementation
{
    struct Task : TaskT<Task, implementation::Task>
    {
    };
}
