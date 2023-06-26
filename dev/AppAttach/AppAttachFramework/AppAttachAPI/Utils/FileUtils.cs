// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using System;
using System.Diagnostics;
using System.IO;
using System.Threading;

namespace AppAttachAPI.Utils
{
    /// <summary>
    /// Utility class for file-related operations.
    /// </summary>
    public static class FileUtils
    {
        private static readonly string _logFolderPath = Path.Combine(Environment.GetFolderPath(Environment.SpecialFolder.LocalApplicationData), "Temp", "AppAttach");
        private static readonly string _logFilePath = Path.Combine(_logFolderPath, "AppAttachLog.log");
        private static readonly object _lockObject = new object();
        private static readonly ThreadLocal<Guid> _guid = new ThreadLocal<Guid>(() => Guid.NewGuid());
        // private static readonly ThreadLocal<string> _guid = new ThreadLocal<string>(() => Convert.ToBase64String(Guid.NewGuid().ToByteArray()).Substring(0, 8));

        private static string _source = Process.GetCurrentProcess().ProcessName;
        private static string _hostName = Environment.MachineName;
        private static string _osVersion = Environment.OSVersion.ToString();
        private static string _timeZone = TimeZoneInfo.Local.StandardName;
        private static string _username = Environment.UserName;

        /// <summary>
        /// Generates a resource file with the specified content and returns the full path of the file.
        /// </summary>
        /// <param name="content"></param>
        /// <param name="resourceName"></param>
        /// <returns></returns>
        public static string generateResourceFile(string content, string resourceName)
        {
            var fullPath = System.IO.Path.GetTempPath() + resourceName;
            File.WriteAllText(fullPath, content);
            return fullPath;
        }

        public static bool CheckFileExists(string filePath)
        {
            return System.IO.File.Exists(filePath);
        }

        public static string extractFileNameWithExtension(string packagePath)
        {
            return Path.GetFileName(packagePath);
        }

        public static string extractFileNameWithoutExtension(string packagePath)
        {
            return Path.GetFileNameWithoutExtension(Path.GetFileName(packagePath));
        }

        public static void WriteLog(string message)
        {
            try
            {
                lock (_lockObject)
                {
                    // Create the directory if it doesn't exist
                    var logDirectory = Path.GetDirectoryName(_logFilePath);
                    if (!Directory.Exists(logDirectory))
                    {
                        Directory.CreateDirectory(logDirectory);
                    }

                    // Write the message to the log file
                    using (var writer = File.AppendText(_logFilePath))
                    {
                        writer.WriteLine($"{DateTime.Now.ToString("yyyy-MM-dd HH:mm:ss.fffZ")} [{_source}] [{_hostName}] [{_osVersion}] [{_timeZone}] [{_username}] [{_guid.Value}] ------ {message} ");
                    }
                }
            }
            catch (Exception ex)
            {
                // Handle any exceptions that occur while writing to the log file
                // For example, you could log the exception to the system event log
                Console.WriteLine($"An error occurred while writing to the log file: {ex.Message}");
            }
        }

        public static void removeLogFolderIfExists()
        {
            if (Directory.Exists(_logFolderPath))
            {
                Directory.Delete(_logFolderPath, true);
            }
        }
    }
}
