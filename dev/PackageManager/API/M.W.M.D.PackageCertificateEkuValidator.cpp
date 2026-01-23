// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

#include "pch.h"
#include "M.W.M.D.PackageCertificateEkuValidator.h"
#include "Microsoft.Windows.Management.Deployment.PackageCertificateEkuValidator.g.cpp"
#include <Microsoft.Utf8.h>

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    PackageCertificateEkuValidator::PackageCertificateEkuValidator(hstring const& expectedCertificateEku)
    {
        m_expectedEku = expectedCertificateEku;
    }

    bool PackageCertificateEkuValidator::IsPackageValid(winrt::Windows::Foundation::IInspectable const& appxPackagingObject)
    {
        winrt::com_ptr<IAppxPackageReader> packageReader;
        if (SUCCEEDED(appxPackagingObject.as(IID_PPV_ARGS(&packageReader))))
        {
            winrt::com_ptr<IAppxFile> signatureFile;
            if (FAILED_LOG(packageReader->GetFootprintFile(APPX_FOOTPRINT_FILE_TYPE_SIGNATURE, signatureFile.put())))
            {
                return false;
            }

            return CheckSignature(signatureFile.get());
        }

        winrt::com_ptr<IAppxBundleReader> bundleReader;
        if (SUCCEEDED(appxPackagingObject.as(IID_PPV_ARGS(&bundleReader))))
        {
            winrt::com_ptr<IAppxFile> signatureFile;
            if (FAILED_LOG(bundleReader->GetFootprintFile(APPX_BUNDLE_FOOTPRINT_FILE_TYPE_SIGNATURE, signatureFile.put())))
            {
                return false;
            }

            return CheckSignature(signatureFile.get());
        }

        THROW_HR(APPX_E_CORRUPT_CONTENT);
    }

    bool PackageCertificateEkuValidator::CheckSignature(IAppxFile* signatureFile)
    {
        winrt::com_ptr<IStream> signatureStream;
        THROW_IF_FAILED(signatureFile->GetStream(signatureStream.put()));

        // The p7x signature should have a leading 4-byte PKCX header
        static constexpr DWORD P7xFileId{ 0x58434b50 }; // PKCX
        static constexpr DWORD P7xFileIdSize{ sizeof(P7xFileId) };

        STATSTG streamStats{};
        THROW_IF_FAILED(signatureStream->Stat(&streamStats, STATFLAG_NONAME));
        if (streamStats.cbSize.HighPart > 0 || streamStats.cbSize.LowPart < P7xFileIdSize)
        {
            std::ignore = LOG_HR_MSG(HRESULT_FROM_WIN32(ERROR_BAD_FORMAT), "StreamSize=0x%08X%08X", streamStats.cbSize.HighPart, streamStats.cbSize.LowPart);
            return false;
        }

        const DWORD streamSize{ streamStats.cbSize.LowPart };
        auto streamBuffer{ wil::make_unique_nothrow<BYTE[]>(streamSize) };
        THROW_IF_NULL_ALLOC(streamBuffer);

        ULONG bytesRead{};
        THROW_IF_FAILED(signatureStream->Read(streamBuffer.get(), streamSize, &bytesRead));
        THROW_HR_IF(HRESULT_FROM_WIN32(ERROR_BAD_FORMAT), bytesRead != streamSize);

        const auto streamFileId{ *reinterpret_cast<DWORD*>(streamBuffer.get()) };
        if (streamFileId != P7xFileId)
        {
            std::ignore = LOG_HR_MSG(HRESULT_FROM_WIN32(ERROR_BAD_FORMAT), "FileId=0x%08X", streamFileId);
            return false;
        }

        CRYPT_DATA_BLOB signatureBlob{};
        signatureBlob.cbData = streamSize - P7xFileIdSize;
        signatureBlob.pbData = streamBuffer.get() + P7xFileIdSize;

        wil::unique_hcertstore certStore;
        wil::unique_hcryptmsg signedMessage;
        DWORD queryContentType{};
        DWORD queryFormatType{};
        if (!CryptQueryObject(
            CERT_QUERY_OBJECT_BLOB,
            &signatureBlob,
            CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED,
            CERT_QUERY_FORMAT_FLAG_BINARY,
            0,      // Reserved parameter
            nullptr,   // No encoding info needed
            &queryContentType,
            &queryFormatType,
            &certStore,
            &signedMessage,
            nullptr    // No additional params for signed message output
        ))
        {
            std::ignore = LOG_LAST_ERROR();
            return false;
        }

        if (queryContentType != CERT_QUERY_CONTENT_PKCS7_SIGNED || queryFormatType != CERT_QUERY_FORMAT_BINARY || !certStore || !signedMessage)
        {
            std::ignore = LOG_HR_MSG(HRESULT_FROM_WIN32(ERROR_BAD_FORMAT), "ContentType=%u, FormatType=%u", queryContentType, queryFormatType);
            return false;
        }

        DWORD signerInfoSize{};
        if (!CryptMsgGetParam(signedMessage.get(), CMSG_SIGNER_INFO_PARAM, 0, nullptr, &signerInfoSize))
        {
            std::ignore = LOG_LAST_ERROR();
            return false;
        }

        if (signerInfoSize == 0 || signerInfoSize >= STRSAFE_MAX_CCH)
        {
            std::ignore = LOG_HR_MSG(HRESULT_FROM_WIN32(ERROR_BAD_FORMAT), "SignerInfoSize=%u", signerInfoSize);
            return false;
        }

        auto signerInfoBuffer{ wil::make_unique_nothrow<BYTE[]>(signerInfoSize) };
        THROW_IF_NULL_ALLOC(signerInfoBuffer);
        CMSG_SIGNER_INFO* signerInfo{ reinterpret_cast<CMSG_SIGNER_INFO*>(signerInfoBuffer.get()) };
        if (!CryptMsgGetParam(signedMessage.get(), CMSG_SIGNER_INFO_PARAM, 0, signerInfo, &signerInfoSize))
        {
            std::ignore = LOG_LAST_ERROR();
            return false;
        }

        // Get the signing certificate from the certificate store based on the issuer and serial number of the signer info
        CERT_INFO certInfo;
        certInfo.Issuer = signerInfo->Issuer;
        certInfo.SerialNumber = signerInfo->SerialNumber;

        wil::unique_cert_context certContext{
            CertGetSubjectCertificateFromStore(
                certStore.get(),
                X509_ASN_ENCODING | PKCS_7_ASN_ENCODING,
                &certInfo)
        };
        if (!certContext)
        {
            std::ignore = LOG_LAST_ERROR();
            return false;
        }

        DWORD ekuBufferSize{};
        if (!CertGetEnhancedKeyUsage(
            certContext.get(),
            0, // Accept EKU from EKU extension or EKU extended properties
            nullptr,
            &ekuBufferSize))
        {
            std::ignore = LOG_LAST_ERROR();
            return false;
        }

        if (ekuBufferSize < sizeof(CERT_ENHKEY_USAGE))
        {
            std::ignore = LOG_HR_MSG(HRESULT_FROM_WIN32(ERROR_BAD_FORMAT), "Size=%u", ekuBufferSize);
            return false;
        }

        auto ekuBuffer{ wil::make_unique_nothrow<BYTE[]>(ekuBufferSize)};
        THROW_IF_NULL_ALLOC(ekuBuffer);
        PCERT_ENHKEY_USAGE ekusFound{ reinterpret_cast<PCERT_ENHKEY_USAGE>(ekuBuffer.get()) };
        if (!CertGetEnhancedKeyUsage(
            certContext.get(),
            0, // Accept EKU from EKU extension or EKU extended properties
            ekusFound,
            &ekuBufferSize))
        {
            std::ignore = LOG_LAST_ERROR();
            return false;
        }

        for (DWORD i = 0; i < ekusFound->cUsageIdentifier; i++)
        {
            const auto ekuUtf18{ ::Microsoft::Utf8::ToUtf16<std::unique_ptr<WCHAR[]>>(ekusFound->rgpszUsageIdentifier[i]) };
            if (wcscmp(ekuUtf18.get(), m_expectedEku.c_str()) == 0)
            {
                return true;
            }
        }

        std::ignore = LOG_HR_MSG(HRESULT_FROM_WIN32(ERROR_BAD_FORMAT), "EKU not found");
        return false;
    }
}
