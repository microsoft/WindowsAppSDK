// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#if !defined(URFW_H)
#define URFW_H

bool UrfwNeedsDetours() noexcept;

HRESULT UrfwInitialize() noexcept;

void UrfwShutdown() noexcept;

#endif // URFW_H
