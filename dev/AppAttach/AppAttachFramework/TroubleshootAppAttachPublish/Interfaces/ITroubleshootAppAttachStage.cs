using AppAttachAPI.Response.Interfaces;
using System.Collections.Generic;

namespace TroubleshootAppAttachPublish.Interfaces
{
    public interface ITroubleshootAppAttachStage
    {
        List<IAppAttachOutput> stage(string packagePath);

    }
}
