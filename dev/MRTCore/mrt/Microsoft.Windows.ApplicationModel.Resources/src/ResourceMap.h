// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "ResourceMap.g.h"
using namespace winrt::Microsoft::Windows::ApplicationModel::Resources;

namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
{

struct ResourceMap : ResourceMapT<ResourceMap>
{
    ResourceMap() = delete;
    ResourceMap(
        Microsoft::Windows::ApplicationModel::Resources::ResourceManager resourceManager,
        MrmManagerHandle resourceManagerHandle,
        MrmMapHandle resourceMapHandle) :
        m_resourceManager(resourceManager), m_resourceManagerHandle(resourceManagerHandle), m_resourceMapHandle(resourceMapHandle)
    {}

    ~ResourceMap() {} // The resource manager owns all the resource maps so nothing to destroy;

    uint32_t ResourceCount();

    Microsoft::Windows::ApplicationModel::Resources::ResourceMap GetSubtree(hstring const& reference);
    Microsoft::Windows::ApplicationModel::Resources::ResourceMap TryGetSubtree(hstring const& reference);
    
    Microsoft::Windows::ApplicationModel::Resources::ResourceCandidate GetValue(hstring const& resource);

    Microsoft::Windows::ApplicationModel::Resources::ResourceCandidate GetValue(
        hstring const& resource,
        Microsoft::Windows::ApplicationModel::Resources::ResourceContext const& context);

    winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, Microsoft::Windows::ApplicationModel::Resources::ResourceCandidate> GetValueByIndex(
        uint32_t index);

    winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, Microsoft::Windows::ApplicationModel::Resources::ResourceCandidate> GetValueByIndex(
        uint32_t index,
        Microsoft::Windows::ApplicationModel::Resources::ResourceContext const& context);

    Microsoft::Windows::ApplicationModel::Resources::ResourceCandidate TryGetValue(hstring const& resource);
    Microsoft::Windows::ApplicationModel::Resources::ResourceCandidate TryGetValue(hstring const& resource, Microsoft::Windows::ApplicationModel::Resources::ResourceContext const& context);

private:
    Microsoft::Windows::ApplicationModel::Resources::ResourceCandidate GetValueImpl(
        const Microsoft::Windows::ApplicationModel::Resources::ResourceContext* context,
        hstring const& resource,
        bool treatNotFoundAsOk);

    Microsoft::Windows::ApplicationModel::Resources::ResourceMap GetSubtreeImpl(hstring const& reference, bool treatNotFoundAsOk);

    winrt::Windows::Foundation::Collections::IKeyValuePair<hstring, Microsoft::Windows::ApplicationModel::Resources::ResourceCandidate> GetValueByIndexImpl(
        const Microsoft::Windows::ApplicationModel::Resources::ResourceContext* context,
        uint32_t index);

    Microsoft::Windows::ApplicationModel::Resources::ResourceManager m_resourceManager = nullptr;
    MrmManagerHandle m_resourceManagerHandle = nullptr;
    MrmMapHandle m_resourceMapHandle = nullptr;
    uint32_t m_resourceCount = static_cast<uint32_t>(-1);
};

} // namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
