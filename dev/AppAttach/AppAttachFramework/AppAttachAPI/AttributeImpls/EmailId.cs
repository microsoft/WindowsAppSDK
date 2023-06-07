using AppAttachAPI.Constants;
using AppAttachAPI.Data;
using System;

namespace AppAttachAPI.AttributeImpls
{
    public class EmailId : IAttribute
    {
        private string _emailId;

        public string getAttributeName()
        {
            return AttrConsts.EMAIL_ID;
        }

        public bool getAttributeValidationStatus()
        {
            return true;
        }

        public string getAttributeValue()
        {
            return this._emailId;
        }

        public void setAttributeValue(string value)
        {
            this._emailId = value;
        }
    }
}
