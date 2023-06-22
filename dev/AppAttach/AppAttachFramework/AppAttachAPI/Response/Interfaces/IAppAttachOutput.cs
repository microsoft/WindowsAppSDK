// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

namespace AppAttachAPI.Response.Interfaces
{
    public interface IAppAttachOutput
    {
        string getMessage();

        bool isError();
    }
}
