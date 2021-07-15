// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "ResourceNotFoundEventArgs.h"
#include "ResourceNotFoundEventArgs.g.cpp"

namespace winrt::Microsoft::WindowsApp::Resources::implementation
{
Microsoft::WindowsApp::Resources::ResourceContext ResourceNotFoundEventArgs::Context() { return m_resourceContext; }

hstring ResourceNotFoundEventArgs::Name() { return m_resourceName; }

void ResourceNotFoundEventArgs::SetResolvedCandidate(Microsoft::WindowsApp::Resources::ResourceCandidate const& candidate)
{
    m_candidate = candidate;
}
} // namespace winrt::Microsoft::WindowsApp::Resources::implementation
