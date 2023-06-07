using AppAttachAPI.Constants;
using AppAttachAPI.Data;
using System;

namespace AppAttachAPI.AttributeImpls
{
    public class CertificatePath : IAttribute
    {
        private string _certificatePath;

        public string getAttributeName()
        {
            return AttrConsts.CERTIFICATE_PATH;
        }

        public bool getAttributeValidationStatus()
        {
            return true;
        }

        public string getAttributeValue()
        {
            return this._certificatePath;
        }

        public void setAttributeValue(string value)
        {
            this._certificatePath = value;
        }
    }
}
