// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "ResourceNotFoundEventArgs.h"
#include "ResourceNotFoundEventArgs.g.cpp"

namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
{
Microsoft::Windows::ApplicationModel::Resources::ResourceContext ResourceNotFoundEventArgs::Context() { return m_resourceContext; }

hstring ResourceNotFoundEventArgs::Name() { return m_resourceName; }

void ResourceNotFoundEventArgs::SetResolvedCandidate(Microsoft::Windows::ApplicationModel::Resources::ResourceCandidate const& candidate)
{
    m_candidate = candidate;
}
} // namespace winrt::Microsoft::Windows::ApplicationModel::Resources::implementation
