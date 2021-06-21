// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include <EnvironmentManager.g.h>

using namespace winrt::Windows::Foundation::Collections;

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct EnvironmentManager : EnvironmentManagerT<EnvironmentManager>
    {
        enum Scope
        {
            Process = 0,
            User = 1,
            Machine = 2
        };

        EnvironmentManager(Scope const& scope);

        static Microsoft::ProjectReunion::EnvironmentManager GetForProcess();
        static Microsoft::ProjectReunion::EnvironmentManager GetForUser();
        static Microsoft::ProjectReunion::EnvironmentManager GetForMachine();
        Windows::Foundation::Collections::IMapView<hstring, hstring> GetEnvironmentVariables();
        hstring GetEnvironmentVariable(hstring const& variableName);
        bool IsSupported();
        void SetEnvironmentVariable(hstring const& name, hstring const& value);
        void AppendToPath(hstring const& path);
        void RemoveFromPath(hstring const& path);
        void AddExecutableFileExtension(hstring const& pathExt);
        void RemoveExecutableFileExtension(hstring const& pathExt);

    private:
        Scope m_Scope{};

        PCWSTR c_UserEvRegLocation{ L"Environment" };
        PCWSTR c_MachineEvRegLocation{ L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment" };
        PCWSTR c_PathName{ L"PATH" };
        PCWSTR c_PathExtName{ L"PATHEXT" };

        StringMap GetProcessEnvironmentVariables() const;
        StringMap GetUserOrMachineEnvironmentVariables() const;

        std::wstring GetProcessEnvironmentVariable(const std::wstring variableName) const;
        std::wstring GetUserOrMachineEnvironmentVariable(const std::wstring variableName) const;

        wil::unique_hkey GetRegHKeyForEVUserAndMachineScope(bool needsWriteAccess = false) const;

        std::wstring GetPath() const;
        std::wstring GetPathExt() const;

        void DeleteEnvironmentVariableIfExists(const HKEY hkey, const std::wstring name) const;
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct EnvironmentManager : EnvironmentManagerT<EnvironmentManager, implementation::EnvironmentManager>
    {
    };
}
