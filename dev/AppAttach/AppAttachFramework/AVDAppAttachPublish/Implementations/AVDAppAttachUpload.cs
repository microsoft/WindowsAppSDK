using AppAttachAPI.Response.Implementations;
using AppAttachAPI.Response.Interfaces;
using AppAttachAPI.Utils;
using AVDAppAttachPublish.Exceptions;
using AVDAppAttachPublish.Interfaces;
using Microsoft.WindowsAzure.Storage;
using Microsoft.WindowsAzure.Storage.File;
using System;
using System.Collections.Generic;

namespace AVDAppAttachPublish.Implementations
{
    /// <summary>
    /// Represents the AVD AppAttach upload class implementing IAVDAppAttachUpload interface.
    /// </summary>
    public class AVDAppAttachUpload : IAVDAppAttachUpload
    {
        private List<IAppAttachOutput> _errorList;
        private CloudStorageAccount _storageAccount;
        private CloudFileClient _fileClient;
        private string _shareName;

        /// <summary>
        /// Initializes a new instance of the <see cref="AVDAppAttachUpload"/> class with the specified Azure Storage key and file share name.
        /// </summary>
        /// <param name="azureStorageKey">The Azure Storage key.</param>
        /// <param name="azureStorageFileShare">The Azure Storage file share name.</param>
        public AVDAppAttachUpload(string azureStorageKey, string azureStorageFileShare)
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
        /// Uploads a file to Azure Storage file share.
        /// </summary>
        /// <param name="packagePath">The path to the file to upload.</param>
        /// <param name="artifactName">The name of the artifact to upload.</param>
        /// <returns>The list of AppAttachErrorCode.</returns>
        public List<IAppAttachOutput> upload(string packagePath)
        {
            string artifactName = FileUtils.extractFileNameWithExtension(packagePath);
            try
            {
                if (CheckFileExists(artifactName))
                {
                    throw new UploadFailedException(artifactName);
                }

                CloudFileShare fileShare = _fileClient.GetShareReference(_shareName);
                CloudFileDirectory rootDir = fileShare.GetRootDirectoryReference();
                CloudFile cloudFile = rootDir.GetFileReference(artifactName);

                cloudFile.UploadFromFile(packagePath);
            }
            catch (UploadFailedException exception)
            {
                _errorList.Add(new AppAttachOutput(exception.Message, true));
            }
            return _errorList;
        }

        private bool CheckFileExists(string artifactName)
        {
            CloudFileShare fileShare = _fileClient.GetShareReference(_shareName);
            CloudFileDirectory rootDir = fileShare.GetRootDirectoryReference();
            CloudFile cloudFile = rootDir.GetFileReference(artifactName);

            return cloudFile.Exists();
        }
    }
}
