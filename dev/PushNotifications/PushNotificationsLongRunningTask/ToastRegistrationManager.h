// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <unordered_map>
#include <algorithm>
#include <vector>

// Custom case-insensitive hash and equality for std::wstring
struct CaseInsensitiveWStringHash
{
    size_t operator()(const std::wstring& str) const
    {
        std::wstring lowerStr = str;
        std::transform(lowerStr.begin(), lowerStr.end(), lowerStr.begin(), ::towlower);
        return std::hash<std::wstring>{}(lowerStr);
    }
};

struct CaseInsensitiveWStringEqual
{
    bool operator()(const std::wstring& left, const std::wstring& right) const
    {
        return _wcsicmp(left.c_str(), right.c_str()) == 0;
    }
};

class ToastRegistrationManager
{
public:
    ToastRegistrationManager();

    void Add(std::wstring const& processName, std::wstring const& toastAppId);

    void Remove(std::wstring const& processName);

    std::wstring GetToastRegistration(std::wstring const& processName);

private:
    winrt::Windows::Storage::ApplicationDataContainer m_toastStorage{ nullptr };

    std::unordered_map<std::wstring, std::wstring, CaseInsensitiveWStringHash, CaseInsensitiveWStringEqual> m_registrationMap = {};
    wil::srwlock m_lock;
};
