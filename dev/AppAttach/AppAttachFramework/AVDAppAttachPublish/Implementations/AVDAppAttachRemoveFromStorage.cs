// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachAPI.Response.Implementations;
using AppAttachAPI.Response.Interfaces;
using AppAttachAPI.Utils;
using AVDAppAttachPublish.Interfaces;
using Microsoft.WindowsAzure.Storage;
using Microsoft.WindowsAzure.Storage.File;
using System;
using System.Collections.Generic;

namespace AVDAppAttachPublish.Implementations
{
    public class AVDAppAttachRemoveFromStorage : IAVDAppAttachRemoveFromStorage
    {
        private List<IAppAttachOutput> _errorList;
        private CloudStorageAccount _storageAccount;
        private CloudFileClient _fileClient;
        private string _shareName;

        private bool CheckFileExists(string artifactName)
        {
            CloudFileShare fileShare = _fileClient.GetShareReference(_shareName);
            CloudFileDirectory rootDir = fileShare.GetRootDirectoryReference();
            CloudFile cloudFile = rootDir.GetFileReference(artifactName);

            return cloudFile.Exists();
        }

        /// <summary>
        /// Initializes a new instance of the <see cref="AVDAppAttachRemoveFromStorage"/> class with the specified Azure Storage key and file share name.
        /// </summary>
        /// <param name="azureStorageKey">The Azure Storage key.</param>
        /// <param name="azureStorageFileShare">The Azure Storage file share name.</param>
        public AVDAppAttachRemoveFromStorage(string azureStorageKey, string azureStorageFileShare)
        {
            _errorList = new List<IAppAttachOutput>();
            try
            {
                _storageAccount = CloudStorageAccount.Parse(azureStorageKey);
                _fileClient = _storageAccount.CreateCloudFileClient();
                _shareName = azureStorageFileShare;
            }
            catch (Exception exception)
            {
                _errorList.Add(new AppAttachOutput(exception.Message, true));
            }
        }

        /// <summary>
        /// Removes a file from Azure Storage file share.
        /// </summary>
        /// <param name="artifactName">The name of the MSIX package artifact.</param>
        /// <returns>A list of IAppAttachErrorCode objects indicating any errors that occurred during the operation.</returns>
        public List<IAppAttachOutput> removeFromStorage(string packageName)
        {
            string artifactName = FileUtils.extractFileNameWithExtension(packageName);
            try
            {
                // Set the reference to the file to be deleted
                CloudFileDirectory rootDir = _fileClient.GetShareReference(_shareName).GetRootDirectoryReference();
                CloudFile fileToDelete = rootDir.GetFileReference(artifactName);

                if (CheckFileExists(artifactName) && null != fileToDelete)
                {
                    // Delete the file
                    fileToDelete.Delete();
                }
            }
            catch (Exception exception)
            {
                _errorList.Add(new AppAttachOutput(exception.Message, true));
            }
            return _errorList;
        }
    }
}
