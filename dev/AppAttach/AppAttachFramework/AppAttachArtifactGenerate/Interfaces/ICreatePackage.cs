// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using AppAttachAPI.Response.Interfaces;

namespace AppAttachArtifactGenerate.Interfaces
{
    public interface ICreatePackage
    {
        IAppAttachFlowResponse CreatePackage();
        string GetPackagePath();
    }
}
