// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachAPI.Constants;
using AppAttachAPI.Data;

namespace AppAttachAPI.AttributeImpls
{
    public class AccessToken : IAttribute
    {
        private string _accessToken;

        public string getAttributeName()
        {
            return AttrConsts.ACCESS_TOKEN;
        }

        public bool getAttributeValidationStatus()
        {
            return true;
        }

        public string getAttributeValue()
        {
            return this._accessToken;
        }

        public void setAttributeValue(string value)
        {
            this._accessToken = value;
        }
    }
}
