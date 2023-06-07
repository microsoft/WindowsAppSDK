using AppAttachAPI.Constants;
using AppAttachAPI.Data;
using System;

namespace AppAttachAPI.AttributeImpls
{
    public class AzureWorkspace : IAttribute
    {
        private string _azureWorkspace;

        public string getAttributeName()
        {
            return AttrConsts.AZURE_WORKSPACE;
        }

        public bool getAttributeValidationStatus()
        {
            return true;
        }

        public string getAttributeValue()
        {
            return this._azureWorkspace;
        }

        public void setAttributeValue(string value)
        {
            this._azureWorkspace = value;
        }
    }
}
