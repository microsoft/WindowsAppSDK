// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include <EnvironmentWriter.g.h>
#include "EnvironmentHelper.h"

using namespace winrt::Windows::Foundation::Collections;

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct EnvironmentWriter : EnvironmentWriterT<EnvironmentWriter>
    {
        EnvironmentWriter(Scope const& scope);

        static Microsoft::ProjectReunion::EnvironmentWriter GetForProcess();
        static Microsoft::ProjectReunion::EnvironmentWriter GetForUser();
        static Microsoft::ProjectReunion::EnvironmentWriter GetForMachine();
        bool IsSupported();
        void SetEnvironmentVariable(hstring const& name, hstring const& value);
        void AppendToPath(hstring const& path);
        void RemoveFromPath(hstring const& path);
        void AddExecutableFileExtension(hstring const& pathExt);
        void RemoveExecutableFileExtension(hstring const& pathExt);

    private:
        Scope m_Scope{};

        std::wstring GetPath();
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct EnvironmentWriter : EnvironmentWriterT<EnvironmentWriter, implementation::EnvironmentWriter>
    {
    };
}
