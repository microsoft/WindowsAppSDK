// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using System;
using System.Diagnostics;
using System.Linq;

namespace AppAttachAPI.Utils
{
    /// <summary>
    /// Utility class for executing PowerShell scripts.
    /// </summary>
    public static class PowerShellUtils
    {
        private static string ExecutePowerShell(string processArguments)
        {
            // Create a new process to execute the PowerShell command
            ProcessStartInfo startInfo = new ProcessStartInfo();
            startInfo.FileName = "powershell.exe";
            startInfo.Arguments = processArguments;
            startInfo.RedirectStandardOutput = true;
            startInfo.RedirectStandardError = true;
            startInfo.UseShellExecute = false;
            startInfo.CreateNoWindow = true;

            Process process = new Process();
            process.StartInfo = startInfo;

            // Write PowerShell to Log file
            if (processArguments.Contains("File"))
            {
                FileUtils.WriteLog($"Executing PowerShell file: {startInfo.FileName}\n");
            }
            else
            {
                FileUtils.WriteLog($"Executing PowerShell command: {processArguments}");
            }

            // Execute PowerShell and capture the output
            try
            {
                process.Start();
            }
            catch (Exception ex)
            {
                FileUtils.WriteLog($"Failed to start PowerShell process. Exception: {ex}");
                throw new Exception("Failed to start PowerShell process.", ex);
            }

            string output = process.StandardOutput.ReadToEnd();
            string error = process.StandardError.ReadToEnd();

            process.WaitForExit();

            // Write the output and error to the log file
            FileUtils.WriteLog($"PowerShell command output:\n{output}");

            if (process.ExitCode != 0 || !String.IsNullOrEmpty(error))
            {
                FileUtils.WriteLog($"PowerShell command exited with code {process.ExitCode} and the error is:\n{error}");
                throw new Exception($"PowerShell command exited with code {process.ExitCode}. Error message: {output + "\n" + error}");
            }

            return output;

        }

        public static string ExecutePowerShellCommand(string command, params object[] parameters)
        {
            // Construct the PowerShell command string with the provided parameters
            if (parameters.Length > 0)
            {
                command = string.Format(command, parameters);
            }

            // Prepare PowerShell Arguments
            var arguments = $"-NoProfile -ExecutionPolicy unrestricted -Command \"{command}\"";

            return ExecutePowerShell(arguments);

        }

        /// <summary>
        /// Executes a PowerShell script with the specified script path and parameters.
        /// </summary>
        /// <param name="scriptPath"></param>
        /// <param name="parameters"></param>
        /// <returns></returns>
        /// <exception cref="Exception"></exception>
        public static string ExecutePowerShellScript(string scriptPath, params string[] parameters)
        {
            var arguments = "";

            // Construct the PowerShell command string with the provided parameters
            arguments = string.Join(" ", parameters.Select(s => $"\"{s}\""));

            // Prepare PowerShell Arguments
            var fullArguments = $"-ExecutionPolicy unrestricted -File \"{scriptPath}\" {arguments}";

            return ExecutePowerShell(fullArguments);
        }
    }
}
