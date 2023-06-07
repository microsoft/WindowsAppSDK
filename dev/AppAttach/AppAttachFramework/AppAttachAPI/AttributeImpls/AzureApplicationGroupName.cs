using AppAttachAPI.Constants;
using AppAttachAPI.Data;
using System;

namespace AppAttachAPI.AttributeImpls
{
    public class AzureApplicationGroupName : IAttribute
    {
        private string _azureApplicationGroupName;

        public string getAttributeName()
        {
            return AttrConsts.AZURE_APPLICATION_GROUP_NAME;
        }

        public bool getAttributeValidationStatus()
        {
            return true;
        }

        public string getAttributeValue()
        {
            return this._azureApplicationGroupName;
        }

        public void setAttributeValue(string value)
        {
            this._azureApplicationGroupName = value;
        }
    }
}
