// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachAPI.Constants;
using AppAttachAPI.Data;

namespace AppAttachAPI.AttributeImpls
{
    public class AzureStorageAccount : IAttribute
    {
        private string _azureStorageAccount;

        public string getAttributeName()
        {
            return AttrConsts.AZURE_STORAGE_ACCOUNT;
        }

        public bool getAttributeValidationStatus()
        {
            return true;
        }

        public string getAttributeValue()
        {
            return this._azureStorageAccount;
        }

        public void setAttributeValue(string value)
        {
            this._azureStorageAccount = value;
        }
    }
}
