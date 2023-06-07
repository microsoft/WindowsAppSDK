using AppAttachAPI.Data;
using AppAttachAPI.Response.Interfaces;
using System.Collections.Generic;

namespace AppAttachAPI
{
    public interface IArtifactPublisher : IDestinationType
    {
        /// <summary>
        /// Publishes the code as an app attachment using the list of attributes.
        /// </summary>
        /// <param name="attributesMap">The map of attributes used for publish</param>
        /// <returns>An <see cref="IAppAttachFlowResponse"/> object representing the response of the
        /// publish operation</returns>
        IAppAttachFlowResponse publish(Dictionary<string, IAttribute> attributesMap);

        /// <summary>
        /// Removes the code as an app attachment using the list of attributes.
        /// </summary>
        /// <param name="attributesMap">The map of attributes used for publish</param>
        /// <returns>An <see cref="IAppAttachFlowResponse"/> object representing the response of the
        /// publish operation</returns>
        IAppAttachFlowResponse unPublish(Dictionary<string, IAttribute> attributesMap);
    }
}
