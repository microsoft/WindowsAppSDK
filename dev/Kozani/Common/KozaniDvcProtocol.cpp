// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include <pch.h>
#include <winrt\Windows.Storage.h>
#include "KozaniDvcProtocol.h"

namespace Microsoft::Kozani::DvcProtocol
{
    std::string CreatePdu(UINT64 activityId, Dvc::ProtocolDataUnit::DataType type, const std::string& payload)
    {
        // Do not check payload.empty() because if the payload message only contains default values, it can be empty after SerializeAsString().
        
        Dvc::ProtocolDataUnit pdu;
        pdu.set_activity_id(activityId);
        pdu.set_type(type);

        if (!payload.empty())
        {
            pdu.set_data(std::move(payload));
        }

        std::string rawPdu{ pdu.SerializeAsString() };

        // rawPdu should never be empty as the activityId must not be default value (0).
        THROW_HR_IF(KOZANI_E_PDU_SERIALIZATION, rawPdu.empty());
        return rawPdu;
    }

    std::string CreateConnectionAckPdu(PCSTR connectionId, UINT64 activityId)
    {
        Dvc::ConnectionAck ackMessage;
        ackMessage.set_connection_id(connectionId);
        return CreatePdu(activityId, Dvc::ProtocolDataUnit::ConnectionAck, ackMessage.SerializeAsString());
    }

    std::string SerializeActivatedEventArgs(winrt::Windows::ApplicationModel::Activation::IActivatedEventArgs& args)
    {
        switch (args.Kind())
        {
        case winrt::Windows::ApplicationModel::Activation::ActivationKind::Launch:
            {
                auto specificArgs{ args.as<winrt::Windows::ApplicationModel::Activation::LaunchActivatedEventArgs>() };
                if (!specificArgs.Arguments().empty())
                {
                    const std::string argsUtf8{ ::Microsoft::Utf8::ToUtf8(specificArgs.Arguments().c_str()) };
                    Dvc::LaunchActivationArgs launchArgs;
                    launchArgs.set_arguments(std::move(argsUtf8));
                    return launchArgs.SerializeAsString();
                }
                break;
            }

        case winrt::Windows::ApplicationModel::Activation::ActivationKind::File:
            {
                auto specificArgs{ args.as<winrt::Windows::ApplicationModel::Activation::FileActivatedEventArgs>() };
                const std::string verbUtf8{ ::Microsoft::Utf8::ToUtf8(specificArgs.Verb().c_str()) };
                Dvc::FileActivationArgs fileArgs;
                fileArgs.set_verb(std::move(verbUtf8));

                auto files{ specificArgs.Files() };
                for (auto const& file : specificArgs.Files())
                {
                    const std::string filePathUtf8{ ::Microsoft::Utf8::ToUtf8(file.Path().c_str()) };
                    fileArgs.add_file_paths(std::move(filePathUtf8));
                }

                return fileArgs.SerializeAsString();
            }
        case winrt::Windows::ApplicationModel::Activation::ActivationKind::Protocol:
            {
                auto specificArgs{ args.as<winrt::Windows::ApplicationModel::Activation::ProtocolActivatedEventArgs>() };
                const std::string uriUtf8{ ::Microsoft::Utf8::ToUtf8(specificArgs.Uri().AbsoluteUri().c_str())};
                Dvc::ProtocolActivationArgs protocolArgs;
                protocolArgs.set_uri(std::move(uriUtf8));

                return protocolArgs.SerializeAsString();
            }
        }
        return std::string();
    }

    std::string CreateActivateAppRequestPdu(
        UINT64 activityId,
        PCWSTR appUserModelId,
        winrt::Windows::ApplicationModel::Activation::ActivationKind activationKind,
        const std::string& serializedArgs)
    {
        Dvc::ActivateAppRequest activateAppRequest;
        activateAppRequest.set_activation_kind(static_cast<Dvc::ActivationKind>(activationKind));

        const std::string appUserModelIdUtf8{ ::Microsoft::Utf8::ToUtf8(appUserModelId) };
        activateAppRequest.set_app_user_model_id(std::move(appUserModelIdUtf8));
        if (!serializedArgs.empty())
        {
            activateAppRequest.set_arguments(serializedArgs);
        }

        return CreatePdu(activityId, Dvc::ProtocolDataUnit::ActivateAppRequest, activateAppRequest.SerializeAsString());
    }

    std::string CreateActivateAppResultPdu(
        UINT64 activityId, 
        HRESULT hr, 
        DWORD appProcessId, 
        bool isNewInstance,
        const std::string& errorMessage)
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

        return CreatePdu(activityId, Dvc::ProtocolDataUnit::ActivateAppResult, activateAppResult.SerializeAsString());
    }

    std::string CreateAppTerminationNoticePdu(UINT64 activityId)
    {
        return CreatePdu(activityId, Dvc::ProtocolDataUnit::AppTerminationNotice);
    }
}