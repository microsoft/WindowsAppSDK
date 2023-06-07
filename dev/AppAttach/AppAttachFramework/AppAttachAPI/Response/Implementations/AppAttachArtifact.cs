using AppAttachAPI.Response.Interfaces;

namespace AppAttachAPI.Response.Implementations
{
    public class AppAttachArtifact : IAppAttachArtifact
    {
        private string _vhdxPath;

        public AppAttachArtifact(string vhdxPath)
        {
            _vhdxPath = vhdxPath;
        }

        public string getVHDXPath()
        {
            return _vhdxPath;
        }
    }
}