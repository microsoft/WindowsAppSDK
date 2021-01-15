// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.
#pragma once

#include <winrt/Windows.Foundation.h>
#include "ActivatedEventArgsBase.h"

namespace winrt::Microsoft::ProjectReunion::implementation
{
    using namespace winrt::Windows::ApplicationModel::Activation;

    class StartupActivatedEventArgs : public winrt::implements<StartupActivatedEventArgs,
        ActivatedEventArgsBase, IStartupTaskActivatedEventArgs>
    {
    public:
        StartupActivatedEventArgs(const std::wstring& taskId) : m_taskId(taskId)
        {
            m_kind = ActivationKind::StartupTask;
        }

        static IActivatedEventArgs CreateFromProtocol(IProtocolActivatedEventArgs const& protocolArgs)
        {
            auto query = protocolArgs.Uri().QueryParsed();
            std::wstring taskId = query.GetFirstValueByName(L"TaskId").c_str();
            return make<StartupActivatedEventArgs>(taskId);
        }

        // IStartupTaskActivatedEventArgs
        winrt::hstring TaskId()
        {
            return m_taskId;
        }

    private:
        winrt::hstring m_taskId;
    };
}

