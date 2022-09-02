// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "ResourceManager.g.h"

namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
{

struct ResourceManager : ResourceManagerT<ResourceManager>
{
    ResourceManager();
    ResourceManager(hstring const& fileName);

    Microsoft::Windows::ApplicationModel::Resources::ResourceMap MainResourceMap();
    Microsoft::Windows::ApplicationModel::Resources::ResourceContext CreateResourceContext();

    winrt::event_token ResourceNotFound(winrt::Windows::Foundation::TypedEventHandler<
                                        Microsoft::Windows::ApplicationModel::Resources::ResourceManager,
                                        Microsoft::Windows::ApplicationModel::Resources::ResourceNotFoundEventArgs> const& handler);

    void ResourceNotFound(winrt::event_token const& token) noexcept;

    Microsoft::Windows::ApplicationModel::Resources::ResourceCandidate HandleResourceNotFound(
        Microsoft::Windows::ApplicationModel::Resources::ResourceContext context,
        hstring name);

private:
    ~ResourceManager();
    MrmManagerHandle m_resourceManagerHandle = nullptr;
    slim_mutex m_lock;

    winrt::event<winrt::Windows::Foundation::TypedEventHandler<
        Microsoft::Windows::ApplicationModel::Resources::ResourceManager,
        Microsoft::Windows::ApplicationModel::Resources::ResourceNotFoundEventArgs>>
        m_resourceNotFound;
};

} // namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation

namespace winrt::Microsoft::Windows::ApplicationModel::Resources::factory_implementation
{

struct ResourceManager : ResourceManagerT<ResourceManager, implementation::ResourceManager>
{};

} // namespace winrt::Microsoft::Windows::ApplicationModel::Resources::factory_implementation
