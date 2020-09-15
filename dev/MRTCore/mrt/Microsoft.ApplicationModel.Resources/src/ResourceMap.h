// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once
#include "ResourceMap.g.h"
using namespace winrt::Microsoft::ApplicationModel::Resources;

namespace winrt::Microsoft::ApplicationModel::Resources::implementation
{

struct ResourceMap : ResourceMapT<ResourceMap>
{
    ResourceMap() = delete;
    ResourceMap(
        Microsoft::ApplicationModel::Resources::ResourceManager resourceManager,
        MrmManagerHandle resourceManagerHandle,
        MrmMapHandle resourceMapHandle) :
        m_resourceManager(resourceManager), m_resourceManagerHandle(resourceManagerHandle), m_resourceMapHandle(resourceMapHandle)
    {}

    ~ResourceMap() {} // The resource manager owns all the resource maps so nothing to destroy;

    uint32_t ResourceCount();

    Microsoft::ApplicationModel::Resources::ResourceMap GetSubtree(hstring const& reference);
    Microsoft::ApplicationModel::Resources::ResourceCandidate GetValue(hstring const& resource);

    Microsoft::ApplicationModel::Resources::ResourceCandidate GetValue(
        Microsoft::ApplicationModel::Resources::ResourceContext const& context,
        hstring const& resource);

    Windows::Foundation::Collections::IKeyValuePair<hstring, Microsoft::ApplicationModel::Resources::ResourceCandidate> GetValueByIndex(
        uint32_t index);

    Windows::Foundation::Collections::IKeyValuePair<hstring, Microsoft::ApplicationModel::Resources::ResourceCandidate> GetValueByIndex(
        Microsoft::ApplicationModel::Resources::ResourceContext const& context,
        uint32_t index);

private:
    Microsoft::ApplicationModel::Resources::ResourceCandidate GetValueImpl(
        const Microsoft::ApplicationModel::Resources::ResourceContext* context,
        hstring const& resource);

    Windows::Foundation::Collections::IKeyValuePair<hstring, Microsoft::ApplicationModel::Resources::ResourceCandidate> GetValueByIndexImpl(
        const Microsoft::ApplicationModel::Resources::ResourceContext* context,
        uint32_t index);

    Microsoft::ApplicationModel::Resources::ResourceManager m_resourceManager = nullptr;
    MrmManagerHandle m_resourceManagerHandle = nullptr;
    MrmMapHandle m_resourceMapHandle = nullptr;
    uint32_t m_resourceCount = static_cast<uint32_t>(-1);
};

} // namespace winrt::Microsoft::ApplicationModel::Resources::implementation