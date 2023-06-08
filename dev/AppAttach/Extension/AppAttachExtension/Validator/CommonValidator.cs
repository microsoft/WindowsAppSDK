using System;
using System.Collections.Generic;
using System.Linq;
using System.Security.Cryptography.X509Certificates;
using System.Security.Cryptography;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Controls;
using System.Windows;

namespace AppAttachExtension.Validator
{
    public class CommonValidator
    {
        public static string CertificateVerify(string certificatePath, string password)
        {
            string subject="";
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
