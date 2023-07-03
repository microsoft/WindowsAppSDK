// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachAPI.AttributeImpls;
using AppAttachAPI.Data;
using System;
using System.Collections.Generic;
using System.IO;

namespace AppAttachAPI.Utils
{
    /// <summary>
    /// Utility class for attribute-related operations.
    /// </summary>
    public static class AttributeUtils
    {
        /// <summary>
        /// Get the value of attribute isPublishRequired
        /// </summary>
        /// <param name="attributes"></param>
        /// <returns></returns>
        public static string getIsPublishRequired(Dictionary<string, IAttribute> attributes)
        {
            IAttribute isPublishRequired;
            if (!attributes.TryGetValue("isPublishRequired", out isPublishRequired))
            {
                isPublishRequired = new IsPublishRequired();
                isPublishRequired.setAttributeValue(bool.FalseString);
            }

            return isPublishRequired.getAttributeValue();
        }

        /// <summary>
        /// Generates the output file name based on the project file path, package version, configuration, and platform.
        /// </summary>
        /// <param name="projFilePath">The project file path.</param>
        /// <param name="packageVersion">The package version.</param>
        /// <param name="configuration">The configuration.</param>
        /// <param name="platform">The platform.</param>
        /// <returns>The generated output file name.</returns>
        public static string getOutputFile(string projFilePath, string packageVersion, string configuration, string platform)
        {
            return String.Format("{0}_{1}_{2}_{3}", Path.GetFileNameWithoutExtension(projFilePath), packageVersion, configuration, platform);
        }
    }
}
