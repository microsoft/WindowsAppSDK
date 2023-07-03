// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

namespace AppAttachAPI.Data
{
    public interface IAttribute
    {
        string getAttributeName();
        string getAttributeValue();
        void setAttributeValue(string value);
        bool getAttributeValidationStatus();
    }
}
