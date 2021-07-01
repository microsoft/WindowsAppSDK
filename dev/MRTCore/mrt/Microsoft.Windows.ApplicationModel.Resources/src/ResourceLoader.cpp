// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

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
}

ResourceLoader::ResourceLoader(hstring const& fileName)
{
    winrt::check_hresult(MrmCreateResourceManager(fileName.c_str(), &m_resourceManager));
    winrt::check_hresult(MrmGetChildResourceMap(m_resourceManager, nullptr, L"Resources", &m_currentResourceMap));
}

ResourceLoader::ResourceLoader(hstring const& fileName, hstring const& resourceMap)
{
    winrt::check_hresult(MrmCreateResourceManager(fileName.c_str(), &m_resourceManager));
    winrt::check_hresult(MrmGetChildResourceMap(m_resourceManager, nullptr, resourceMap.c_str(), &m_currentResourceMap));
}

ResourceLoader::~ResourceLoader() { MrmDestroyResourceManager(m_resourceManager); }

hstring ResourceLoader::GetDefaultResourceFilePath()
{
    hstring fileName;
    winrt::check_hresult(GetDefaultPriFile(fileName));

    return fileName;
}

hstring ResourceLoader::GetString(hstring const& resourceId)
{
    wchar_t* resourceString;
    winrt::check_hresult(MrmLoadStringResource(m_resourceManager, nullptr, m_currentResourceMap, resourceId.c_str(), &resourceString));

    string_resoure_ptr resourceContainer(resourceString);
    return winrt::to_hstring(resourceContainer.get());
}

hstring ResourceLoader::GetStringForUri(winrt::Windows::Foundation::Uri const& resourceUri)
{
    wchar_t* resourceString;
    winrt::check_hresult(MrmLoadStringResourceFromResourceUri(m_resourceManager, nullptr, resourceUri.ToString().c_str(), &resourceString));

    string_resoure_ptr resourceContainer(resourceString);
    return winrt::to_hstring(resourceContainer.get());
}
} // namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
