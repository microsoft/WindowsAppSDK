// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachAPI.Constants;
using AppAttachAPI.Data;

namespace AppAttachAPI.AttributeImpls
{
    public class MsbuildPath : IAttribute
    {
        private string _msbuildPath;

        public string getAttributeName()
        {
            return AttrConsts.MSBUILD_PATH;
        }

        public bool getAttributeValidationStatus()
        {
            return true;
        }

        public string getAttributeValue()
        {
            return this._msbuildPath;
        }

        public void setAttributeValue(string value)
        {
            this._msbuildPath = value;
        }
    }
}
