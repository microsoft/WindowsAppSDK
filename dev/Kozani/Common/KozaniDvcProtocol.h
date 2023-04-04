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

    const size_t MaxProtocolDataUnitSize = 64 * 1024;

    std::string CreatePDU(UINT64 activityId, Dvc::ProtocolDataUnit::DataType type, const std::string& payload);
    
    std::string CreateConnectionAckPDU(PCSTR connectionId, UINT64 activityId);
    
    std::string SerializeActivatedEventArgs(winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs& args);
    
    std::string CreateActivateAppRequestPDU(
        UINT64 activityId,
        PCWSTR appUserModelId,
        winrt::Windows::ApplicationModel::Activation::ActivationKind activationKind,
        winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs& args);

    std::string CreateActivateAppResultPDU(
        UINT64 activityId, 
        HRESULT hr, 
        DWORD appProcessId, 
        bool isNewInstance,
        _In_ const std::string& errorMessage);

    std::string CreateAppTerminationNoticePDU(UINT64 activityId);
}