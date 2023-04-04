// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>
#include "KozaniDvcProtocol.h"

namespace Microsoft::Kozani::DvcProtocol
{
    bool IsEmptyPayloadProtocolDataUnitType(Dvc::ProtocolDataUnit::DataType type)
    {
        switch (type)
        {
            case Dvc::ProtocolDataUnit::AppTerminationNotice:
                return true;
        }

        return false;
    }

    std::string CreatePDU(UINT64 activityId, Dvc::ProtocolDataUnit::DataType type, const std::string& payload = std::string())
    {
        if (!IsEmptyPayloadProtocolDataUnitType(type))
        {
            // Payload data of the PDU should not be empty. It catches a failure condition when empty string is returned 
            // from a failed SerializeAsString call before calling into this method.
            THROW_HR_IF(E_UNEXPECTED, payload.empty());
        }

        Dvc::ProtocolDataUnit pdu;
        pdu.set_activity_id(activityId);
        pdu.set_type(type);

        if (!payload.empty())
        {
            pdu.set_data(std::move(payload));
        }

        std::string rawPDU{ pdu.SerializeAsString() };
        THROW_HR_IF(E_UNEXPECTED, rawPDU.empty());

        return std::move(rawPDU);
    }

    std::string CreateConnectionAckPDU(PCSTR connectionId, UINT64 activityId)
    {
        Dvc::ConnectionAck ackMessage;
        ackMessage.set_connection_id(connectionId);
        return CreatePDU(activityId, Dvc::ProtocolDataUnit::ConnectionAck, ackMessage.SerializeAsString());
    }

    std::string SerializeActivatedEventArgs(winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs& args)
    {
        switch (args.Kind())
        {
        case winrt::Windows::ApplicationModel::Activation::ActivationKind::Launch:
            auto specificArgs{ args.as<winrt::Windows::ApplicationModel::Activation::LaunchActivatedEventArgs>() };
            if (!specificArgs.Arguments().empty())
            {
                const std::string argsUtf8{ ::Microsoft::Utf8::ToUtf8(specificArgs.Arguments().c_str()) };
                Dvc::LaunchActivationArgs launchArgs;
                launchArgs.set_arguments(std::move(argsUtf8));
                return std::move(launchArgs.SerializeAsString());
            }

            break;
        }
        return std::string();
    }

    std::string CreateActivateAppRequestPDU(
        UINT64 activityId,
        PCWSTR appUserModelId,
        winrt::Windows::ApplicationModel::Activation::ActivationKind activationKind,
        winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs& args)
    {
        Dvc::ActivateAppRequest activateAppRequest;
        activateAppRequest.set_activation_kind(static_cast<Dvc::ActivationKind>(activationKind));

        const std::string appUserModelIdUtf8{ ::Microsoft::Utf8::ToUtf8(appUserModelId) };
        activateAppRequest.set_app_user_model_id(std::move(appUserModelIdUtf8));

        if (args)
        {
            activateAppRequest.set_arguments(SerializeActivatedEventArgs(args));
        }

        return CreatePDU(activityId, Dvc::ProtocolDataUnit::ActivateAppRequest, activateAppRequest.SerializeAsString());
    }

    std::string CreateActivateAppResultPDU(
        UINT64 activityId, 
        HRESULT hr, 
        DWORD appProcessId, 
        bool isNewInstance,
        _In_ const std::string& errorMessage)
    {
        Dvc::ActivateAppResult activateAppResult;
        activateAppResult.set_hresult(hr);
        if (SUCCEEDED(hr))
        {
            activateAppResult.set_process_id(appProcessId);
            activateAppResult.set_is_new_instance(isNewInstance);
        }
        else if (!errorMessage.empty())
        {
            activateAppResult.set_error_message(errorMessage);
        }

        return CreatePDU(activityId, Dvc::ProtocolDataUnit::ActivateAppResult, activateAppResult.SerializeAsString());
    }

    std::string CreateAppTerminationNoticePDU(UINT64 activityId)
    {
        return CreatePDU(activityId, Dvc::ProtocolDataUnit::AppTerminationNotice);
    }
}