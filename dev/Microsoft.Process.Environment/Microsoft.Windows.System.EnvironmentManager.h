#pragma once
#include "Microsoft.Windows.System.EnvironmentManager.g.h"

namespace winrt::Microsoft::Windows::System::implementation
{
    struct EnvironmentManager : EnvironmentManagerT<EnvironmentManager>
    {
        EnvironmentManager() = default;

        static winrt::Microsoft::Windows::System::EnvironmentManager GetForProcess();
        static winrt::Microsoft::Windows::System::EnvironmentManager GetForUser();
        static winrt::Microsoft::Windows::System::EnvironmentManager GetForMachine();
        static bool IsSupported();
        winrt::Windows::Foundation::Collections::IMapView<hstring, hstring> GetEnvironmentVariables();
        hstring GetEnvironmentVariable(hstring const& name);
        void SetEnvironmentVariable(hstring const& name, hstring const& value);
        void AppendToPath(hstring const& path);
        void RemoveFromPath(hstring const& path);
        void AddExecutableFileExtension(hstring const& pathExt);
        void RemoveExecutableFileExtension(hstring const& pathExt);
    };
}
namespace winrt::Microsoft::Windows::System::factory_implementation
{
    struct EnvironmentManager : EnvironmentManagerT<EnvironmentManager, implementation::EnvironmentManager>
    {
    };
}
