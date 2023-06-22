// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachAPI.Constants;
using AppAttachAPI.Data;

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
