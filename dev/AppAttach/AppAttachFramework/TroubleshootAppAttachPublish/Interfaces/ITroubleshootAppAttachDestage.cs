using AppAttachAPI.Response.Interfaces;
using System.Collections.Generic;

namespace TroubleshootAppAttachPublish.Interfaces
{
    public interface ITroubleshootAppAttachDestage
    {

        List<IAppAttachOutput> deStage(string packagePath);
    }
}
