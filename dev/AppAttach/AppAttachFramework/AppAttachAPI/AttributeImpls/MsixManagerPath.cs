// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachAPI.Constants;
using AppAttachAPI.Data;

namespace AppAttachAPI.AttributeImpls
{
    public class MsixManagerPath : IAttribute
    {
        private string _msixManagerPath;

        public string getAttributeName()
        {
            return AttrConsts.MSIX_MANAGER_PATH;
        }

        public bool getAttributeValidationStatus()
        {
            return true;
        }

        public string getAttributeValue()
        {
            return this._msixManagerPath;
        }

        public void setAttributeValue(string value)
        {
            this._msixManagerPath = value;
        }
    }
}
