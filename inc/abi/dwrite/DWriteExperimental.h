#pragma once

#if DWRITE_CORE

DWRITE_BEGIN_INTERFACE(IDWriteAsyncResult1, "C50F19A9-B4EC-47DB-9A66-C308C1E0045F") : IDWriteAsyncResult
{
    /// <summary>
    /// Blocks until the asynchronous operation completes, the specified timeout interval
    /// elapses, or Cancel is called, whichever comes first.
    /// </summary>
    /// <param name="timeoutMilliseconds">Maximum number of milliseconds to wait.</param>
    /// <returns>
    /// Returns S_OK if the operation completed successfully, DWRITE_E_DOWNLOADCANCELLED if
    /// Cancel was called, or a standard HRESULT error code of the operation failed. This
    /// should be the same value as returned by IDWriteAsyncResult::GetResult.
    /// </returns>
    /// <remarks>
    /// If this interface is implemented, DirectWrite calls this method instead of waiting
    /// on the event handled returned by IDWriteAsyncResult::GetWaitHandle.
    /// </remarks>
    STDMETHOD(WaitForCompletion)(UINT32 timeoutMilliseconds) PURE;

    /// <summary>
    /// Cancels the pending async operation.
    /// </summary>
    STDMETHOD_(void, Cancel)() PURE;
};

/// <summary>
/// Represents the status of a font download operation.
/// </summary>
enum DWRITE_DOWNLOAD_STATUS : UINT32
{
    /// <summary>
    /// The font download is in progress.
    /// </summary>
    DWRITE_DOWNLOAD_STATUS_PENDING,

    /// <summary>
    /// The font download completed successfully.
    /// </summary>
    DWRITE_DOWNLOAD_STATUS_COMPLETED,

    /// <summary>
    /// The font download failed.
    /// </summary>
    DWRITE_DOWNLOAD_STATUS_FAILED
};

/// <summary>
/// Represents a font file download operation. This object encapsulates all of the
/// font download requests for a specific file and provides methods for processing
/// those download requests.
/// </summary>
DWRITE_BEGIN_INTERFACE(IDWriteFileDownload, "FAC87BFA-B85A-4FEA-9FD5-D060962C297C") : IUnknown
{
    /// <summary>
    /// Gets the current status of the font file download operation. For a newly-created
    /// object, this is always DWRITE_DOWNLOAD_STATUS_PENDING.
    /// </summary>
    STDMETHOD_(DWRITE_DOWNLOAD_STATUS, GetStatus)() PURE;

    /// <summary>
    /// Gets the result of the font file download.
    /// </summary>
    /// <returns>Returns E_PENDING if the status is DWRITE_DOWNLOAD_STATUS_PENDING,
    /// S_OK if the status is DWRITE_DOWNLOAD_STATUS_COMPLETED, or an error code if
    /// the status is DWRITE_DOWNLOAD_STATUS_FAILED.</returns>
    STDMETHOD(GetDownloadResult)() PURE;

    /// <summary>
    /// Gets the remote font file stream for this file.
    /// </summary>
    /// <param name="fileStream">Receives a pointer to the font file stream object.</param>
    /// <returns>Returns a standard HRESULT error code.</returns>
    STDMETHOD(GetStream)(_COM_Outptr_ IDWriteRemoteFontFileStream** fileStream) PURE;

    /// <summary>
    /// Begins or continues a download operation. This function processes as much of the
    /// font file as possible without blocking.
    /// </summary>
    /// <param name="asyncResult">If the status on return is DWRITE_DOWNLOAD_STATUS_PENDING,
    /// receives a pointer to an async result object created by the loader's BeginDownload
    /// method. Otherwise, receives NULL.</param>
    /// <returns>Returns a standard HRESULT error code if the stauts on return is
    /// DWRITE_DOWNLOAD_STATUS_FAILED. Otherwise, returns S_OK.</returns>
    /// <remarks>If a non-null value is returned in asyncResult output parameter, the caller
    /// should wait for the async result to complete and then call BeginDownload again.</remarks>
    STDMETHOD(BeginDownload)(_COM_Outptr_result_maybenull_ IDWriteAsyncResult** asyncResult) PURE;
};

/// <summary>
/// Represents a list of font file download operations.
/// </summary>
DWRITE_BEGIN_INTERFACE(IDWriteFileDownloadList, "8AB33F0B-6724-47C6-A481-93B33AED6478") : IUnknown
{
    /// <summary>
    /// Gets the number of items in the list.
    /// </summary>
    STDMETHOD_(UINT32, GetFileCount)() PURE;

    /// <summary>
    /// Gets the font file download object with the specified index.
    /// </summary>
    /// <param name="index">Zero-based index of the object.</param>
    /// <param name="fileDownload">Receives a pointer to the font file download object.</param>
    /// <returns>Returns a standard HRESULT error code.</returns>
    STDMETHOD(GetFileDownload)(UINT32 index, _COM_Outptr_ IDWriteFileDownload** fileDownload) PURE;
};

DWRITE_BEGIN_INTERFACE(IDWriteFontDownloadQueue1, "96E1C125-3AB4-4728-AABA-E3C919B7F0D0") : IDWriteFontDownloadQueue
{
    /// <summary>
    /// Transfers the contents of the font download queue to a newly-created object. The returned
    /// object exposes a list of IDWriteFileDownload objects, each of which encapsulates the
    /// download requests for a given font file.
    /// </summary>
    /// <param name="downloadList">Receives a pointer to the newly-created object.</param>
    /// <returns>Returns a standard HRESULT error code.</returns>
    /// <remarks>This method provides an alternative to calling IDWriteFontDownloadQueue::BeginDownload.
    /// The client can call this method and then process the download requests for each file itself.</remarks>
    STDMETHOD(CreateDownloadListAndClearQueue)(_COM_Outptr_ IDWriteFileDownloadList** downloadList) PURE;

    /// <summary>
    /// Invokes the DownloadCompleted method of each registered IDWriteFontDownloadListener object.
    /// </summary>
    /// <param name="clientContext">Optional context object.</param>
    /// <param name="downloadResult">Result of the download operation.</param>
    /// <remarks>Downloads initiated by IDWriteFontDownloadQueue::BeginDownload automatically call
    /// this method. However, if a client calls CreateDownloadListAndClearQueue and processes the
    /// download requests itself, the client may call this method to notify download listeners upon
    /// completion.
    /// </remarks>
    STDMETHOD_(void, InvokeDownloadCompleted)(_In_opt_ IUnknown* context, HRESULT downloadResult) PURE;
};

#endif
