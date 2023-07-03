// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachAPI.Constants;
using AppAttachAPI.Data;

namespace AppAttachAPI.AttributeImpls
{
    public class AzureResourceGroup : IAttribute
    {
        private string _azureResourceGroup;

        public string getAttributeName()
        {
            return AttrConsts.AZURE_RESOURCE_GROUP;
        }

        public bool getAttributeValidationStatus()
        {
            return true;
        }

        public string getAttributeValue()
        {
            return this._azureResourceGroup;
        }

        public void setAttributeValue(string value)
        {
            this._azureResourceGroup = value;
        }
    }
}
