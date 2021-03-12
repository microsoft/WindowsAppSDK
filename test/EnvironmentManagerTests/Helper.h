#pragma once
#include "pch.h"

using namespace winrt::Microsoft::ProjectReunion; // for EnvironmentManager
using namespace winrt::Windows::Foundation::Collections; // for IMapView
typedef IMapView<winrt::hstring, winrt::hstring> EnvironmentVariables;

inline const wchar_t* USER_EV_REG_LOCATION = L"Environment";
inline const wchar_t* MACHINE_EV_REG_LOCATION = L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment";

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
    const DWORD NAME_LENGTH = sizeOfLongestNameInCharacters + 1;
    const DWORD VALUE_SIZE_IN_BYTES = sizeOfLongestValueInCharacters * sizeof(WCHAR);

    std::unique_ptr<wchar_t[]> environmentVariableName(new wchar_t[NAME_LENGTH]);
    std::unique_ptr<BYTE[]> environmentVariableValue(new BYTE[VALUE_SIZE_IN_BYTES]);

    for (int valueIndex = 0; valueIndex < numberOfValues; valueIndex++)
    {
        DWORD nameLength = NAME_LENGTH;
        DWORD valueSize = VALUE_SIZE_IN_BYTES;
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

        environmentVariables.Insert(environmentVariableName.get(), reinterpret_cast<LPWSTR>(environmentVariableValue.get()));

        environmentVariableName.reset(new wchar_t[NAME_LENGTH]);
        environmentVariableValue.reset(new BYTE[VALUE_SIZE_IN_BYTES]);
    }

    return environmentVariables.GetView();
}

inline EnvironmentVariables GetEnvironmentVariablesForUser()
{
    wil::unique_hkey environmentVariablesHKey;
    THROW_IF_FAILED(HRESULT_FROM_WIN32(RegOpenKeyEx(HKEY_CURRENT_USER, USER_EV_REG_LOCATION, 0, KEY_READ, environmentVariablesHKey.addressof())));
    return GetEnvironmentVariablesFromRegistry(environmentVariablesHKey.get());
}

inline EnvironmentVariables GetEnvironmentVariablesForMachine()
{
    wil::unique_hkey environmentVariablesHKey;
    THROW_IF_FAILED(HRESULT_FROM_WIN32(RegOpenKeyEx(HKEY_LOCAL_MACHINE, MACHINE_EV_REG_LOCATION, 0, KEY_READ, environmentVariablesHKey.addressof())));
    return GetEnvironmentVariablesFromRegistry(environmentVariablesHKey.get());
}

inline EnvironmentVariables GetEnvironmentVariablesForProcess()
{
    LPWSTR environmentVariablesBlock = GetEnvironmentStrings();
    VERIFY_IS_NOT_NULL(environmentVariablesBlock);

    LPTSTR variable;
    variable = (LPTSTR)environmentVariablesBlock;

    StringMap environmentVariables;
    while (*variable)
    {
        std::wstring environmentVariable(variable);
        size_t locationOfNull = environmentVariable.find_last_of(L'=');

        environmentVariables.Insert(environmentVariable.substr(0, locationOfNull), environmentVariable.substr(locationOfNull + 1));

        variable += lstrlen(variable) + 1;
    }

    VERIFY_WIN32_BOOL_SUCCEEDED(FreeEnvironmentStrings(environmentVariablesBlock));

    return environmentVariables.GetView();
}

/// <summary>
/// Compares two IMapView<winrt::hstring, winrt::hstring> collections for
/// 1. Have the same size
/// 2. All the keys in <paramref name="underTest" /> are in <paramref name="real" />
/// 3. All the values in <paramref name="underTest" /> are in <paramref name="real" />
/// </summary>
/// <param name="underTest">The EnvironmentVariables from the WInRT API that is being tested</param>
/// <param name="real">The Environment Variables that came from GetEnvironmentStrings</param>
/// <remarks>
/// This test will alwayse use <paramref name="underTest" /> to compare to <paramref name="real" />.  As long as the size, keys, and values
/// are compared from <paramref name="underTest" /> to <paramref name="real" /> this will fail in the case that any keys are different, or any values are different
/// </remarks>
inline void CompareIMapViews(EnvironmentVariables fromWinRT, EnvironmentVariables fromWin32)
{
    std::wstringstream sizeMessage;
    sizeMessage << L"Size of WinRT Collection: ";
    sizeMessage << fromWinRT.Size() << "\r\n";
    sizeMessage << L"Size of Win32 Collection: ";
    sizeMessage << fromWin32.Size();

    WEX::Logging::Log::Comment(sizeMessage.str().c_str());
    // Make sure the sizes are the same.
    VERIFY_ARE_EQUAL(fromWinRT.Size(), fromWin32.Size());

    if (fromWinRT.Size() == 0)
    {
        return;
    }

    auto winRTIterator = fromWinRT.First();
    do
    {
        // Make sure the same key exists in both collections
        auto winRTKey = winRTIterator.Current().Key();

        std::wstringstream logMessage;
        logMessage << L"Key from WinRT: ";
        logMessage << winRTKey.c_str();

        WEX::Logging::Log::Comment(logMessage.str().c_str());

        VERIFY_IS_TRUE(fromWin32.HasKey(winRTKey));

        // Make sure they have the same value
        auto winRTValue = winRTIterator.Current().Value();

        std::wstringstream valueMessage;
        valueMessage << L"Value from test: ";
        valueMessage << winRTValue.c_str() << L"\r\n";
        valueMessage << L"Value from real: " << fromWin32.Lookup(winRTKey).c_str();

        WEX::Logging::Log::Comment(valueMessage.str().c_str());
        VERIFY_ARE_EQUAL(winRTValue, fromWin32.Lookup(winRTKey));
        winRTIterator.MoveNext();
    } while (winRTIterator.HasCurrent());
}
