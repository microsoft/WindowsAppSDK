// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#pragma once

#include <winrt/Windows.ApplicationModel.Activation.h>
#include <Microsoft.Utf8.h>
#include <Kozani.DVC.pb.h>

namespace Dvc = ::Microsoft::Kozani::DVC;

namespace Microsoft::Kozani::DvcProtocol
{
    const char DvcChannelName[] = "KozaniDvc";

    std::string CreatePdu(UINT64 activityId, Dvc::ProtocolDataUnit::DataType type, const std::string& payload);
    
    std::string CreateConnectionAckPdu(PCSTR connectionId, UINT64 activityId);
    
    std::string SerializeActivatedEventArgs(winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs& args);
    
    std::string CreateActivateAppRequestPdu(
        UINT64 activityId,
        PCWSTR appUserModelId,
        winrt::Windows::ApplicationModel::Activation::ActivationKind activationKind,
        winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs& args);

    std::string CreateActivateAppResultPdu(
        UINT64 activityId, 
        HRESULT hr, 
        DWORD appProcessId, 
        bool isNewInstance,
        const std::string& errorMessage);

    std::string CreateAppTerminationNoticePdu(UINT64 activityId);
}