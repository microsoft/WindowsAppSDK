using AppAttachAPI.Constants;
using AppAttachAPI.Data;
using System;

namespace AppAttachAPI.AttributeImpls
{
    public class AzureStorageFileShare : IAttribute
    {
        private string _azureStorageFileShare;

        public string getAttributeName()
        {
            return AttrConsts.AZURE_STORAGE_FILE_SHARE;
        }

        public bool getAttributeValidationStatus()
        {
            return true;
        }

        public string getAttributeValue()
        {
            return this._azureStorageFileShare;
        }

        public void setAttributeValue(string value)
        {
            this._azureStorageFileShare = value;
        }
    }
}
