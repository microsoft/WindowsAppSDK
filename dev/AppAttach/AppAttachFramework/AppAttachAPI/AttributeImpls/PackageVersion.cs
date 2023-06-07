using AppAttachAPI.Constants;
using AppAttachAPI.Data;
using System;

namespace AppAttachAPI.AttributeImpls
{
    public class PackageVersion : IAttribute
    {
        private string _packageVersion;

        public string getAttributeName()
        {
            return AttrConsts.PACKAGE_VERSION;
        }

        public bool getAttributeValidationStatus()
        {
            return true;
        }

        public string getAttributeValue()
        {
            return this._packageVersion;
        }

        public void setAttributeValue(string value)
        {
            this._packageVersion = value;
        }
    }
}
