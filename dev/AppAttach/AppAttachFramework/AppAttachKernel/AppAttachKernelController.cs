using AppAttachAPI;
using AppAttachAPI.Constants;
using AppAttachAPI.Data;
using AppAttachAPI.Response;
using AppAttachAPI.Response.Implementations;
using AppAttachAPI.Response.Interfaces;
using AppAttachAPI.Utils;
using AppAttachMessenger.Interface;
using AppAttachMessenger;
using BootStrapper;
using System;
using System.Collections.Generic;

namespace AppAttachKernel
{
    /// <summary>
    /// AppAttachKernelController is responsible for executing AppAttachAPI process.
    /// </summary>
    public class AppAttachKernelController
    {

        private IValidator _validator;
        private IArtifactGenerator _generator;
        private IArtifactPublisher _publisher;
        private bool _isPublishNotRequired;

        public AppAttachKernelController()
        {
            IBootStrap obj = new AVDBootStrapper();

            // Get validator, generator and publisher instances from the BootStrap instance.
            _validator = obj.getValidator();
            _generator = obj.getArtifactGenerator();
            _publisher = obj.getArtifactPublisher();

            _isPublishNotRequired = false;
        }

        /// <summary>
        /// Executes the AppAttachAPI process with the given JSON value and host.
        /// </summary>
        /// <param name="jsonValue">JSON Value of the Request</param>
        /// <param name="messageHandler">The optional message handler implementation responsible for processing outgoing messages.</param>
        /// <returns></returns>
        public IAppAttachFlowResponse execute(string jsonValue, MessageHandler messageHandler = null)
        {

            //Start Messenger Listening Service
            if(null != messageHandler)
            {
                Messenger.Instance.Initialize(messageHandler);
            }

            // Prepare arguments map.
            Dictionary<string, IAttribute> attributesMap = PrepareArguments.prepare(jsonValue);

            if (attributesMap != null && attributesMap.Count > 0)
            {
                _isPublishNotRequired = bool.FalseString.Equals(attributesMap[AttrConsts.IS_PUBLISH_REQUIRED].getAttributeValue());

                IAppAttachFlowResponse validatorResponse = _validator.validate(attributesMap);
                if (errorCodeValidator(validatorResponse))
                {
                    return validatorResponse;
                }

                IAppAttachFlowResponse generatorResponse = _generator.generateArtifact(attributesMap);
                if (errorCodeValidator(generatorResponse) || _isPublishNotRequired)
                {
                    return generatorResponse;
                }

                IAppAttachFlowResponse publisherResponse = _publisher.publish(attributesMap);
                if (errorCodeValidator(publisherResponse))
                {
                    return publisherResponse;
                }
            }
            return new AppAttachFlowResponse();
        }

        /// <summary>
        /// Returns true if the response error code indicates an error.
        /// </summary>
        /// <param name="response">Response object from AppAttachAPI.</param>
        private bool errorCodeValidator(IAppAttachFlowResponse response)
        {
            return response.isError();
        }
    }
}
