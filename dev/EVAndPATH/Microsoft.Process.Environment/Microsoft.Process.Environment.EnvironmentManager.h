#pragma once
#include "EnvironmentManager.g.h"

namespace winrt::Microsoft::Process::Environment::implementation
{
    struct EnvironmentManager : EnvironmentManagerT<EnvironmentManager>
    {
        enum Scope
        {
            Process,
            User,
            Machine
        };

        EnvironmentManager(Scope const& scope);

        static Microsoft::Process::Environment::EnvironmentManager GetForProcess();
        static Microsoft::Process::Environment::EnvironmentManager GetForUser();
        static Microsoft::Process::Environment::EnvironmentManager GetForMachine();
        Windows::Foundation::Collections::IMapView<winrt::hstring, winrt::hstring> GetEnvironmentVariables();
        winrt::hstring GetEnvironmentVariable(winrt::hstring const& name);
        void SetEnvironmentVariable(winrt::hstring const& name, winrt::hstring const& value);
        void AppendToPath(winrt::hstring const& path);
        void RemoveFromPath(winrt::hstring const& path);
        void AppendToPathExt(winrt::hstring const& pathExt);
        void RemoveFromPathExt(winrt::hstring const& pathExt);

    private:
        Scope m_Scope;
    };
}
namespace winrt::Microsoft::Process::Environment::factory_implementation
{
    struct EnvironmentManager : EnvironmentManagerT<EnvironmentManager, implementation::EnvironmentManager>
    {
    };
}
