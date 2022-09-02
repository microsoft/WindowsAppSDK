// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <unordered_map>
#include <algorithm>
#include <vector>

class ToastRegistrationManager
{
public:
    ToastRegistrationManager();

    void Add(std::wstring const& processName, std::wstring const& toastAppId);

    void Remove(std::wstring const& processName);

    std::wstring GetToastRegistration(std::wstring const& processName);

private:
    winrt::Windows::Storage::ApplicationDataContainer m_toastStorage{ nullptr };

    std::unordered_map<std::wstring, std::wstring> m_registrationMap = {};
    wil::srwlock m_lock;
};
