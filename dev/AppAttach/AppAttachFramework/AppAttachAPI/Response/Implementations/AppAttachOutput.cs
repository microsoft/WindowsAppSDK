// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachAPI.Response.Interfaces;

namespace AppAttachAPI.Response.Implementations
{
    public class AppAttachOutput : IAppAttachOutput
    {
        private string _message;
        private bool _error;

        public AppAttachOutput() { }

        public AppAttachOutput(string message, bool isError)
        {
            this._message = message;
            this._error = isError;
        }

        public string getMessage()
        {
            return _message;
        }

        public bool isError()
        {
            return _error;
        }
    }
}
