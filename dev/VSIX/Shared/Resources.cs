// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License

using System;
using System.Globalization;
using System.Resources;

namespace WindowsAppSDK.TemplateUtilities
{
  internal class Resources
  {
    private readonly Lazy<ResourceManager> _resourceManager =
        new Lazy<ResourceManager>(() => new ResourceManager("WindowsAppSDK.Cs.Extension.VSPackage", typeof(Resources).Assembly));

    private ResourceManager ResourceManager => _resourceManager.Value;

    public string InstallingNuGetPackages => GetString("1044");
    public string OperationInProgress => GetString("1045");
    public string MissingPackageReferences => GetString("1046");
    public string UnableToAddReferencesMessageBox => GetString("1047");
    public string UnableToAddReferencesInfoBar => GetString("1048");
    public string ManageNuGetPackages => GetString("1049");
    public string SeeErrorDetails => GetString("1050");
    public string MissingPackageReferencesFor => GetString("1051");
    public string PleaseAddPackageReferences => GetString("1052");

    private string GetString(string name)
    {
        var value = ResourceManager.GetString(name, CultureInfo.CurrentUICulture);
        if (string.IsNullOrEmpty(value))
        {
            throw new MissingManifestResourceException($"Resource string '{name}' not found in resource file.");
        }
        return value;
    }

    public string Format(string format, params object[] args)
    {
        return string.Format(CultureInfo.CurrentCulture, format, args);
    }
  }
}
