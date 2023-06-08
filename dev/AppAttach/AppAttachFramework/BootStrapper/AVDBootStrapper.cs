using AppAttachAPI;
using System.Reflection;
using AppAttachArtifactGenerate;
using AVDAppAttachPublish;
using AVDAppAttachValidate;

namespace BootStrapper
{

    public class AVDBootStrapper : IBootStrap
    {

        public DestinationType getDestinationType()
        {
            return DestinationType.AVD;
        }

        public IArtifactGenerator getArtifactGenerator()
        {
            return new AppAttachArtifactGenerator();
        }

        public IArtifactPublisher getArtifactPublisher()
        {
            return new AVDAppAttachPublisher();
        }

        public IValidator getValidator()
        {
            return new AVDAppAttachValidator();
        }

    }
}
