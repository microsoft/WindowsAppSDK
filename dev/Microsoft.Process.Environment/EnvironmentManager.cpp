#include "pch.h"
#include <EnvironmentManager.h>
#include <EnvironmentManager.g.cpp>

namespace winrt::Microsoft::ProjectReunion::implementation
{

    EnvironmentManager::EnvironmentManager(Scope const& scope)
        : m_Scope(scope) { }

    ProjectReunion::EnvironmentManager EnvironmentManager::GetForProcess()
    {
        ProjectReunion::EnvironmentManager environmentManager{ nullptr };
        environmentManager = winrt::make<implementation::EnvironmentManager>(Scope::Process);
        return environmentManager;
    }

    Microsoft::ProjectReunion::EnvironmentManager EnvironmentManager::GetForUser()
    {
        ProjectReunion::EnvironmentManager environmentManager{ nullptr };
        environmentManager = winrt::make<implementation::EnvironmentManager>(Scope::User);
        return environmentManager;
    }

    Microsoft::ProjectReunion::EnvironmentManager EnvironmentManager::GetForMachine()
    {
        ProjectReunion::EnvironmentManager environmentManager{ nullptr };
        environmentManager = winrt::make<implementation::EnvironmentManager>(Scope::Machine);
        return environmentManager;
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
