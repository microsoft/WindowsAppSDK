#include "pch.h"
#include "M.W.M.D.PackageCertificateEkuValidator.h"
#include "Microsoft.Windows.Management.Deployment.PackageCertificateEkuValidator.g.cpp"
#include <TerminalVelocityFeatures-PackageManager.h>

namespace winrt::Microsoft::Windows::Management::Deployment::implementation
{
    PackageCertificateEkuValidator::PackageCertificateEkuValidator(hstring const& expectedCertificateEku)
    {
        m_expectedEku = expectedCertificateEku;
    }

    bool PackageCertificateEkuValidator::IsPackageValid(winrt::Windows::Foundation::IInspectable const& appxPackagingObject)
    {
        winrt::com_ptr<IAppxPackageReader> packageReader;
        winrt::com_ptr<IAppxBundleReader> bundleReader;

        if (SUCCEEDED(appxPackagingObject.as(IID_PPV_ARGS(&packageReader))))
        {
            winrt::com_ptr<IAppxFile> signatureFile;
            if (SUCCEEDED(packageReader->GetFootprintFile(APPX_FOOTPRINT_FILE_TYPE_SIGNATURE, signatureFile.put())))
            {
                return CheckSignature(signatureFile.get());
            }
            else
            {
                return false; // package is not valid because there is no signature present
            }
        }
        else if (SUCCEEDED(appxPackagingObject.as(IID_PPV_ARGS(&bundleReader))))
        {
            winrt::com_ptr<IAppxFile> signatureFile;
            if (SUCCEEDED(bundleReader->GetFootprintFile(APPX_BUNDLE_FOOTPRINT_FILE_TYPE_SIGNATURE, signatureFile.put())))
            {
                return CheckSignature(signatureFile.get());
            }
            else
            {
                return false; // package is not valid because there is no signature present
            }
        }
        else
        {
            THROW_WIN32(ERROR_NOT_SUPPORTED);
        }
    }

    bool PackageCertificateEkuValidator::CheckSignature(IAppxFile* signatureFile)
    {
        winrt::com_ptr<IStream> signatureStream;
        THROW_IF_FAILED(signatureFile->GetStream(signatureStream.put()));

        // The p7x signature should have a leading 4-byte PKCX header
        static const DWORD P7xFileId = 0x58434b50; // PKCX
        static const DWORD P7xFileIdSize = sizeof(P7xFileId);

        STATSTG streamStats{};
        THROW_IF_FAILED(signatureStream->Stat(&streamStats, STATFLAG_NONAME));
        if (streamStats.cbSize.HighPart > 0 || streamStats.cbSize.LowPart < P7xFileIdSize)
        {
            return false; // The signature has unexpected size
        }

        DWORD streamSize = streamStats.cbSize.LowPart;
        auto streamBuffer{ wil::make_unique_nothrow<BYTE[]>(streamSize) };
        THROW_IF_NULL_ALLOC(streamBuffer);

        ULONG bytesRead{};
        THROW_IF_FAILED(signatureStream->Read(streamBuffer.get(), streamSize, &bytesRead));
        THROW_HR_IF(HRESULT_FROM_WIN32(ERROR_BAD_FORMAT), bytesRead != streamSize);

        if (*reinterpret_cast<DWORD*>(streamBuffer.get()) != P7xFileId)
        {
            return false; // The signature does not have expected header
        }

        CRYPT_DATA_BLOB signatureBlob{};
        signatureBlob.cbData = streamSize - P7xFileIdSize;
        signatureBlob.pbData = streamBuffer.get() + P7xFileIdSize;

        wil::unique_hcertstore certStore;
        wil::unique_hcryptmsg signedMessage;
        DWORD queryContentType = 0;
        DWORD queryFormatType = 0;
        if (!CryptQueryObject(
            CERT_QUERY_OBJECT_BLOB,
            &signatureBlob,
            CERT_QUERY_CONTENT_FLAG_PKCS7_SIGNED,
            CERT_QUERY_FORMAT_FLAG_BINARY,
            0,      // Reserved parameter
            NULL,   // No encoding info needed
            &queryContentType,
            &queryFormatType,
            &certStore,
            &signedMessage,
            NULL    // No additional params for signed message output
        ))
        {
            return false; // CryptQueryObject could not read the signature
        }

        if (queryContentType != CERT_QUERY_CONTENT_PKCS7_SIGNED || queryFormatType != CERT_QUERY_FORMAT_BINARY || !certStore || !signedMessage)
        {
            return false; // CryptQueryObject returned unexpected data
        }

        CMSG_SIGNER_INFO* signerInfo = NULL;
        DWORD signerInfoSize = 0;
        if (!CryptMsgGetParam(signedMessage.get(), CMSG_SIGNER_INFO_PARAM, 0, NULL, &signerInfoSize))
        {
            return false; // CryptMsgGetParam could not read the signature
        }

        if (signerInfoSize == 0 || signerInfoSize >= STRSAFE_MAX_CCH)
        {
            return false; // Signer info has unexpected size
        }

        auto signerInfoBuffer{ wil::make_unique_nothrow<BYTE[]>(signerInfoSize) };
        THROW_IF_NULL_ALLOC(signerInfoBuffer);
        signerInfo = reinterpret_cast<CMSG_SIGNER_INFO*>(signerInfoBuffer.get());
        if (!CryptMsgGetParam(signedMessage.get(), CMSG_SIGNER_INFO_PARAM, 0, signerInfo, &signerInfoSize))
        {
            return false; // CryptMsgGetParam could not read the signature
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
            return false; // CertGetSubjectCertificateFromStore could not find a cert context
        }

        DWORD ekuBufferSize = 0;
        if (!CertGetEnhancedKeyUsage(
            certContext.get(),
            0, // Accept EKU from EKU extension or EKU extended properties
            NULL,
            &ekuBufferSize))
        {
            return false; // CertGetEnhancedKeyUsage could not read EKUs
        }

        if (ekuBufferSize < sizeof(CERT_ENHKEY_USAGE))
        {
            return false; // No EKUs are found in the signature
        }

        auto ekuBuffer{ wil::make_unique_nothrow<BYTE[]>(ekuBufferSize)};
        THROW_IF_NULL_ALLOC(ekuBuffer);
        PCERT_ENHKEY_USAGE ekusFound = reinterpret_cast<PCERT_ENHKEY_USAGE>(ekuBuffer.get());
        if (!CertGetEnhancedKeyUsage(
            certContext.get(),
            0, // Accept EKU from EKU extension or EKU extended properties
            ekusFound,
            &ekuBufferSize))
        {
            return false; // CertGetEnhancedKeyUsage could not read EKUs
        }

        for (DWORD i = 0; i < ekusFound->cUsageIdentifier; i++)
        {
            auto eku{ ekusFound->rgpszUsageIdentifier[i] };

            int length = MultiByteToWideChar(CP_ACP, 0, eku, -1, nullptr, 0);
            auto ekuWcharBuffer{ wil::make_unique_nothrow<WCHAR[]>(length) };
            THROW_IF_NULL_ALLOC(ekuWcharBuffer);

            MultiByteToWideChar(CP_ACP, 0, eku, -1, ekuWcharBuffer.get(), length);

            if (wcscmp(ekuWcharBuffer.get(), m_expectedEku.c_str()) == 0)
            {
                return true; // Found expected EKU
            }
        }

        return false; // Did not find expected EKU
    }

}
