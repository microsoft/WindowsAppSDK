using AppAttachAPI.Response;
using AppAttachAPI.Response.Interfaces;

namespace AppAttachArtifactGenerate.Interfaces
{
    public interface ICreateAppAttachImage
    {
        IAppAttachFlowResponse CreateAppAttachImage();
        string GetAppAttachImagePath();
    }
}