// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachAPI.Response.Interfaces;
using System.Collections.Generic;

namespace AVDAppAttachPublish.Interfaces
{
    public interface IAVDAppAttachDeploy
    {
        /// <summary>
        /// Deploys the Msix Package to the specified Azure WVD Host Pool and Application Group.
        /// </summary>
        /// <param name="azureSubscriptionId">The Azure Subscription ID.</param>
        /// <param name="azureResourceGroup">The name of the Azure Resource Group.</param>
        /// <param name="azureHostPoolName">The name of the Host Pool in which the Msix Package is to be deployed.</param>
        /// <param name="azureApplicationGroupName">The name of the Application Group to which the Msix Package is to be added.</param>
        /// <returns>A list of errors encountered during deployment.</returns>
        List<IAppAttachOutput> deploy(string azureSubscriptionId, string azureResourceGroup, string azureHostPoolName, string azureApplicationGroupName);

    }
}
