using AppAttachAPI.Constants;
using AppAttachAPI.Data;
using System;

namespace AppAttachAPI.AttributeImpls
{
    public class AzureHostPoolName : IAttribute
    {
        private string _azureHostPoolName;

        public string getAttributeName()
        {
            return AttrConsts.AZURE_HOST_POOL_NAME;
        }

        public bool getAttributeValidationStatus()
        {
            return true;
        }

        public string getAttributeValue()
        {
            return this._azureHostPoolName;
        }

        public void setAttributeValue(string value)
        {
            this._azureHostPoolName = value;
        }
    }
}
