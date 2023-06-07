namespace AppAttachAPI
{
    public interface IBootStrap : IDestinationType
    {
        IValidator getValidator();
        IArtifactGenerator getArtifactGenerator();
        IArtifactPublisher getArtifactPublisher();
    }
}
