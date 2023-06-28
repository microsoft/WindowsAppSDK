// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachAPI.Response.Implementations;
using AppAttachAPI.Response.Interfaces;
using AppAttachAPI.Utils;
using AVDAppAttachPublish.Interfaces;

using System;
using System.Collections.Generic;

namespace AVDAppAttachPublish.Implementations
{
    public class AVDAppAttachRemoveFromApplicationGroup : IAVDAppAttachRemoveFromApplicationGroup
    {
        private List<IAppAttachOutput> _errorList;
        private readonly string FILE_NAME;

        /// <summary>
        /// Initializes errorList.
        /// </summary>
        /// <param name="packagePath">The path of the MSIX package.</param>
        public AVDAppAttachRemoveFromApplicationGroup(string packagePath)
        {
            _errorList = new List<IAppAttachOutput>();
            FILE_NAME = FileUtils.extractFileNameWithoutExtension(packagePath);
        }

        /// <summary>
        /// Removes the MSIX package from the specified Azure Virtual Desktop application group.
        /// </summary>
        /// <param name="azureSubscriptionId">The Azure subscription ID.</param>
        /// <param name="azureResourceGroup">The Azure resource group name.</param>
        /// <param name="azureHostPoolName">The Azure Virtual Desktop host pool name.</param
        /// <param name="azureApplicationGroupName">The name of the Azure application group.</param>
        /// <returns>A list of IAppAttachErrorCode objects that represent any errors that occurred during removal.</returns>
        public List<IAppAttachOutput> removeFromApplicationGroup(string azureSubscriptionId, string azureResourceGroup, string azureHostPoolName, string azureApplicationGroupName)
        {
            try
            {
                // Remove the msix package from the host pool
                PowerShellUtils.ExecutePowerShellCommand(
                    "Get-AzWvdMsixPackage -HostPoolName \"{0}\" -ResourceGroupName \"{1}\" -SubscriptionId \"{2}\" -PackageAlias \"{3}\" | Remove-AzWvdMsixPackage",
                    azureHostPoolName, azureResourceGroup, azureSubscriptionId, FILE_NAME
                );

                // Remove the application from the application group
                PowerShellUtils.ExecutePowerShellCommand(
                    "Get-AzWvdApplication -ApplicationGroupName \"{0}\" -Name \"{1}\" -ResourceGroupName \"{2}\" -SubscriptionId \"{3}\" | Remove-AzWvdApplication",
                    azureApplicationGroupName, FILE_NAME, azureResourceGroup, azureSubscriptionId
                );
            }
            catch (Exception exception)
            {
                _errorList.Add(new AppAttachOutput(exception.Message, true));
            }
            return _errorList;
        }
    }
}
