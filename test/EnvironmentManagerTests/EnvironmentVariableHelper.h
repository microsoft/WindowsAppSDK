// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "pch.h"

using namespace winrt::Microsoft::ProjectReunion;
using namespace winrt::Windows::Foundation::Collections;
typedef IMapView<winrt::hstring, winrt::hstring> EnvironmentVariables;

inline constexpr PCWSTR c_userEvRegLocation = L"Environment";
inline constexpr PCWSTR c_machineEvRegLocation = L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment";

inline EnvironmentVariables GetEnvironmentVariablesFromRegistry(HKEY hKey)
{
    StringMap environmentVariables;

    DWORD sizeOfLongestNameInCharacters;
    DWORD sizeOfLongestValueInCharacters;
    DWORD numberOfValues;

    THROW_IF_FAILED(RegQueryInfoKeyW(
        hKey
        , nullptr // lpClass
        , nullptr // lpcchClass
        , nullptr // lpReserved
        , nullptr // lpcSubKeys
        , nullptr // lpcbMaxSubKeyLen
        , nullptr // lpcbMaxCLassLen
        , &numberOfValues //lpcValues
        , &sizeOfLongestNameInCharacters
        , &sizeOfLongestValueInCharacters
        , nullptr // lpcmSecurityDescriptor
        , nullptr)); // lpftLastWriteTime

    // +1 for null character
    const DWORD c_nameLength = sizeOfLongestNameInCharacters + 1;
    const DWORD c_valueSizeInBytes = sizeOfLongestValueInCharacters * sizeof(WCHAR);

    std::unique_ptr<wchar_t[]> environmentVariableName(new wchar_t[c_nameLength]);
    std::unique_ptr<BYTE[]> environmentVariableValue(new BYTE[c_valueSizeInBytes]);

    for (DWORD valueIndex = 0; valueIndex < numberOfValues; valueIndex++)
    {
        DWORD nameLength = c_nameLength;
        DWORD valueSize = c_valueSizeInBytes;
        LSTATUS enumerationStatus = RegEnumValueW(hKey
            , valueIndex
            , environmentVariableName.get()
            , &nameLength
            , nullptr
            , nullptr
            , environmentVariableValue.get()
            , &valueSize);

        // An empty name indicates the default value.
        if (nameLength == 0)
        {
            continue;
        }

        // If there was an error getting the value
        if (enumerationStatus != ERROR_SUCCESS && enumerationStatus != ERROR_NO_MORE_ITEMS)
        {
            THROW_HR(HRESULT_FROM_WIN32(enumerationStatus));
        }

        environmentVariableValue.get()[valueSize] = L'\0';
        environmentVariables.Insert(environmentVariableName.get(), reinterpret_cast<PWSTR>(environmentVariableValue.get()));

        environmentVariableName.get()[0] = L'\0';
        environmentVariableValue.reset(new BYTE[c_valueSizeInBytes]);
    }

    return environmentVariables.GetView();
}

inline EnvironmentVariables GetEnvironmentVariablesForUser()
{
    wil::unique_hkey environmentVariablesHKey;
    THROW_IF_FAILED(HRESULT_FROM_WIN32(RegOpenKeyEx(HKEY_CURRENT_USER, c_userEvRegLocation, 0, KEY_READ, environmentVariablesHKey.addressof())));
    return GetEnvironmentVariablesFromRegistry(environmentVariablesHKey.get());
}

inline EnvironmentVariables GetEnvironmentVariablesForMachine()
{
    wil::unique_hkey environmentVariablesHKey;
    THROW_IF_FAILED(HRESULT_FROM_WIN32(RegOpenKeyEx(HKEY_LOCAL_MACHINE, c_machineEvRegLocation, 0, KEY_READ, environmentVariablesHKey.addressof())));
    return GetEnvironmentVariablesFromRegistry(environmentVariablesHKey.get());
}

inline EnvironmentVariables GetEnvironmentVariablesForProcess()
{
    //Get the pointer to the process block
    PWSTR environmentVariablesString{ GetEnvironmentStrings() };
    THROW_HR_IF_NULL(E_POINTER, environmentVariablesString);

    StringMap environmentVariables;
    for (auto environmentVariableOffset = environmentVariablesString; *environmentVariableOffset; environmentVariableOffset += wcslen(environmentVariableOffset) + 1)
    {
        auto delimiter{ wcschr(environmentVariableOffset, L'=') };
        FAIL_FAST_HR_IF_NULL(E_UNEXPECTED, delimiter);
        std::wstring variableName(environmentVariableOffset, 0, delimiter - environmentVariableOffset);
        auto variableValue{ delimiter + 1 };
        environmentVariables.Insert(variableName, variableValue);
    }

    THROW_IF_WIN32_BOOL_FALSE(FreeEnvironmentStrings(environmentVariablesString));

    return environmentVariables.GetView();
}

/// Compares two IMapView<winrt::hstring, winrt::hstring> collections for
/// 1. Have the same size
/// 2. All the keys in underTest are in real
/// 3. All the values in underTest are in real
/// @param underTest The EnvironmentVariables from EnvironmentManager
/// @param real The Environment Variables that came from GetEnvironmentStrings
/// @note This test will alwayse use underTest to compare to real.  As long as the size, keys, and values
/// are compared from underTest to real this will fail in the case that any keys are different, or any values are different
inline void CompareIMapViews(EnvironmentVariables fromEnvironmentManager, EnvironmentVariables fromWin32)
{
    auto sizeMessage = wil::str_printf<wil::unique_cotaskmem_string>(
        L"Size of fromEnvironmentManager Collection: %i\r\n Size of Win32 Collection: %i", fromEnvironmentManager.Size(), fromWin32.Size());

    WEX::Logging::Log::Comment(sizeMessage.get());
    // Make sure the sizes are the same.
    VERIFY_ARE_EQUAL(fromEnvironmentManager.Size(), fromWin32.Size());

    if (fromEnvironmentManager.Size() == 0)
    {
        return;
    }

    auto environmentManagerIterator = fromEnvironmentManager.First();
    do
    {
        // Make sure the same key exists in both collections
        auto environmentManagerKey = environmentManagerIterator.Current().Key();

        auto logMessage = wil::str_printf<wil::unique_cotaskmem_string>(
            L"Key from environment Manager: %ls", environmentManagerKey.c_str());

        WEX::Logging::Log::Comment(logMessage.get());

        VERIFY_IS_TRUE(fromWin32.HasKey(environmentManagerKey));

        // Make sure they have the same value
        auto environmentManagerValue = environmentManagerIterator.Current().Value();

        auto valueMessage = wil::str_printf<wil::unique_cotaskmem_string>(
            L"Value from environment Manager: %ls\r\nValue from real: %ls", environmentManagerValue.c_str(), fromWin32.Lookup(environmentManagerKey).c_str());

        WEX::Logging::Log::Comment(valueMessage.get());
        VERIFY_ARE_EQUAL(environmentManagerValue, fromWin32.Lookup(environmentManagerKey));
        environmentManagerIterator.MoveNext();
    } while (environmentManagerIterator.HasCurrent());
}
