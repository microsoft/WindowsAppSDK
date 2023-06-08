// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachAPI;
using AppAttachAPI.Data;
using AppAttachAPI.Response.Implementations;
using AppAttachAPI.Response.Interfaces;
using System.Collections.Generic;
using TroubleshootAppAttachPublish.Interfaces;


// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.
namespace TroubleshootAppAttachPublish
{
    public class TroubleshootAppAttachPublish : IArtifactPublisher
    {
        private List<IAppAttachOutput> _errorList;
        private IAppAttachFlowResponse _response;

        private ITroubleshootAppAttachStage _troubleshootAppAttachStage;
        private ITroubleshootAppAttachRegister _troubleshootAppAttachRegister;
        private ITroubleshootAppAttachDestage _troubleshootAppAttachDestage;
        private ITroubleshootAppAttachUnregister _troubleshootAppAttachUnRegister;

        private string _packagePath { get; set; }

        private void prepare(Dictionary<string, IAttribute> attributesMap)
        {
            _errorList = new List<IAppAttachOutput>();

            this._packagePath = attributesMap["appAttachImagePath"].getAttributeValue();

            return;
        }

        public DestinationType getDestinationType()
        {
            return DestinationType.Local;
        }

        public IAppAttachFlowResponse publish(Dictionary<string, IAttribute> attributesMap)
        {
            prepare(attributesMap);

            List<IAppAttachOutput> stageResponse = _troubleshootAppAttachStage.stage(_packagePath);
            List<IAppAttachOutput> registerResponse = _troubleshootAppAttachRegister.register(_packagePath);

            // Combine the errors from both operations into a single error list
            _errorList.AddRange(stageResponse);
            _errorList.AddRange(registerResponse);

            // Create a response object with the package path, error status, and error messages
            _response = new AppAttachFlowResponse(_errorList.Count != 0, _packagePath, _errorList);
            return _response;
        }

        public IAppAttachFlowResponse unPublish(Dictionary<string, IAttribute> attributesMap)
        {
            prepare(attributesMap);

            List<IAppAttachOutput> stageResponse = _troubleshootAppAttachDestage.deStage(_packagePath);
            List<IAppAttachOutput> registerResponse = _troubleshootAppAttachUnRegister.unregister(_packagePath);
            List<IAppAttachOutput> cleanUpResponse = _troubleshootAppAttachUnRegister.cleanUp(_packagePath);

            // Combine the errors from both operations into a single error list
            _errorList.AddRange(stageResponse);
            _errorList.AddRange(registerResponse);
            _errorList.AddRange(cleanUpResponse);

            // Create a response object with the package path, error status, and error messages
            _response = new AppAttachFlowResponse(_errorList.Count != 0, _packagePath, _errorList);
            return _response;
        }
    }
}
