// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#pragma once

#include "PushManager.g.h"
#include <list>
#include <mutex>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    struct PushManager
    {
        PushManager() = default;

        static Windows::Foundation::IAsyncOperationWithProgress<Microsoft::ProjectReunion::ChannelResult, Microsoft::ProjectReunion::ChannelResult> CreateChannelAsync(winrt::guid remoteId);

    private:
        static bool isChannelRequestRetryable(const winrt::hresult& hrException);
        static std::list<winrt::guid> remoteIdList;
        static std::mutex mtx;
        static std::unique_lock<std::mutex> lock;
    };
}
namespace winrt::Microsoft::ProjectReunion::factory_implementation
{
    struct PushManager : PushManagerT<PushManager, implementation::PushManager>
    {
    };
}
