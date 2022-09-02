// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "pch.h"
#include "TestCommon.h"

using namespace winrt::Microsoft::Windows::System;
using namespace winrt::Windows::Foundation::Collections;
typedef IMapView<winrt::hstring, winrt::hstring> EnvironmentVariables;

inline EnvironmentVariables GetEnvironmentVariablesFromRegistry(HKEY hKey)
{
    StringMap environmentVariables{};

    DWORD sizeOfLongestNameInCharacters{};
    DWORD sizeOfLongestValueInCharacters{};
    DWORD numberOfValues{};

    THROW_IF_WIN32_ERROR(RegQueryInfoKeyW(
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
    const DWORD c_nameLength{ sizeOfLongestNameInCharacters + 1 };
    const DWORD c_valueSizeInBytes{ sizeOfLongestValueInCharacters * sizeof(WCHAR) };

    std::unique_ptr<wchar_t[]> environmentVariableName{ new wchar_t[c_nameLength] };
    std::unique_ptr<BYTE[]> environmentVariableValue{ new BYTE[c_valueSizeInBytes] };

    for (DWORD valueIndex = 0; valueIndex < numberOfValues; valueIndex++)
    {
        DWORD nameLength = c_nameLength;
        DWORD valueSize = c_valueSizeInBytes;
        LSTATUS enumerationStatus{ RegEnumValueW(hKey
            , valueIndex
            , environmentVariableName.get()
            , &nameLength
            , nullptr
            , nullptr
            , environmentVariableValue.get()
            , &valueSize) };

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

inline std::wstring GetEnvironmentVariableFromRegistry(const std::wstring variableKey, HKEY KeyToOpen)
{
    DWORD sizeOfEnvironmentValue{};

    // See how big we need the buffer to be
    LSTATUS queryResult{ RegQueryValueEx(KeyToOpen, variableKey.c_str(), 0, nullptr, nullptr, &sizeOfEnvironmentValue) };

    if (queryResult != ERROR_SUCCESS)
    {
        if (queryResult == ERROR_FILE_NOT_FOUND)
        {
            return L"";
        }

        THROW_HR(HRESULT_FROM_WIN32((queryResult)));
    }

    std::unique_ptr<wchar_t[]> environmentValue{ new wchar_t[sizeOfEnvironmentValue] };
    THROW_IF_FAILED(HRESULT_FROM_WIN32((RegQueryValueEx(KeyToOpen, variableKey.c_str(), 0, nullptr, (LPBYTE)environmentValue.get(), &sizeOfEnvironmentValue))));

    return std::wstring{ environmentValue.get() };
}

inline wil::unique_hkey GetKeyToEnvironmentVariables(bool isUser)
{
    wil::unique_hkey environmentVariablesHKey{};
    if (isUser)
    {
        THROW_IF_WIN32_ERROR(RegOpenKeyEx(HKEY_CURRENT_USER, c_UserEvRegLocation, 0, KEY_ALL_ACCESS, environmentVariablesHKey.addressof()));
    }
    else
    {
        THROW_IF_WIN32_ERROR(RegOpenKeyEx(HKEY_LOCAL_MACHINE, c_MachineEvRegLocation, 0, KEY_ALL_ACCESS, environmentVariablesHKey.addressof()));
    }

    return environmentVariablesHKey;
}

inline EnvironmentVariables GetEnvironmentVariablesForUser()
{
    wil::unique_hkey environmentVariablesHKey{};
    THROW_IF_WIN32_ERROR(RegOpenKeyEx(HKEY_CURRENT_USER, c_UserEvRegLocation, 0, KEY_READ, environmentVariablesHKey.addressof()));
    return GetEnvironmentVariablesFromRegistry(environmentVariablesHKey.get());
}

inline std::wstring GetEnvironmentVariableForUser(const std::wstring variableName)
{
    wil::unique_hkey environmentVariableHKey{};
    THROW_IF_WIN32_ERROR(RegOpenKeyEx(HKEY_CURRENT_USER, c_UserEvRegLocation, 0, KEY_READ, environmentVariableHKey.addressof()));
    return GetEnvironmentVariableFromRegistry(variableName, environmentVariableHKey.get());
}

inline std::wstring GetEnvironmentVariableForMachine(const std::wstring variableName)
{
    wil::unique_hkey environmentVariableHKey{};
    THROW_IF_WIN32_ERROR(RegOpenKeyEx(HKEY_LOCAL_MACHINE, c_MachineEvRegLocation, 0, KEY_READ, environmentVariableHKey.addressof()));
    return GetEnvironmentVariableFromRegistry(variableName, environmentVariableHKey.get());
}

inline std::wstring GetEnvironmentVariableForProcess(const std::wstring variableName)
{
    // Get the size of the buffer.
    DWORD sizeNeededInCharacters{ ::GetEnvironmentVariable(variableName.c_str(), nullptr, 0) };

    // If we got an error
    if (sizeNeededInCharacters == 0)
    {
        DWORD lastError = GetLastError();

        if (lastError == ERROR_ENVVAR_NOT_FOUND)
        {
            return L"";
        }
        else
        {
            THROW_HR(HRESULT_FROM_WIN32(lastError));
        }
    }

    std::wstring environmentVariableValue{};

    environmentVariableValue.resize(sizeNeededInCharacters - 1);
    DWORD getResult{ ::GetEnvironmentVariable(variableName.c_str(), &environmentVariableValue[0], sizeNeededInCharacters) };

    if (getResult == 0)
    {
        THROW_HR(HRESULT_FROM_WIN32(GetLastError()));
    }

    return environmentVariableValue;
}

inline void InjectIntoPath(bool isProcess, bool isUser, const std::wstring& pathPart, UINT32 index)
{
    std::wstring existingPath{};

    if (isProcess)
    {
        existingPath = GetEnvironmentVariableForProcess(c_PathName);
    }
    else if (isUser)
    {
        existingPath = GetEnvironmentVariableForUser(c_PathName);
    }
    else
    {
        existingPath = GetEnvironmentVariableForMachine(c_PathName);
    }

    std::list<std::wstring> pathParts{};

    wchar_t* token;
    wchar_t* tokenizationState;
    token = wcstok_s(existingPath.data(), L";", &tokenizationState);
    while (token != nullptr)
    {
        std::wstring pathPartToken{ token };

        pathPartToken += L';';

        pathParts.push_back(pathPartToken);

        token = wcstok_s(NULL, L";", &tokenizationState);
    }

    // Since this will inject something into the path to be removed
    // The injection should happen around other items.
    // +2 to make sure the injection site is surrounded.
    if (pathParts.size() <= index)
    {
        for (UINT32 partToAdd = static_cast<UINT32>(pathParts.size()); partToAdd < index + 2; partToAdd++)
        {
            std::wstring stringToAdd(L"index");
            stringToAdd.append(std::to_wstring((partToAdd)));
            stringToAdd.append(L";");

            pathParts.push_back(stringToAdd);
        }
    }

    UINT32 currentIndex{};
    for (auto iterator = pathParts.begin(); iterator != pathParts.end(); ++iterator)
    {
        if (currentIndex == index)
        {
            std::wstring pathPartToInsert{ pathPart };

            if (pathPartToInsert.back() != L';')
            {
                pathPartToInsert += L';';
            }

            pathParts.insert(iterator, pathPartToInsert);
            break;
        }

        currentIndex++;
    }

    std::wstring newPath{};
    for (auto part : pathParts)
    {
        newPath += part;
    }

    if (isProcess)
    {
        SetEnvironmentVariable(c_PathName, newPath.c_str());
    }
    else
    {
        THROW_IF_WIN32_ERROR(RegSetValueEx(
            GetKeyToEnvironmentVariables(isUser).get()
            , c_PathName
            , 0
            , REG_EXPAND_SZ
            , reinterpret_cast<const BYTE*>(newPath.c_str())
            , static_cast<DWORD>((newPath.size() + 1) * sizeof(wchar_t))));
    }

}

inline void InjectIntoPathExt(bool isProcess, bool isUser, const std::wstring& pathExtPart, UINT32 index)
{
    std::wstring existingPathExt{};

    if (isProcess)
    {
        existingPathExt = GetEnvironmentVariableForProcess(c_PathExtName);
    }
    else if (isUser)
    {
        existingPathExt = GetEnvironmentVariableForUser(c_PathExtName);
    }
    else
    {
        existingPathExt = GetEnvironmentVariableForMachine(c_PathExtName);
    }

    std::list<std::wstring> pathExtParts{};

    wchar_t* token;
    wchar_t* tokenizationState;
    token = wcstok_s(existingPathExt.data(), L";", &tokenizationState);
    while (token != nullptr)
    {
        std::wstring pathExtPartToken{ token };

        pathExtPartToken += L';';

        pathExtParts.push_back(pathExtPartToken);

        token = wcstok_s(NULL, L";", &tokenizationState);
    }

    // Since this will inject something into the path to be removed
    // The injection should happen around other items.
    // +2 to make sure the injection site is surrounded.
    if (pathExtParts.size() <= index)
    {
        for (UINT32 partToAdd = static_cast<UINT32>(pathExtParts.size()); partToAdd < index + 2; partToAdd++)
        {
            std::wstring stringToAdd(L"index");
            stringToAdd.append(std::to_wstring((partToAdd)));
            stringToAdd.append(L";");

            pathExtParts.push_back(stringToAdd);
        }
    }

    UINT32 currentIndex{};
    for (auto iterator = pathExtParts.begin(); iterator != pathExtParts.end(); ++iterator)
    {
        if (currentIndex == index)
        {
            std::wstring pathExtPartToInsert{ pathExtPart };

            if (pathExtPartToInsert.back() != L';')
            {
                pathExtPartToInsert += L';';
            }

            pathExtParts.insert(iterator, pathExtPartToInsert);
            break;
        }

        currentIndex++;
    }

    std::wstring newPath{};
    for (auto pathPart : pathExtParts)
    {
        newPath += pathPart;
    }

    if (isProcess)
    {
        SetEnvironmentVariable(c_PathExtName, newPath.c_str());
    }
    else
    {
        THROW_IF_WIN32_ERROR(RegSetValueEx(
            GetKeyToEnvironmentVariables(isUser).get()
            , c_PathExtName
            , 0
            , REG_EXPAND_SZ
            , reinterpret_cast<const BYTE*>(newPath.c_str())
            , static_cast<DWORD>((newPath.size() + 1) * sizeof(wchar_t))));
    }

}

inline std::wstring GetSecondValueFromPath(bool isProcess, bool isUser)
{
    std::wstring existingPath{};

    if (isProcess)
    {
        existingPath = GetEnvironmentVariableForProcess(c_PathName);
    }
    else if (isUser)
    {
        existingPath = GetEnvironmentVariableForUser(c_PathName);
    }
    else
    {
        existingPath = GetEnvironmentVariableForMachine(c_PathName);
    }

    int index{ 0 };
    wchar_t* token;
    wchar_t* tokenizationState;
    token = wcstok_s(existingPath.data(), L";", &tokenizationState);
    while (token != nullptr)
    {
        std::wstring pathPartToken{ token };

        pathPartToken += L';';

        if (index == 1)
        {
            return pathPartToken;
        }

        token = wcstok_s(NULL, L";", &tokenizationState);
        index++;
    }

    return {};
}

inline std::wstring GetSecondValueFromPathExt(bool isProcess, bool isUser)
{
    std::wstring existingPath{};

    if (isProcess)
    {
        existingPath = GetEnvironmentVariableForProcess(c_PathExtName);
    }
    else if (isUser)
    {
        existingPath = GetEnvironmentVariableForUser(c_PathExtName);
    }
    else
    {
        existingPath = GetEnvironmentVariableForMachine(c_PathExtName);
    }

    int index{ 0 };
    wchar_t* token;
    wchar_t* tokenizationState;
    token = wcstok_s(existingPath.data(), L";", &tokenizationState);
    while (token != nullptr)
    {
        std::wstring pathPartToken{ token };

        pathPartToken += L';';

        if (index == 1)
        {
            return pathPartToken;
        }

        token = wcstok_s(NULL, L";", &tokenizationState);
        index++;
    }

    return {};
}


inline EnvironmentVariables GetEnvironmentVariablesForMachine()
{
    wil::unique_hkey environmentVariablesHKey{};
    THROW_IF_WIN32_ERROR(RegOpenKeyEx(HKEY_LOCAL_MACHINE, c_MachineEvRegLocation, 0, KEY_READ, environmentVariablesHKey.addressof()));
    return GetEnvironmentVariablesFromRegistry(environmentVariablesHKey.get());
}


inline EnvironmentVariables GetEnvironmentVariablesForProcess()
{
    //Get the pointer to the process block
    PWSTR environmentVariablesString{ GetEnvironmentStrings() };
    THROW_HR_IF_NULL(E_POINTER, environmentVariablesString);

    StringMap environmentVariables{};
    for (auto environmentVariableOffset = environmentVariablesString; *environmentVariableOffset; environmentVariableOffset += wcslen(environmentVariableOffset) + 1)
    {
        auto delimiter{ wcschr(environmentVariableOffset, L'=') };
        FAIL_FAST_HR_IF_NULL(E_UNEXPECTED, delimiter);
        std::wstring variableName{ environmentVariableOffset, 0, static_cast<std::size_t> (delimiter - environmentVariableOffset) };
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
    auto sizeMessage{ wil::str_printf<wil::unique_cotaskmem_string>(
        L"Size of fromEnvironmentManager Collection: %i\r\n Size of Win32 Collection: %i", fromEnvironmentManager.Size(), fromWin32.Size()) };

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
