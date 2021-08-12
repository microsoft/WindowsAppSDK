#include "pch.h"
#include "Microsoft.Windows.System.EnvironmentManager.h"
#include "Microsoft.Windows.System.EnvironmentManager.g.cpp"

namespace winrt::Microsoft::Windows::System::implementation
{
    winrt::Microsoft::Windows::System::EnvironmentManager EnvironmentManager::GetForProcess()
    {
        throw hresult_not_implemented();
    }
    winrt::Microsoft::Windows::System::EnvironmentManager EnvironmentManager::GetForUser()
    {
        throw hresult_not_implemented();
    }
    winrt::Microsoft::Windows::System::EnvironmentManager EnvironmentManager::GetForMachine()
    {
        throw hresult_not_implemented();
    }
    bool EnvironmentManager::IsSupported()
    {
        throw hresult_not_implemented();
    }
    winrt::Windows::Foundation::Collections::IMapView<hstring, hstring> EnvironmentManager::GetEnvironmentVariables()
    {
        throw hresult_not_implemented();
    }
    hstring EnvironmentManager::GetEnvironmentVariable(hstring const& name)
    {
        throw hresult_not_implemented();
    }
    void EnvironmentManager::SetEnvironmentVariable(hstring const& name, hstring const& value)
    {
        throw hresult_not_implemented();
    }
    void EnvironmentManager::AppendToPath(hstring const& path)
    {
        throw hresult_not_implemented();
    }
    void EnvironmentManager::RemoveFromPath(hstring const& path)
    {
        throw hresult_not_implemented();
    }
    void EnvironmentManager::AddExecutableFileExtension(hstring const& pathExt)
    {
        throw hresult_not_implemented();
    }
    void EnvironmentManager::RemoveExecutableFileExtension(hstring const& pathExt)
    {
        throw hresult_not_implemented();
    }
}
