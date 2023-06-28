// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using System;

namespace AVDAppAttachPublish.Exceptions
{
    /// <summary>
    /// The base class for all custom exceptions related to cloud publishing operations.
    /// </summary>
    public class CloudPublishException : Exception
    {
        public CloudPublishException() : base() { }
        public CloudPublishException(string errorMessage) : base(errorMessage) { }
    }
}
