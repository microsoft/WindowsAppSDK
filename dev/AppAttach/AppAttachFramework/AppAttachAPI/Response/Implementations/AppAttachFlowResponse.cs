// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.


using AppAttachAPI.Response.Interfaces;
using System.Collections.Generic;

namespace AppAttachAPI.Response.Implementations
{
    public class AppAttachFlowResponse : IAppAttachFlowResponse
    {
        private AppAttachArtifact _appAttachArtifact;
        private List<IAppAttachOutput> _appAttachOutputs;
        private bool _isError;

        public AppAttachFlowResponse()
        {
            this._isError = false;
            this._appAttachOutputs = new List<IAppAttachOutput>();
            this._appAttachArtifact = null;
        }

        public AppAttachFlowResponse(bool isError, string vhdxPath, List<IAppAttachOutput> appAttachOutputs)
        {
            this._isError = isError;
            this._appAttachArtifact = new AppAttachArtifact(vhdxPath);
            this._appAttachOutputs = appAttachOutputs;
        }

        public AppAttachArtifact getAppAttachArtifact()
        {
            return _appAttachArtifact;
        }

        public List<IAppAttachOutput> getAppAttachOutputs()
        {
            return _appAttachOutputs;
        }

        public bool isError()
        {
            return _isError;
        }

        public void setError(bool isError)
        {
            _isError = isError;
        }
    }
}