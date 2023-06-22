// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using System.Security.Cryptography.X509Certificates;

namespace AppAttachExtension.Validator
{
    public class CommonValidator
    {
        public static string CertificateVerify(string certificatePath, string password)
        {
            string subject = "";
            try
            {
                X509Certificate2 certificate = new X509Certificate2(certificatePath, password);
                var privateKey = certificate.PrivateKey;
                var friendlyname = certificate.FriendlyName;
                subject = certificate.Subject;
                var issuer = certificate.Issuer;
                var expirydate = certificate.GetExpirationDateString();
                return subject;
            }
            catch
            {
                return subject;
            }
        }
    }
}
