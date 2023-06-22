// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachAPI.Constants;
using AppAttachAPI.Data;

namespace AppAttachAPI.AttributeImpls
{
    public class CertificatePassword : IAttribute
    {
        private string _certificatePassword;

        public string getAttributeName()
        {
            return AttrConsts.CERTIFICATE_PASSWORD;
        }

        public bool getAttributeValidationStatus()
        {
            return true;
        }

        public string getAttributeValue()
        {
            return this._certificatePassword;
        }

        public void setAttributeValue(string value)
        {
            this._certificatePassword = value;
        }
    }
}
