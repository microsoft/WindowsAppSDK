// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "Task.h"
#if __has_include("Task.g.cpp")
#include "Task.g.cpp"
#endif
#include <wil/result_macros.h>
#include <FrameworkUdk/Containment.h>

using namespace winrt;
using namespace winrt::Windows::ApplicationModel::Background;
using namespace winrt::Windows::Storage;

// 62755661: [2.0 Servicing][WASDK] Fix UniversalBGTask::Task::Run crash on missing CLSID / CoCreateInstance failure
#define WINAPPSDK_CHANGEID_62755661 62755661

namespace winrt::Microsoft::Windows::ApplicationModel::Background::UniversalBGTask::implementation
{
    void Task::Run(winrt::Windows::ApplicationModel::Background::IBackgroundTaskInstance taskInstance)
    {
        winrt::hstring lookupStr = winrt::to_hstring(taskInstance.Task().TaskId());
        ApplicationDataContainer localSettings = ApplicationData::Current().LocalSettings();
        auto values = localSettings.Values();
        auto lookupobj = values.Lookup(lookupStr);

        // 62755661: Guard the new crash-hardening behavior behind containment so apps pinned to an
        // earlier WinAppSDK patch level keep the original (throwing) behavior.
        if (WinAppSdk::Containment::IsChangeEnabled<WINAPPSDK_CHANGEID_62755661>())
        {
            // LocalSettings.Lookup returns S_OK with a null IInspectable when the key is missing.
            // Treat this as an orphaned OS task registration: log and unregister so the broker
            // stops re-firing it. Returning cleanly is preferred over throwing because thrown
            // exceptions are treated as transient by the broker and would be retried indefinitely.
            if (!lookupobj)
            {
                LOG_HR_MSG(
                    HRESULT_FROM_WIN32(ERROR_NOT_FOUND),
                    "UniversalBGTask: no CLSID stored in LocalSettings for TaskId='%ls'. Unregistering orphaned task.",
                    lookupStr.c_str());
                try
                {
                    taskInstance.Task().Unregister(true);
                }
                CATCH_LOG_MSG("UniversalBGTask: failed to unregister orphaned task TaskId='%ls'.", lookupStr.c_str());
                return;
            }

            winrt::guid comClsId = winrt::unbox_value<winrt::guid>(lookupobj);

            // CoCreateInstance can fail when the COM class isn't registered, the stored CLSID is
            // GUID_NULL, or the impl doesn't expose IBackgroundTask. Log the HR with the CLSID
            // for diagnostics and return; do not unregister, since the failure may be transient.
            wchar_t comClsIdStr[40]{};
            ::StringFromGUID2(comClsId, comClsIdStr, ARRAYSIZE(comClsIdStr));
            HRESULT coCreateHr = CoCreateInstance(comClsId, nullptr, CLSCTX_LOCAL_SERVER,
                winrt::guid_of<winrt::Windows::ApplicationModel::Background::IBackgroundTask>(),
                winrt::put_abi(m_bgTask));
            if (FAILED(coCreateHr))
            {
                LOG_HR_MSG(
                    coCreateHr,
                    "UniversalBGTask: CoCreateInstance failed for CLSID=%ls referenced by TaskId='%ls'.",
                    comClsIdStr,
                    lookupStr.c_str());
                return;
            }

            m_bgTask.Run(taskInstance);
        }
        else
        {
            // Original (pre-servicing) behavior, preserved for apps pinned to an earlier patch level.
            winrt::guid comClsId = winrt::unbox_value<winrt::guid>(lookupobj);

            THROW_IF_FAILED(CoCreateInstance(comClsId, nullptr, CLSCTX_LOCAL_SERVER, winrt::guid_of<winrt::Windows::ApplicationModel::Background::IBackgroundTask>(), winrt::put_abi(m_bgTask)));
            m_bgTask.Run(taskInstance);
        }
    }
}
