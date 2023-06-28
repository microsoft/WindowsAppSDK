// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachAPI;
using AppAttachAPI.Constants;
using AppAttachAPI.Data;
using AppAttachAPI.Response.Implementations;
using AppAttachAPI.Utils;
using AVDAppAttachValidate.Constants;
using System.Collections.Generic;

namespace AVDAppAttachValidate.Implementations
{
    /// <summary>
    /// This validation strategy sets Azure-Context and uses that information to verify whether VHDX file already exists in file share
    /// </summary>
    public class AzureValidationStrategy : IValidationStrategy
    {
        /// <summary>
        /// Validates the given attributes according to the strategy described above.
        /// </summary>
        /// <param name="attributes"></param>
        /// <param name="response"></param>
        /// <returns>True if the validation is successful, otherwise false.</returns>
        public bool validate(Dictionary<string, IAttribute> attributes, AppAttachFlowResponse response)
        {
            // If publish is not required, validation is skipped
            if (!bool.TrueString.Equals(AttributeUtils.getIsPublishRequired(attributes)))
            {
                return true;
            }

            // Generates powershell script that validates the strategy
            var scriptPath = FileUtils.generateResourceFile(ScriptResources.AzureFileShareScript, "AzureFileShareScript.ps1");

            // Get attribute values
            var projFilePath = attributes[AttrConsts.PROJECT_FILE_PATH].getAttributeValue();
            var packageVersion = attributes[AttrConsts.PACKAGE_VERSION].getAttributeValue();
            var configuration = attributes[AttrConsts.CONFIGURATION].getAttributeValue();
            var platform = attributes[AttrConsts.PLATFORM].getAttributeValue();
            string outputFile = AttributeUtils.getOutputFile(projFilePath, packageVersion, configuration, platform) + "." + ArtifactConstants.Extensions.VHDX;


            var accessToken = attributes[AttrConsts.ACCESS_TOKEN].getAttributeValue();
            var emailId = attributes[AttrConsts.EMAIL_ID].getAttributeValue();
            var resourceGroupName = attributes[AttrConsts.AZURE_RESOURCE_GROUP].getAttributeValue();
            var subscriptionId = attributes[AttrConsts.AZURE_SUBSCRIPTION_ID].getAttributeValue();
            var storageAccountName = attributes[AttrConsts.AZURE_STORAGE_ACCOUNT].getAttributeValue();
            var fileshareName = attributes[AttrConsts.AZURE_STORAGE_FILE_SHARE].getAttributeValue();

            var fileExistsInFileShare = PowerShellConstants.FILE_EXISTS_IN_FILESHARE;
            var fileDoesNotExistInFileShare = PowerShellConstants.FILE_DOES_NOT_EXIST_IN_FILESHARE;

            // Execute PowerShell script
            var powerShellOutput = PowerShellUtils.ExecutePowerShellScript(scriptPath, accessToken, emailId, resourceGroupName, subscriptionId, storageAccountName, fileshareName, outputFile, fileExistsInFileShare, fileDoesNotExistInFileShare);

            // Handle PowerShell output
            if (powerShellOutput.Contains(fileExistsInFileShare))
            {
                response.getAppAttachOutputs().Add(new AppAttachOutput($"Package {outputFile} already exists in File Share", true));
                response.setError(true);
                return false;
            }
            else if (powerShellOutput.Contains(fileDoesNotExistInFileShare))
            {
                return true;
            }
            else
            {
                response.getAppAttachOutputs().Add(new AppAttachOutput($"Something went wrong while checking whether package already exists in fileshare", true));
                response.setError(true);
                return false;
            }
        }
    }
}
