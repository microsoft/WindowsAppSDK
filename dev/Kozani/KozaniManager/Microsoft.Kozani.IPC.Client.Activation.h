// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include "KozaniProtobufMessages.h"

namespace Microsoft::Kozani::IPC::Client::Activation
{
std::string ActivateApp(
    std::int64_t cookie,
    PCWSTR appUserModelId,
    ::IInspectable* args);

std::string ActivateApp(
    std::int64_t cookie,
    PCWSTR appUserModelId,
    winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs& args);

std::string ActivateApp(
    std::int64_t cookie,
    PCWSTR appUserModelId,
    winrt::Windows::ApplicationModel::Activation::LaunchActivatedEventArgs& args);

std::string ActivateApp_Launch(
    std::int64_t cookie,
    PCWSTR appUserModelId,
    PCWSTR arguments);

std::string ActivateApp_Launch(
    std::int64_t cookie,
    const std::string& appUserModelId,
    const std::string& arguments);
}
