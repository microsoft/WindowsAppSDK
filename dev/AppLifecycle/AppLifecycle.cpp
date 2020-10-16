// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

#include <pch.h>
#include <AppLifecycle.h>
#include <AppLifecycle.g.cpp>

namespace winrt::Microsoft::ProjectReunion::implementation
{
    Windows::ApplicationModel::Activation::IActivatedEventArgs AppLifecycle::GetActivatedEventArgs()
    {
        //throw hresult_not_implemented();
        return nullptr;
    }

    bool AppLifecycle::RegisterForFileTypeActivation(hstring const& groupName, Microsoft::ProjectReunion::DesiredView const& desiredView, hstring const& logo,
        array_view<hstring const> supportedFileTypes, array_view<hstring const> supportedVerbs)
    {
        //throw hresult_not_implemented();
        return false;
    }

    bool AppLifecycle::RegisterForProtocolActivation(hstring const& name, Microsoft::ProjectReunion::DesiredView const& desiredView)
    {
        //throw hresult_not_implemented();
        return false;
    }

    bool AppLifecycle::RegisterForStartupActivation(hstring const& taskId, bool isEnabled, hstring const& displayName)
    {
        //throw hresult_not_implemented();
        return false;
    }

    bool AppLifecycle::RegisterForToastActivation(hstring const& displayName)
    {
        //throw hresult_not_implemented();
        return false;
    }

    bool AppLifecycle::UnregisterForFileTypeActivation(hstring const& groupName)
    {
        //throw hresult_not_implemented();
        return false;
    }

    bool AppLifecycle::UnregisterForProtocolActivation(hstring const& name)
    {
        //throw hresult_not_implemented();
        return false;
    }

    bool AppLifecycle::UnregisterForStartupActivation()
    {
        //throw hresult_not_implemented();
        return false;
    }

    bool AppLifecycle::UnregisterForToastActivation()
    {
        //throw hresult_not_implemented();
        return false;
    }
}
