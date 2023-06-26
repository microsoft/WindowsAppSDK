// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachAPI;
using AppAttachAPI.Constants;
using AppAttachAPI.Data;
using AppAttachAPI.Response.Implementations;
using AppAttachAPI.Response.Interfaces;
using AppAttachAPI.Utils;
using AVDAppAttachValidate.Implementations;
using System;
using System.Collections.Generic;
using System.Linq;

namespace AVDAppAttachValidate
{
    /// <summary>
    /// Validates incoming attributes for AVD implementation applying various strategies and attribute regex
    /// </summary>
    public class AVDAppAttachValidator : IValidator
    {
        private List<IValidationStrategy> _validationStrategies = new List<IValidationStrategy>() { new EnvironmentCheckStrategy(), new AzureValidationStrategy() };
        private List<string> _artifactRequiredAttributes = new List<string>() { AttrConsts.PACKAGE_LOCATION, AttrConsts.PROJECT_FILE_PATH, AttrConsts.CONFIGURATION, AttrConsts.PLATFORM, AttrConsts.CERTIFICATE_PATH, AttrConsts.CERTIFICATE_PASSWORD, AttrConsts.MSBUILD_PATH, AttrConsts.MSIX_MANAGER_PATH, AttrConsts.PACKAGE_VERSION, AttrConsts.IS_PUBLISH_REQUIRED };
        private List<string> _azureRequiredAttributes = new List<string>() { AttrConsts.EMAIL_ID, AttrConsts.ACCESS_TOKEN, AttrConsts.AZURE_STORAGE_KEY, AttrConsts.AZURE_WORKSPACE, AttrConsts.AZURE_STORAGE_FILE_SHARE, AttrConsts.AZURE_STORAGE_ACCOUNT, AttrConsts.AZURE_SUBSCRIPTION_ID, AttrConsts.AZURE_RESOURCE_GROUP, AttrConsts.AZURE_HOST_POOL_NAME, AttrConsts.AZURE_APPLICATION_GROUP_NAME };

        /// <summary>
        /// Validates the given attributes according to the implementation described above.
        /// </summary>
        /// <param name="attributes"></param>
        /// <returns></returns>
        public IAppAttachFlowResponse validate(Dictionary<string, IAttribute> attributes)
        {
            AppAttachFlowResponse response = new AppAttachFlowResponse();

            try
            {
                List<string> requiredAttributeNamesList = getRequiredAttributeNamesList(attributes);

                // Loop through all attribute names
                foreach (string attributeName in requiredAttributeNamesList)
                {
                    IAttribute attribute;

                    // If mandatory attribute does not exist in incomimg map, set as error.
                    if (!attributes.TryGetValue(attributeName, out attribute))
                    {
                        response.setError(true);
                        response.getAppAttachOutputs().Add(new AppAttachOutput($"Missing attribute: {attributeName}", true));
                    }

                    // If attribute validation logic does not pass, set as error.
                    if (!attribute.getAttributeValidationStatus())
                    {
                        response.setError(true);
                        response.getAppAttachOutputs().Add(new AppAttachOutput($"Please provide correct input for attribute: {attributeName}", true));
                    }
                }

                // Loop through all strategies
                foreach (IValidationStrategy strategy in _validationStrategies)
                {
                    strategy.validate(attributes, response);
                }
            }
            catch (Exception ex)
            {
                response.setError(true);
                response.getAppAttachOutputs().Add(new AppAttachOutput("Something went wrong while validating input\n" + ex.Message, true));
            }

            return response;

        }

        public DestinationType getDestinationType()
        {
            return DestinationType.AVD;
        }

        public List<IAppAttachOutput> getValidationStatus()
        {
            throw new NotImplementedException();
        }

        /// <summary>
        /// Get list of required attribute names
        /// </summary>
        /// <param name="attributes"></param>
        /// <returns></returns>
        public List<string> getRequiredAttributeNamesList(Dictionary<string, IAttribute> attributes)
        {
            // If publish is required, return artifact attribute names as well as azure attribute names.
            if (bool.TrueString.Equals(AttributeUtils.getIsPublishRequired(attributes)))
            {
                return new List<string>(_artifactRequiredAttributes.Concat(_azureRequiredAttributes));
            }

            else
            {
                return _artifactRequiredAttributes;
            }

        }
    }
}