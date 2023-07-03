// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachAPI;
using AppAttachAPI.Data;
using AppAttachAPI.Response.Implementations;
using AppAttachAPI.Utils;
using AVDAppAttachValidate.Constants;
using System.Collections.Generic;

namespace AVDAppAttachValidate.Implementations
{
    /// <summary>
    /// This validation strategy verifies whether the environment is setup currently checking whether visual studio is running in admin mode.
    /// </summary>
    public class EnvironmentCheckStrategy : IValidationStrategy
    {
        /// <summary>
        /// Validates the given attributes according to the strategy described above.
        /// </summary>
        /// <param name="attributes"></param>
        /// <param name="response"></param>
        /// <returns></returns>
        public bool validate(Dictionary<string, IAttribute> attributes, AppAttachFlowResponse response)
        {
            // Generates powershell script that validates the strategy
            var scriptPath = FileUtils.generateResourceFile(ScriptResources.EnvironmentCheckScript, "EnvironmentCheckScript.ps1");

            var powershellIsRunningAsAdmin = PowerShellConstants.POWERSHELL_IS_RUNNING_AS_ADMIN;
            var powershellIsNotRunningAsAdmin = PowerShellConstants.POWERSHELL_IS_NOT_RUNNING_AS_ADMIN;

            // Execute PowerShell script
            var powerShellOutput = PowerShellUtils.ExecutePowerShellScript(scriptPath, powershellIsRunningAsAdmin, powershellIsNotRunningAsAdmin);

            // Handle PowerShell output
            if (powerShellOutput.Contains(powershellIsRunningAsAdmin))
            {
                return true;
            }
            else if (powerShellOutput.Contains(powershellIsNotRunningAsAdmin))
            {
                response.getAppAttachOutputs().Add(new AppAttachOutput($"Please run Visual Studio in Admin Mode", true));
                response.setError(true);
                return false;
            }
            else
            {
                response.getAppAttachOutputs().Add(new AppAttachOutput($"Something went wrong while checking Visual Studio is running in admin mode or not", true));
                response.setError(true);
                return false;
            }
        }
    }
}
