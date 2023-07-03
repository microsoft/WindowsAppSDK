// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachAPI.Data;
using AppAttachAPI.Response.Implementations;
using System.Collections.Generic;

namespace AppAttachAPI
{
    /// <summary>
    /// Defines an interface for attribute validation strategy.
    /// </summary>
    public interface IValidationStrategy
    {
        /// <summary>
        /// Uses the defined strategy to validate app attach attributes
        /// </summary>
        /// <param name="attributes"></param>
        /// <param name="response"></param>
        /// <returns></returns>
        bool validate(Dictionary<string, IAttribute> attributes, AppAttachFlowResponse response);
    }
}
