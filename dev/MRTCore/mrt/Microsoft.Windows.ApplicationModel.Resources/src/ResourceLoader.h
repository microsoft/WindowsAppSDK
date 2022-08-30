// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once
#include "ResourceLoader.g.h"
#include "ResourceContext.h"

using namespace winrt::Microsoft::Windows::ApplicationModel::Resources;

namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
{

struct ResourceLoader : ResourceLoaderT<ResourceLoader>
{
    ResourceLoader();
    ResourceLoader(hstring const& fileName);
    ResourceLoader(hstring const& fileName, hstring const& resourceMap);

    static hstring GetDefaultResourceFilePath();

    hstring GetString(hstring const& resourceId);
    hstring GetStringForUri(winrt::Windows::Foundation::Uri const& resourceUri);

private:
    ~ResourceLoader();
    void SetDefaultContext();

    MrmManagerHandle m_resourceManager = nullptr;
    MrmMapHandle m_currentResourceMap = nullptr;
    Resources::ResourceContext m_defaultContext {nullptr};
};

} // namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation

namespace winrt::Microsoft::Windows::ApplicationModel::Resources::factory_implementation
{

struct ResourceLoader : ResourceLoaderT<ResourceLoader, implementation::ResourceLoader>
{};

} // namespace winrt::Microsoft::Windows::ApplicationModel::Resources::factory_implementation
