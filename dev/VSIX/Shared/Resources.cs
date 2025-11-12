// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License

using System;
using System.Globalization;
using System.Resources;

namespace WindowsAppSDK.TemplateUtilities
{
    internal static class Resources
    {
        private static readonly Lazy<ResourceManager> _resourceManager =
            new Lazy<ResourceManager>(() => new ResourceManager("VSPackage", typeof(Resources).Assembly));

        private static ResourceManager ResourceManager => _resourceManager.Value;

        public static string InstallingNuGetPackages => GetString("1044");
        public static string OperationInProgress => GetString("1045");
        public static string MissingPackageReferences => GetString("1046");
        public static string UnableToAddReferencesMessageBox => GetString("1047");
        public static string UnableToAddReferencesInfoBar => GetString("1048");
        public static string ManageNuGetPackages => GetString("1049");
        public static string SeeErrorDetails => GetString("1050");
        public static string MissingPackageReferencesFor => GetString("1051");
        public static string PleaseAddPackageReferences => GetString("1052");

        private static string GetString(string name)
        {
            return ResourceManager.GetString(name, CultureInfo.CurrentUICulture) ?? name;
        }

        public static string Format(string format, params object[] args)
        {
            return string.Format(CultureInfo.CurrentCulture, format, args);
        }
    }
}
