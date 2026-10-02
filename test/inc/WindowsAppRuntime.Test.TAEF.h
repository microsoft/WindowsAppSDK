// Copyright (c) Microsoft Corporation and Contributors. All rights reserved.
// Licensed under the MIT License.

#ifndef __WINDOWSAPPRUNTIME_TEST_TAEF_H
#define __WINDOWSAPPRUNTIME_TEST_TAEF_H

namespace Test::TAEF
{
    inline std::filesystem::path GetDeploymentDir()
    {
        WEX::Common::String testDeploymentDir;
        WEX::TestExecution::RuntimeParameters::TryGetValue(L"TestDeploymentDir", testDeploymentDir);
        return static_cast<PCWSTR>(testDeploymentDir);
    }

    inline bool TryGetOption(
        _In_ PCWSTR name,
        WEX::Common::String& value)
    {
        HRESULT hr = WEX::TestExecution::RuntimeParameters::TryGetValue(name, value);
        if (!SUCCEEDED(hr))
        {
            VERIFY_ARE_EQUAL(hr, HRESULT_FROM_WIN32(ERROR_NOT_FOUND));
        }
        return SUCCEEDED(hr);
    }

    inline bool TryGetOption(
        _In_ PCWSTR name,
        UINT32& value)
    {
        WEX::Common::String valueString;
        if (!TryGetOption(name, valueString))
        {
            return false;
        }
        WCHAR * s = nullptr;
        int base = ((wcslen(valueString) >= 2) && (valueString[0] == L'0') && (valueString[1] == L'x')) ? 16 : 10;
        unsigned long n = wcstoul(valueString, &s, base);
        if (*valueString != L'\0')
        {
            WEX::Common::String invalidParameter;
            invalidParameter.Format(L"Invalid parameter: /p:%s=<n>", name);
            return false;
        }
        value = n;
        return true;
    }

    inline bool IsEnabled(
        _In_ PCWSTR name,
        const WEX::Common::String& value,
        bool defaultValue = false)
    {
        if (value.GetLength() == 0)
        {
            return defaultValue;
        }
        WCHAR * s = nullptr;
        long n = wcstol(value, &s, 10);
        if ((*s != L'\0') || ((n != 0) && (n != 1)))
        {
            WEX::Common::String invalidParameter;
            invalidParameter.Format(L"Invalid parameter: /p:%s=<0|1>", name);
            VERIFY_IS_TRUE(*s == L'\0', invalidParameter);
            VERIFY_IS_TRUE((n == 0) || (n == 1), invalidParameter);
        }
        return n != 0;
    }

    inline bool IsEnabled(
        _In_ PCWSTR name,
        bool defaultValue = false)
    {
        WEX::Common::String value;
        const bool ok = TryGetOption(name, value);
        if (!ok)
        {
            WEX::Common::String environmentVariableName;
            environmentVariableName.Format(L"STATEREPOSITORY_TEST_%s", name);
            WCHAR environmentVariable[10]{};
            const auto length{ GetEnvironmentVariableW(environmentVariableName, environmentVariable, ARRAYSIZE(environmentVariable)) };
            if ((length == 0) || (length > ARRAYSIZE(environmentVariable)))
            {
               return defaultValue;
            }
            value = environmentVariable;
        }
        return IsEnabled(name, value, defaultValue);
    }
}

#endif // __WINDOWSAPPRUNTIME_TEST_TAEF_H
