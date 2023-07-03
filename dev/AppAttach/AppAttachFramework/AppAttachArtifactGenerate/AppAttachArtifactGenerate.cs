// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachAPI;
using AppAttachAPI.AttributeImpls;
using AppAttachAPI.Constants;
using AppAttachAPI.Data;
using AppAttachAPI.Response.Implementations;
using AppAttachAPI.Response.Interfaces;
using AppAttachArtifactGenerate.Implementations;
using AppAttachArtifactGenerate.Interfaces;
using System.Collections.Generic;

namespace AppAttachArtifactGenerate
{
    public class AppAttachArtifactGenerator : IArtifactGenerator
    {
        public IAppAttachFlowResponse generateArtifact(Dictionary<string, IAttribute> attributes)
        {
            PackageInfo msixPackageInfo = new PackageInfo
            {
                packageLocation = attributes.ContainsKey(AttrConsts.PACKAGE_LOCATION) ? attributes[AttrConsts.PACKAGE_LOCATION].getAttributeValue() : null,
                msBuildPath = attributes[AttrConsts.MSBUILD_PATH].getAttributeValue(),
                projFilePath = attributes[AttrConsts.PROJECT_FILE_PATH].getAttributeValue(),
                configuration = attributes[AttrConsts.CONFIGURATION].getAttributeValue(),
                platform = attributes[AttrConsts.PLATFORM].getAttributeValue(),
                certificatePath = attributes[AttrConsts.CERTIFICATE_PATH].getAttributeValue(),
                certificatePassword = attributes[AttrConsts.CERTIFICATE_PASSWORD].getAttributeValue(),
                packageVersion = attributes[AttrConsts.PACKAGE_VERSION].getAttributeValue()
            };

            ICreatePackage package = new CreateMSIXPackage(msixPackageInfo);
            IAppAttachFlowResponse packageResponse = package.CreatePackage();

            if (packageResponse.getAppAttachOutputs()[0].isError())
            {
                return packageResponse;
            }

            AppAttachImageInfo vhdxAttachImageInfo = new AppAttachImageInfo
            {
                packagePath = package.GetPackagePath(),
                msixMgrPath = attributes[AttrConsts.MSIX_MANAGER_PATH].getAttributeValue()
            };

            ICreateAppAttachImage appAttachImage = new CreateVHDXAppAttachImage(vhdxAttachImageInfo);
            IAppAttachFlowResponse appAttachImageResponse = appAttachImage.CreateAppAttachImage();

            if (!(appAttachImageResponse.getAppAttachOutputs()[0].isError()))
            {
                appAttachImageResponse = new AppAttachFlowResponse(false, appAttachImageResponse.getAppAttachArtifact().getVHDXPath(), new List<IAppAttachOutput>() { });
                AppAttachImagePath appAttachImagePathAttr = new AppAttachImagePath();
                appAttachImagePathAttr.setAttributeValue(appAttachImage.GetAppAttachImagePath());
                attributes.Add(AttrConsts.APPATTACH_IMAGE_PATH, appAttachImagePathAttr);
            }


            return appAttachImageResponse;
        }

        public DestinationType getDestinationType()
        {
            return DestinationType.AVD;
        }

    }
}
