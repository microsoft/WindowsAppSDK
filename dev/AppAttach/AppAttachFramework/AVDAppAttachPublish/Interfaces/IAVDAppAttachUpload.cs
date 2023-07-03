// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachAPI.Response.Interfaces;
using System.Collections.Generic;

namespace AVDAppAttachPublish.Interfaces
{
    public interface IAVDAppAttachUpload
    {
        /// <summary>
        /// Uploads a file to Azure Storage file share.
        /// </summary>
        /// <param name="packagePath">The path to the file to upload.</param>
        /// <param name="artifactName">The name of the artifact to upload.</param>
        /// <returns>The list of AppAttachErrorCode.</returns>
        List<IAppAttachOutput> upload(string packagePath);
    }
}
