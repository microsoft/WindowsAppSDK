// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"

#include "Microsoft.Kozani.Activation.h"

std::string Microsoft::Kozani::Activation::ActivateApp(
    std::int64_t cookie,
    PCWSTR appUserModelId,
    ::IInspectable* activatedEventArgs)
{
    winrt::com_ptr<::IInspectable> inspectable(activatedEventArgs, winrt::take_ownership_from_abi);
    auto args{ inspectable.as<winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs>() };
    return ActivateApp(cookie, appUserModelId, args);
}

std::string Microsoft::Kozani::Activation::ActivateApp(
    std::int64_t cookie,
    PCWSTR appUserModelId,
    winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs& args)
{
    const auto activationKind{ args.Kind() };
    if (activationKind == winrt::Windows::ApplicationModel::Activation::ActivationKind::Launch)
    {
        auto specificArgs{ args.as<winrt::Windows::ApplicationModel::Activation::LaunchActivatedEventArgs>() };
        return ActivateApp(cookie, appUserModelId, specificArgs);
    }

    THROW_HR_MSG(HRESULT_FROM_WIN32(ERROR_NOT_SUPPORTED), "ActivationKind:%d", activationKind);
}

std::string Microsoft::Kozani::Activation::ActivateApp(
    std::int64_t cookie,
    PCWSTR appUserModelId,
    winrt::Windows::ApplicationModel::Activation::LaunchActivatedEventArgs& args)
{
    const auto arguments{ args.Arguments() };
    return ActivateApp_Launch(cookie, appUserModelId, arguments.c_str());
}

std::string Microsoft::Kozani::Activation::ActivateApp_Launch(
    std::int64_t cookie,
    PCWSTR appUserModelId,
    PCWSTR arguments)
{
    const std::string appUserModelIdUtf8{ ::Microsoft::Utf8::ToUtf8(appUserModelId) };
    const std::string argumentsUtf8{ arguments ? ::Microsoft::Utf8::ToUtf8(arguments) : "" };
    return ActivateApp_Launch(cookie, appUserModelIdUtf8, argumentsUtf8);
}

std::string Microsoft::Kozani::Activation::ActivateApp_Launch(
    std::int64_t cookie,
    const std::string& appUserModelId,
    const std::string& arguments)
{
    ::Microsoft::Kozani::Activation::ActivateAppRequest message;
    message.set_cookie(cookie);
    message.set_activation_kind(::Microsoft::Kozani::Activation::ActivationKind::Launch);
    message.set_app_user_model_id(appUserModelId);
    message.set_arguments(arguments);

    std::string bytes;
    message.SerializeToString(&bytes);
    return bytes;
}
