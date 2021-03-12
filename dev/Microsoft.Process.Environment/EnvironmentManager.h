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
        hstring GetEnvironmentVariable(hstring const& name);
        void SetEnvironmentVariable(hstring const& name, hstring const& value);
        void AppendToPath(hstring const& path);
        void RemoveFromPath(hstring const& path);
        void AddExecutableFileExtension(hstring const& pathExt);
        void RemoveExecutableFileExtension(hstring const& pathExt);

    private:
        Scope m_Scope;

        std::wstring USER_EV_REG_LOCATION = L"Environment";
        std::wstring MACHINE_EV_REG_LOCATION = L"SYSTEM\\CurrentControlSet\\Control\\Session Manager\\Environment";

        StringMap GetProcessEnvironmentVariables();
        StringMap GetUserOrMachineEnvironmentVariables();
        wil::unique_hkey GetRegHKeyForEVUserAndMachineScope(bool needsWriteAccess = false);
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct EnvironmentManager : EnvironmentManagerT<EnvironmentManager, implementation::EnvironmentManager>
    {
    };
}
