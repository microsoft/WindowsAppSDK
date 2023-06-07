using AppAttachAPI.Constants;
using AppAttachAPI.Data;
using System;

namespace AppAttachAPI.AttributeImpls
{
    public class Configuration : IAttribute
    {
        private string _configuration;

        public string getAttributeName()
        {
            return AttrConsts.CONFIGURATION;
        }

        public bool getAttributeValidationStatus()
        {
            return true;
        }

        public string getAttributeValue()
        {
            return this._configuration;
        }

        public void setAttributeValue(string value)
        {
            this._configuration = value;
        }
    }
}
