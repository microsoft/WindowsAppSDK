using AppAttachAPI.Response.Interfaces;
using System.Collections.Generic;

namespace TroubleshootAppAttachPublish.Interfaces
{
    public interface ITroubleshootAppAttachUnregister
    {
        List<IAppAttachOutput> unregister(string packagePath);

        List<IAppAttachOutput> cleanUp(string packagePath);
    }
}
