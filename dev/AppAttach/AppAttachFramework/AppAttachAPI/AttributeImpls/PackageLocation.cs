using AppAttachAPI.Constants;
using AppAttachAPI.Data;
using System;

namespace AppAttachAPI.AttributeImpls
{
    public class PackageLocation : IAttribute
    {
        private string _packageLocation;

        public string getAttributeName()
        {
            return AttrConsts.PACKAGE_LOCATION;
        }

        public bool getAttributeValidationStatus()
        {
            return true;
        }

        public string getAttributeValue()
        {
            return this._packageLocation;
        }

        public void setAttributeValue(string value)
        {
            this._packageLocation = value;
        }
    }
}
