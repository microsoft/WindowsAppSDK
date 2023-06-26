// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

namespace AppAttachAPI
{
    public interface IBootStrap : IDestinationType
    {
        IValidator getValidator();
        IArtifactGenerator getArtifactGenerator();
        IArtifactPublisher getArtifactPublisher();
    }
}
