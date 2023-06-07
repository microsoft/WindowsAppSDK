using AppAttachAPI.Constants;
using AppAttachAPI.Data;
using System;

namespace AppAttachAPI.AttributeImpls
{
    public class IsPublishRequired : IAttribute
    {
        private string _isPublishRequired;

        public string getAttributeName()
        {
            return AttrConsts.IS_PUBLISH_REQUIRED;
        }

        public bool getAttributeValidationStatus()
        {
            return true;
        }

        public string getAttributeValue()
        {
            return this._isPublishRequired;
        }

        public void setAttributeValue(string value)
        {
            this._isPublishRequired = value;
        }
    }
}
