using AppAttachAPI.Response.Implementations;
using System.Collections.Generic;

namespace AppAttachAPI.Response.Interfaces
{
    public interface IAppAttachFlowResponse
    {
        List<IAppAttachOutput> getAppAttachOutputs();

        AppAttachArtifact getAppAttachArtifact();

        bool isError();
    }
}
