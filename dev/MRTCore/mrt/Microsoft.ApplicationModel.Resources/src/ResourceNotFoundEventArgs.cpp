// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "ResourceNotFoundEventArgs.h"
#include "ResourceNotFoundEventArgs.g.cpp"

namespace winrt::Microsoft::ApplicationModel::Resources::implementation
{
Microsoft::ApplicationModel::Resources::ResourceContext ResourceNotFoundEventArgs::Context() { return m_resourceContext; }

hstring ResourceNotFoundEventArgs::Name() { return m_resourceName; }

void ResourceNotFoundEventArgs::SetResolvedCandidate(Microsoft::ApplicationModel::Resources::ResourceCandidate const& candidate)
{
    m_candidate = candidate;
}
} // namespace winrt::Microsoft::ApplicationModel::Resources::implementation
