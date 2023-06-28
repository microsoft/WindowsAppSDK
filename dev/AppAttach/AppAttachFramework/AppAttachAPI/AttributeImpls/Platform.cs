// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachAPI.Constants;
using AppAttachAPI.Data;

namespace AppAttachAPI.AttributeImpls
{
    public class Platform : IAttribute
    {
        private string _platform;


        public string getAttributeName()
        {
            return AttrConsts.PLATFORM;
        }

        public bool getAttributeValidationStatus()
        {
            return true;
        }

        public string getAttributeValue()
        {
            return this._platform;
        }

        public void setAttributeValue(string value)
        {
            this._platform = value;
        }
    }
}