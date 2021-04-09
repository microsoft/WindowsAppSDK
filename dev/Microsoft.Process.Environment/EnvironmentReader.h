// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include <EnvironmentReader.g.h>
#include "EnvironmentHelper.h"

using namespace winrt::Windows::Foundation::Collections;

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct EnvironmentReader : EnvironmentReaderT<EnvironmentReader>
    {
        EnvironmentReader(Scope const& scope);

        static Microsoft::ProjectReunion::EnvironmentReader GetForProcess();
        static Microsoft::ProjectReunion::EnvironmentReader GetForUser();
        static Microsoft::ProjectReunion::EnvironmentReader GetForMachine();
        Windows::Foundation::Collections::IMapView<hstring, hstring> GetEnvironmentVariables();
        hstring GetEnvironmentVariable(hstring const& variableName);

    private:
        Scope m_Scope{};

        StringMap GetProcessEnvironmentVariables() const;
        StringMap GetUserOrMachineEnvironmentVariables() const;      
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct EnvironmentReader : EnvironmentReaderT<EnvironmentReader, implementation::EnvironmentReader>
    {
    };
}
