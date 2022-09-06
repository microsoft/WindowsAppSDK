// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "ResourceLoader.h"
#include "ResourceLoader.g.cpp"
#include "Helper.h"

namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
{
ResourceLoader::ResourceLoader()
{
    hstring fileName;
    winrt::check_hresult(GetDefaultPriFile(fileName));

    winrt::check_hresult(MrmCreateResourceManager(fileName.c_str(), &m_resourceManager));
    winrt::check_hresult(MrmGetChildResourceMap(m_resourceManager, nullptr, L"Resources", &m_currentResourceMap));
    SetDefaultContext();
}

ResourceLoader::ResourceLoader(hstring const& fileName)
{
    winrt::check_hresult(MrmCreateResourceManager(fileName.c_str(), &m_resourceManager));
    winrt::check_hresult(MrmGetChildResourceMap(m_resourceManager, nullptr, L"Resources", &m_currentResourceMap));
    SetDefaultContext();
}

ResourceLoader::ResourceLoader(hstring const& fileName, hstring const& resourceMap)
{
    winrt::check_hresult(MrmCreateResourceManager(fileName.c_str(), &m_resourceManager));
    winrt::check_hresult(MrmGetChildResourceMap(m_resourceManager, nullptr, resourceMap.c_str(), &m_currentResourceMap));
    SetDefaultContext();
}

ResourceLoader::~ResourceLoader()
{
    m_defaultContext = nullptr;
    MrmDestroyResourceManager(m_resourceManager);
}

hstring ResourceLoader::GetDefaultResourceFilePath()
{
    hstring fileName;
    winrt::check_hresult(GetDefaultPriFile(fileName));

    return fileName;
}

hstring ResourceLoader::GetString(hstring const& resourceId)
{
    wchar_t* resourceString;
    auto contextHandle = m_defaultContext.as<Resources::implementation::ResourceContext>()->GetContextHandle();
    winrt::check_hresult(MrmLoadStringResource(m_resourceManager, contextHandle, m_currentResourceMap, resourceId.c_str(), &resourceString));

    string_resoure_ptr resourceContainer(resourceString);
    return winrt::to_hstring(resourceContainer.get());
}

hstring ResourceLoader::GetStringForUri(winrt::Windows::Foundation::Uri const& resourceUri)
{
    wchar_t* resourceString;
    auto contextHandle = m_defaultContext.as<Resources::implementation::ResourceContext>()->GetContextHandle();
    winrt::check_hresult(MrmLoadStringResourceFromResourceUri(m_resourceManager, contextHandle, resourceUri.ToString().c_str(), &resourceString));

    string_resoure_ptr resourceContainer(resourceString);
    return winrt::to_hstring(resourceContainer.get());
}

void ResourceLoader::SetDefaultContext()
{
    MrmContextHandle contextHandle = nullptr;
    winrt::check_hresult(MrmCreateResourceContext(m_resourceManager, &contextHandle));
    m_defaultContext = winrt::make<ResourceContext>(contextHandle);
    m_defaultContext.as<Resources::implementation::ResourceContext>()->Apply();
}
} // namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
