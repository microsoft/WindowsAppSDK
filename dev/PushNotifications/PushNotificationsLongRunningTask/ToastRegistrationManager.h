// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <unordered_map>
#include <algorithm>
#include <vector>

class ToastRegistrationManager
{
public:
    ToastRegistrationManager() = default;

    void Add(std::wstring const& processName, std::wstring const& appId);

    void Remove(std::wstring const& processName);

    std::wstring GetToastRegistration(std::wstring const& processName);

private:
    std::unordered_map<std::wstring, std::wstring> m_registrationMap = {};
    wil::srwlock m_lock;
};
