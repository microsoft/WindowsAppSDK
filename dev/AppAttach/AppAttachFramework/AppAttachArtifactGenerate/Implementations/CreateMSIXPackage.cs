using AppAttachAPI.Response.Implementations;
using AppAttachAPI.Response.Interfaces;
using AppAttachAPI.Utils;
using System;
using System.Collections.Generic;
using System.IO;
using System.Security.Cryptography.X509Certificates;
using AppAttachArtifactGenerate.Interfaces;
using AppAttachAPI.Response;
using AppAttachAPI.AttributeImpls;
using AppAttachAPI.Constants;

namespace AppAttachArtifactGenerate.Implementations
{
    public class CreateMSIXPackage : ICreatePackage
    {
        private string _packageLocation;
        private string _msBuildPath;
        private string _projFilePath;
        private string _configuration;
        private string _platform;
        private string _certificatePath;
        private string _certificatePassword;
        private string _packageVersion;
        private string _packagePath;
        private string _packageName;
        private string _certificateThumbPrint;

        public CreateMSIXPackage(PackageInfo packageInfoData)
        {
            _packageLocation = packageInfoData.packageLocation;
            _msBuildPath = packageInfoData.msBuildPath;
            _projFilePath = packageInfoData.projFilePath;
            _configuration = packageInfoData.configuration;
            _platform = packageInfoData.platform;
            _certificatePath = packageInfoData.certificatePath;
            _certificatePassword = packageInfoData.certificatePassword;
            _packageVersion = packageInfoData.packageVersion;
        }
        public IAppAttachFlowResponse CreatePackage()
        {
            try
            {
                IAppAttachFlowResponse result;

                _certificateThumbPrint = GetCertificateThumbPrint();
                ImportCertificate();

                _packageName = AttributeUtils.getOutputFile(_projFilePath, _packageVersion, _configuration, _platform);

                if (_packageLocation == null)
                {
                    _packageLocation = Path.GetDirectoryName(_projFilePath) + string.Format("\\bin\\AppPackages\\", _platform, _configuration);
                }

                // msbuild command to create and sign Package
                PowerShellUtils.ExecutePowerShellCommand(CmdBuildAndPackage());
                try
                {
                    _packagePath = Directory.GetFiles(_packageLocation, _packageName + "." + ArtifactConstants.Extensions.MSIX, SearchOption.AllDirectories)[0];
                }
                catch
                {
                    result = new AppAttachFlowResponse(true, null, new List<IAppAttachOutput>() { new AppAttachOutput($"Failed to find {_packageName}.msix", true) });
                    return result;
                }

                return new AppAttachFlowResponse(false, _packagePath, new List<IAppAttachOutput>() { new AppAttachOutput("SUCCESS", false) });
            }
            catch (Exception exception)
            {
                return new AppAttachFlowResponse(true, null, new List<IAppAttachOutput>() { new AppAttachOutput(exception.Message, true) });
            }
        }

        public string GetPackagePath()
        {
            return _packagePath;
        }
        private string GetCertificateThumbPrint()
        {
            X509Certificate2 cert = new X509Certificate2(_certificatePath, _certificatePassword);
            return cert.Thumbprint;
        }

        private void ImportCertificate()
        {
            // check if certificate is already imported on the system
            string certificateOutput = PowerShellUtils.ExecutePowerShellCommand(
                "& Get-ChildItem -Path Cert:\\CurrentUser\\My | Where-Object {{$_.Thumbprint -eq \'{0}\'}}", _certificateThumbPrint
            );

            if (certificateOutput == "")
            {
                // import certificate on system
                PowerShellUtils.ExecutePowerShellCommand(
                    "& Import-PfxCertificate -FilePath \'{0}\' -Password (ConvertTo-SecureString -String \'{1}\' -AsPlainText -Force) -CertStoreLocation Cert:\\CurrentUser\\My",
                    _certificatePath, _certificatePassword
                );
            }
        }

        private string CmdBuildAndPackage()
        {
            return String.Format("& \'{0}\' \'{1}\' /p:Configuration=\'{2}\' /p:Platform=\'{3}\' /p:AppxPackageDir=\'{4}\' /p:AppxPackageName=\'{5}\' /p:AppxPackageSigningEnabled=true /p:PackageCertificateThumbprint=\'{6}\' /p:GenerateAppxPackageOnBuild=true",
                    _msBuildPath, _projFilePath, _configuration, _platform, _packageLocation + "\\", _packageName, _certificateThumbPrint);
        }
    }


}
