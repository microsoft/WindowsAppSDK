using AppAttachAPI.AttributeImpls;
using AppAttachAPI.Response;
using AppAttachAPI.Response.Implementations;
using AppAttachAPI.Response.Interfaces;
using AppAttachAPI.Utils;
using AppAttachArtifactGenerate.Interfaces;
using AppAttachAPI.Constants;
using System;
using System.Collections.Generic;
using System.IO;

namespace AppAttachArtifactGenerate.Implementations
{
    public class CreateVHDXAppAttachImage : ICreateAppAttachImage
    {
        private string _packagePath;
        private string _msixMgrPath;
        private string _appAttachImagePath;
        private double _vhdxSize;
        public CreateVHDXAppAttachImage(AppAttachImageInfo appAttachImageInfoData)
        {
            _packagePath = appAttachImageInfoData.packagePath;
            _msixMgrPath = appAttachImageInfoData.msixMgrPath;
        }

        public IAppAttachFlowResponse CreateAppAttachImage()
        {

            try
            {
                _appAttachImagePath = Path.ChangeExtension(_packagePath, null) + "." + ArtifactConstants.Extensions.VHDX;
                _vhdxSize = ArtifactGenerateUtils.getArtifactSize(_packagePath);
                if (_vhdxSize > 2040000)
                {
                    return new AppAttachFlowResponse(true, null, new List<IAppAttachOutput>() { new AppAttachOutput("VHDX size is more than 204GB", true) });
                }

                PowerShellUtils.ExecutePowerShellCommand(CmdCreateVHDX());

                return new AppAttachFlowResponse(false, _appAttachImagePath, new List<IAppAttachOutput>() { new AppAttachOutput("SUCCESS", false) });
            }
            catch (Exception exception)
            {
                return new AppAttachFlowResponse(true, null, new List<IAppAttachOutput>() { new AppAttachOutput(exception.Message, true) });
            }
        }

        public string GetAppAttachImagePath()
        {
            return _appAttachImagePath;
        }

        private string CmdCreateVHDX()
        {
            return String.Format("& \'{0}\' -Unpack -packagePath \'{1}\' -destination \'{2}\' -applyacls -create -vhdSize \'{3}\' -filetype \'vhdx\' -rootDirectory apps",
                    _msixMgrPath, _packagePath, _appAttachImagePath, _vhdxSize);
        }

    }
}
