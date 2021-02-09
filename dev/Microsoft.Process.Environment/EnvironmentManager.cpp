#include "pch.h"
#include <EnvironmentManager.h>
#include <EnvironmentManager.g.cpp>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    Microsoft::ProjectReunion::EnvironmentManager EnvironmentManager::GetForProcess()
    {
        throw hresult_not_implemented();
    }
    Microsoft::ProjectReunion::EnvironmentManager EnvironmentManager::GetForUser()
    {
        throw hresult_not_implemented();
    }
    Microsoft::ProjectReunion::EnvironmentManager EnvironmentManager::GetForMachine()
    {
        throw hresult_not_implemented();
    }
    Windows::Foundation::Collections::IMapView<hstring, hstring> EnvironmentManager::GetEnvironmentVariables()
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
