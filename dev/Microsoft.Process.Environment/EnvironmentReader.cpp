// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include <EnvironmentReader.h>
#include <EnvironmentReader.g.cpp>

namespace winrt::Microsoft::ProjectReunion::implementation
{

    EnvironmentReader::EnvironmentReader(Scope const& scope)
        : m_Scope(scope) { }

    ProjectReunion::EnvironmentReader EnvironmentReader::GetForProcess()
    {
        ProjectReunion::EnvironmentReader environmentReader{ nullptr };
        environmentReader = winrt::make<implementation::EnvironmentReader>(Scope::Process);
        return environmentReader;
    }

    Microsoft::ProjectReunion::EnvironmentReader EnvironmentReader::GetForUser()
    {
        ProjectReunion::EnvironmentReader environmentReader{ nullptr };
        environmentReader = winrt::make<implementation::EnvironmentReader>(Scope::User);
        return environmentReader;
    }

    Microsoft::ProjectReunion::EnvironmentReader EnvironmentReader::GetForMachine()
    {
        ProjectReunion::EnvironmentReader environmentReader{ nullptr };
        environmentReader = winrt::make<implementation::EnvironmentReader>(Scope::Machine);
        return environmentReader;
    }

    Windows::Foundation::Collections::IMapView<hstring, hstring> EnvironmentReader::GetEnvironmentVariables()
    {
        Windows::Foundation::Collections::StringMap environmentVariables;

        if (m_Scope == Scope::Process)
        {
            environmentVariables = GetProcessEnvironmentVariables();
        }
        else
        {
            environmentVariables = GetUserOrMachineEnvironmentVariables();
        }

        return environmentVariables.GetView();
    }

    hstring EnvironmentReader::GetEnvironmentVariable(hstring const& variableName)
    {
        if (variableName.empty())
        {
            THROW_HR(E_INVALIDARG);
        }

        if (m_Scope == Scope::Process)
        {
            return hstring(GetProcessEnvironmentVariable(std::wstring(variableName)));
        }
        else
        {
            return hstring(GetUserOrMachineEnvironmentVariable(m_Scope, std::wstring(variableName)));
        }
    }

    StringMap EnvironmentReader::GetProcessEnvironmentVariables() const
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

        return environmentVariables;
    }

    StringMap EnvironmentReader::GetUserOrMachineEnvironmentVariables() const
    {
        StringMap environmentVariables;
        wil::unique_hkey environmentVariablesHKey = GetRegHKeyForEVUserAndMachineScope(m_Scope);

        // While this way of calculating the max size of the names,
        // values, and total number of entries includes two calls
        // to the registry, I believe this is superior to
        // using a do/while or a while with a prime
        // because there is no chance of the loop iterating more than
        // is needed AND the size of the name and value arrays are
        // only as big as the biggest name or value.

        DWORD sizeOfLongestNameInCharacters;
        DWORD sizeOfLongestValueInCharacters;
        DWORD numberOfValues;

        THROW_IF_WIN32_ERROR(RegQueryInfoKeyW(environmentVariablesHKey.get(),
            nullptr, nullptr, nullptr, nullptr, nullptr, nullptr,
            &numberOfValues, &sizeOfLongestNameInCharacters,
            &sizeOfLongestValueInCharacters, nullptr, nullptr));

        // +1 for null character
        const DWORD c_nameLength = sizeOfLongestNameInCharacters + 1;
        const DWORD c_valueSizeInBytes{ static_cast<DWORD>(sizeOfLongestValueInCharacters * sizeof(WCHAR)) };

        std::unique_ptr<wchar_t[]> environmentVariableName(new wchar_t[c_nameLength]);
        std::unique_ptr<BYTE[]> environmentVariableValue(new BYTE[c_valueSizeInBytes]);

        for (DWORD valueIndex = 0; valueIndex < numberOfValues; valueIndex++)
        {
            DWORD nameLength = c_nameLength;
            DWORD valueSize = c_valueSizeInBytes;
            LSTATUS enumerationStatus = RegEnumValueW(environmentVariablesHKey.get()
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

        return environmentVariables;
    }
}
