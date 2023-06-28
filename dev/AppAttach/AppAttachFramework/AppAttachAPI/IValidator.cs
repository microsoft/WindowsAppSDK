// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachAPI.Data;
using AppAttachAPI.Response.Interfaces;
using System.Collections.Generic;

namespace AppAttachAPI
{
    /// <summary>
    /// Defines an interface for attribute validation.
    /// </summary>
    public interface IValidator : IDestinationType
    {
        /// <summary>
        /// Gets the validation status after the validation process.
        /// </summary>
        /// <returns></returns>
        List<IAppAttachOutput> getValidationStatus();

        /// <summary>
        /// Gets a list of attribute names that are required for validation.
        /// </summary>
        /// <param name="attributes"></param>
        /// <returns></returns>
        List<string> getRequiredAttributeNamesList(Dictionary<string, IAttribute> attributes);

        /// <summary>
        /// Validates incoming attributes for the current implementation applying various strategies and attribute regex
        /// </summary>
        /// <param name="attributes"></param>
        /// <returns></returns>
        IAppAttachFlowResponse validate(Dictionary<string, IAttribute> attributes);
    }
}
