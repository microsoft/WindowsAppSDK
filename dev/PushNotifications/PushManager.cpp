// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include "pch.h"
#include "PushManager.h"
#include "PushManager.g.cpp"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    Windows::Foundation::IAsyncOperationWithProgress<Microsoft::ProjectReunion::ChannelResult, Microsoft::ProjectReunion::ChannelResult> PushManager::CreateChannelAsync(winrt::guid remoteId)
    {
        throw hresult_not_implemented();
    }
}
