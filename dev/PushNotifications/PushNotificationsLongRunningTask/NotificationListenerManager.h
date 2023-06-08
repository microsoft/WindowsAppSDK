// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <map>
#include <string>
#include <vector>

class NotificationListenerManager
{
public:
    NotificationListenerManager() {};

    // This function has to be called after initializing the ForegroundSinkManager during Platform initialization
    void Initialize(std::shared_ptr<ForegroundSinkManager> foregroundSinkManager, std::shared_ptr<ToastRegistrationManager> toastRegistrationManager);

    void SetAppIdMapping(std::map<std::wstring, std::pair<std::wstring, winrt::guid>>& appIdList);

    void AddListener(std::wstring const& appId, std::wstring const& processName, winrt::guid const& comServerClsid);
    void RemoveListener(std::wstring appId);

    bool IsEmpty();

private:
    wil::srwlock m_lock;

    std::map<std::wstring, Microsoft::WRL::AgileRef> m_notificationListeners;
    std::shared_ptr<ForegroundSinkManager> m_foregroundSinkManager;
    std::shared_ptr<ToastRegistrationManager> m_toastRegistrationManager;
};
