using AppAttachAPI.Data;
using System;
using AppAttachAPI.Constants;

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
