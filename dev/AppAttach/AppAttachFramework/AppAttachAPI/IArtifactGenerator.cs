using AppAttachAPI.Data;
using AppAttachAPI.Response.Interfaces;
using System.Collections.Generic;

namespace AppAttachAPI
{
    public interface IArtifactGenerator : IDestinationType
    {
        IAppAttachFlowResponse generateArtifact(Dictionary<string, IAttribute> attributesMap);
    }
}
