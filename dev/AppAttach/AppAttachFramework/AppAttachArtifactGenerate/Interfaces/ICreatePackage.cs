using AppAttachAPI.Response;
using AppAttachAPI.Response.Interfaces;

namespace AppAttachArtifactGenerate.Interfaces
{
    public interface ICreatePackage
    {
        IAppAttachFlowResponse CreatePackage();
        string GetPackagePath();
    }
}
