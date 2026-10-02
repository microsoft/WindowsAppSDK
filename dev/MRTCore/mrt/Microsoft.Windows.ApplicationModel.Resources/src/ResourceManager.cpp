// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "Helper.h"
#include "ResourceCandidate.h"
#include "ResourceContext.h"
#include "ResourceManager.h"
#include "ResourceManager.g.cpp"
#include "ResourceMap.h"
#include "ResourceNotFoundEventArgs.h"

namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
{
ResourceManager::ResourceManager()
{
    winrt::hstring filePath;
    winrt::check_hresult(GetDefaultPriFile(filePath));

    HRESULT hr = MrmCreateResourceManager(filePath.c_str(), &m_resourceManagerHandle);
    // It's ok if resource is not in a PRI file
    if (!IsResourceNotFound(hr))
    {
        winrt::check_hresult(hr);
    }
}

ResourceManager::ResourceManager(hstring const& fileName)
{
    HRESULT hr = MrmCreateResourceManager(fileName.c_str(), &m_resourceManagerHandle);
    if (!IsResourceNotFound(hr))
    {
        winrt::check_hresult(hr);
    }
}

ResourceManager::~ResourceManager() { MrmDestroyResourceManager(m_resourceManagerHandle); }

Microsoft::Windows::ApplicationModel::Resources::ResourceMap ResourceManager::MainResourceMap()
{
    return winrt::make<ResourceMap>(*this, m_resourceManagerHandle, nullptr);
}

Microsoft::Windows::ApplicationModel::Resources::ResourceContext ResourceManager::CreateResourceContext()
{
    MrmContextHandle contextHandle = nullptr;
    if (m_resourceManagerHandle != nullptr)
    {
        winrt::check_hresult(MrmCreateResourceContext(m_resourceManagerHandle, &contextHandle));
    }

    return winrt::make<ResourceContext>(contextHandle);
}

winrt::event_token ResourceManager::ResourceNotFound(winrt::Windows::Foundation::TypedEventHandler<
                                                     Microsoft::Windows::ApplicationModel::Resources::ResourceManager,
                                                     Microsoft::Windows::ApplicationModel::Resources::ResourceNotFoundEventArgs> const& handler)
{
    slim_lock_guard const guard {m_lock};
    return m_resourceNotFound.add(handler);
}

void ResourceManager::ResourceNotFound(winrt::event_token const& token) noexcept
{
    slim_lock_guard const guard {m_lock};
    m_resourceNotFound.remove(token);
}

Microsoft::Windows::ApplicationModel::Resources::ResourceCandidate ResourceManager::HandleResourceNotFound(
    Microsoft::Windows::ApplicationModel::Resources::ResourceContext context,
    hstring name)
{
    Microsoft::Windows::ApplicationModel::Resources::ResourceNotFoundEventArgs args = winrt::make<ResourceNotFoundEventArgs>(context, name);
    m_resourceNotFound(*this, args);
    Microsoft::Windows::ApplicationModel::Resources::ResourceCandidate candidate = args.as<ResourceNotFoundEventArgs>()->GetResolvedCandidate();
    if (candidate != nullptr)
    {
        candidate.as<winrt::Microsoft::Windows::ApplicationModel::Resources::implementation::ResourceCandidate>()->SetQualifierValuesFromContext(context);
    }

    return candidate;
}
} // namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
