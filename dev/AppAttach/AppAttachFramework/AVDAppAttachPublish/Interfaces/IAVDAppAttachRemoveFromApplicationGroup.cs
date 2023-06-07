using AppAttachAPI.Response.Interfaces;
using System.Collections.Generic;

namespace AVDAppAttachPublish.Interfaces
{
    public interface IAVDAppAttachRemoveFromApplicationGroup
    {

        /// <summary>
        /// Removes the MSIX package from the specified Azure Virtual Desktop application group.
        /// </summary>
        /// <param name="azureSubscriptionId">The Azure subscription ID.</param>
        /// <param name="azureResourceGroup">The Azure resource group name.</param>
        /// <param name="azureHostPoolName">The Azure Virtual Desktop host pool name.</param
        /// <param name="azureApplicationGroupName">The name of the Azure application group.</param>
        /// <returns>A list of IAppAttachErrorCode objects that represent any errors that occurred during removal.</returns>
        List<IAppAttachOutput> removeFromApplicationGroup(string azureSubscriptionId, string azureResourceGroup, string azureHostPoolName, string azureApplicationGroupName);
    }
}
