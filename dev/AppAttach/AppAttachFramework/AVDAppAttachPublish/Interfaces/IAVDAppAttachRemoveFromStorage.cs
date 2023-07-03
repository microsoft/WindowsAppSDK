// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachAPI.Response.Interfaces;
using System.Collections.Generic;

namespace AVDAppAttachPublish.Interfaces
{
    public interface IAVDAppAttachRemoveFromStorage
    {

        /// <summary>
        /// Removes a file from Azure Storage file share.
        /// </summary>
        /// <returns>A boolean indicating whether the operation was successful or not.</returns>
        List<IAppAttachOutput> removeFromStorage(string packagepath);
    }
}
