// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once
#include "ResourceManager.g.h"

namespace winrt::Microsoft::ApplicationModel::Resources::implementation
{

struct ResourceManager : ResourceManagerT<ResourceManager>
{
    ResourceManager();
    ResourceManager(hstring const& fileName);

    Microsoft::ApplicationModel::Resources::ResourceMap MainResourceMap();
    Microsoft::ApplicationModel::Resources::ResourceContext CreateResourceContext();

    winrt::event_token ResourceNotFound(Windows::Foundation::TypedEventHandler<
                                        Microsoft::ApplicationModel::Resources::ResourceManager,
                                        Microsoft::ApplicationModel::Resources::ResourceNotFoundEventArgs> const& handler);

    void ResourceNotFound(winrt::event_token const& token) noexcept;

    Microsoft::ApplicationModel::Resources::ResourceCandidate HandleResourceNotFound(
        Microsoft::ApplicationModel::Resources::ResourceContext context,
        hstring name);

private:
    ~ResourceManager();
    MrmManagerHandle m_resourceManagerHandle = nullptr;
    slim_mutex m_lock;

    winrt::event<Windows::Foundation::TypedEventHandler<
        Microsoft::ApplicationModel::Resources::ResourceManager,
        Microsoft::ApplicationModel::Resources::ResourceNotFoundEventArgs>>
        m_resourceNotFound;
};

} // namespace winrt::Microsoft::ApplicationModel::Resources::implementation

namespace winrt::Microsoft::ApplicationModel::Resources::factory_implementation
{

struct ResourceManager : ResourceManagerT<ResourceManager, implementation::ResourceManager>
{};

} // namespace winrt::Microsoft::ApplicationModel::Resources::factory_implementation
