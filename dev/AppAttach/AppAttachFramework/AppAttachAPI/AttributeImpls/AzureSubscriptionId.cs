using AppAttachAPI.Constants;
using AppAttachAPI.Data;
using System;

namespace AppAttachAPI.AttributeImpls
{
    public class AzureSubscriptionId : IAttribute
    {
        private string _azureSubscriptionId;

        public string getAttributeName()
        {
            return AttrConsts.AZURE_SUBSCRIPTION_ID;
        }

        public bool getAttributeValidationStatus()
        {
            return true;
        }

        public string getAttributeValue()
        {
            return this._azureSubscriptionId;
        }

        public void setAttributeValue(string value)
        {
            this._azureSubscriptionId = value;
        }
    }
}
