using AppAttachAPI;
using AppAttachAPI.Constants;
using AppAttachAPI.Data;
using AppAttachAPI.Response.Implementations;
using AppAttachAPI.Response.Interfaces;
using AVDAppAttachPublish.Implementations;
using AVDAppAttachPublish.Interfaces;
using System;
using System.Collections.Generic;
using System.Linq;

namespace AVDAppAttachPublish
{
    public class AVDAppAttachPublisher : IArtifactPublisher
    {
        private List<IAppAttachOutput> _errorList;
        private IAppAttachFlowResponse _response;

        private IAVDAppAttachUpload _appAttachUpload;
        private IAVDAppAttachDeploy _appAttachDeploy;

        private string _packagePath { get; set; }
        private string _azureSubscriptionId { get; set; }
        private string _azureResourceGroup { get; set; }
        private string _azureStorageKey { get; set; }
        private string _azureStorageAccount { get; set; }
        private string _azureStorageFileShare { get; set; }
        private string _azureApplicationGroupName { get; set; }
        private string _azureHostPoolName { get; set; }


        private void prepare(Dictionary<string, IAttribute> attributesMap)
        {
            this._packagePath = attributesMap[AttrConsts.APPATTACH_IMAGE_PATH].getAttributeValue();
            this._azureSubscriptionId = attributesMap[AttrConsts.AZURE_SUBSCRIPTION_ID].getAttributeValue();
            this._azureResourceGroup = attributesMap[AttrConsts.AZURE_RESOURCE_GROUP].getAttributeValue();
            this._azureStorageKey = attributesMap[AttrConsts.AZURE_STORAGE_KEY].getAttributeValue();
            this._azureStorageAccount = attributesMap[AttrConsts.AZURE_STORAGE_ACCOUNT].getAttributeValue();
            this._azureStorageFileShare = attributesMap[AttrConsts.AZURE_STORAGE_FILE_SHARE].getAttributeValue();
            this._azureApplicationGroupName = attributesMap[AttrConsts.AZURE_APPLICATION_GROUP_NAME].getAttributeValue();
            this._azureHostPoolName = attributesMap[AttrConsts.AZURE_HOST_POOL_NAME].getAttributeValue();

            _appAttachUpload = new AVDAppAttachUpload(_azureStorageKey, _azureStorageFileShare);
            _appAttachDeploy = new AVDAppAttachDeploy(_azureStorageAccount, _azureStorageFileShare, _packagePath);
            _errorList = new List<IAppAttachOutput>();

            return;
        }

        /// <summary>
        /// Publishes the specified list of attributes as an app attachment.
        /// </summary>
        /// <param name="attributes">The list of attributes to publish</param>
        /// <returns>An <see cref="IAppAttachFlowResponse"/> object representing the response of the
        /// publish operation</returns>
        public IAppAttachFlowResponse publish(Dictionary<string, IAttribute> attributesMap)
        {
            // Prepare the publishing environment
            prepare(attributesMap);

            // Upload the app attachment package to the server
            List<IAppAttachOutput> uploadResponse = _appAttachUpload.upload(_packagePath);
            if (uploadResponse.Count() > 0)
            {
                // If there was an error uploading the package, return the error response
                _response = new AppAttachFlowResponse(true, _packagePath, uploadResponse);
                return _response;
            }

            // Deploy the app attachment to the target environment
            List<IAppAttachOutput> deployResponse = _appAttachDeploy.deploy(_azureSubscriptionId, _azureResourceGroup, _azureHostPoolName, _azureApplicationGroupName);
            if (deployResponse.Count() > 0)
            {
                // If there was an error deploying the package, return the error response
                _response = new AppAttachFlowResponse(true, _packagePath, deployResponse);
                return _response;
            }

            // Combine the errors from both operations into a single error list
            _errorList.AddRange(uploadResponse);
            _errorList.AddRange(deployResponse);

            // Create a response object with the package path, error status, and error messages
            _response = new AppAttachFlowResponse(false, _packagePath, _errorList);

            return _response;
        }

        public DestinationType getDestinationType()
        {
            return DestinationType.AVD;
        }

        public IAppAttachFlowResponse unPublish(Dictionary<string, IAttribute> attributesMap)
        {
            throw new NotImplementedException();
        }
    }
}
