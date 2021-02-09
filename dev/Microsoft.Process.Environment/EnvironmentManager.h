#pragma once
#include <EnvironmentManager.g.h>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct EnvironmentManager : EnvironmentManagerT<EnvironmentManager>
    {
        EnvironmentManager() = default;

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
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct EnvironmentManager : EnvironmentManagerT<EnvironmentManager, implementation::EnvironmentManager>
    {
    };
}
