// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachAPI.Constants;
using AppAttachAPI.Data;

namespace AppAttachAPI.AttributeImpls
{
    public class ProjectFilePath : IAttribute
    {
        private string _projectFilePath;

        public string getAttributeName()
        {
            return AttrConsts.PROJECT_FILE_PATH;
        }

        public bool getAttributeValidationStatus()
        {
            return true;
        }

        public string getAttributeValue()
        {
            return this._projectFilePath;
        }

        public void setAttributeValue(string value)
        {
            this._projectFilePath = value;
        }
    }
}
