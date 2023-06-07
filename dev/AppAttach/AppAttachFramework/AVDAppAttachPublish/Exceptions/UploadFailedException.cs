using AppAttachAPI.Exceptions;

namespace AVDAppAttachPublish.Exceptions
{
    /// <summary>
    /// An exception class to indicate that a file upload operation has failed.
    /// This exception extends the <see cref="CloudPublishException"/> base class.
    /// </summary>
    public class UploadFailedException : CloudPublishException
    {
        private static readonly string errorCode = "AAA0004";

        /// <summary>
        /// Constructs a new <see cref="UploadFailedException"/> object with the error message
        /// retrieved from the <see cref="ErrorMessages"/> class based on the specified error code.
        /// </summary>
        /// <param name="errorCode">The error code for the upload failure</param>
        public UploadFailedException(params object[] values) : base(Messages.GetErrorMessage(errorCode, values)) { }
    }
}
