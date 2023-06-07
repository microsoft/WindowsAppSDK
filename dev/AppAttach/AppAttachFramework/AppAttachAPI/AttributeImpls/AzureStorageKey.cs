using AppAttachAPI.Constants;
using AppAttachAPI.Data;
using System;

namespace AppAttachAPI.AttributeImpls
{
    public class AzureStorageKey : IAttribute
    {
        private string _azureStorageKey;

        public string getAttributeName()
        {
            return AttrConsts.AZURE_STORAGE_KEY;
        }

        public bool getAttributeValidationStatus()
        {
            return true;
        }

        public string getAttributeValue()
        {
            return this._azureStorageKey;
        }

        public void setAttributeValue(string value)
        {
            this._azureStorageKey = value;
        }
    }
}
