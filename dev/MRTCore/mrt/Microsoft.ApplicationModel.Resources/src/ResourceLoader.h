// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once
#include "ResourceLoader.g.h"

namespace winrt::Microsoft::ApplicationModel::Resources::implementation
{

struct ResourceLoader : ResourceLoaderT<ResourceLoader>
{
    ResourceLoader();
    ResourceLoader(hstring const& fileName);
    ResourceLoader(hstring const& fileName, hstring const& resourceMap);

    static hstring GetDefaultResourceFilePath();

    hstring GetString(hstring const& resourceId);
    hstring GetStringForUri(Windows::Foundation::Uri const& resourceUri);

private:
    ~ResourceLoader();

    MrmManagerHandle m_resourceManager = nullptr;
    MrmMapHandle m_currentResourceMap = nullptr;
};

} // namespace winrt::Microsoft::ApplicationModel::Resources::implementation

namespace winrt::Microsoft::ApplicationModel::Resources::factory_implementation
{

struct ResourceLoader : ResourceLoaderT<ResourceLoader, implementation::ResourceLoader>
{};

} // namespace winrt::Microsoft::ApplicationModel::Resources::factory_implementation
