using System.Collections;
using System.Reflection;
using System.Xml;

namespace AppAttachAPI.Exceptions
{
    /// <summary>
    /// A static class containing error messages for various publishing-related errors.
    /// </summary>
    public static class Messages
    {
        private static Hashtable _errorTable;

        // TODO: Add support for localization
        /*
         * private static CultureInfo _cultureInfo = CultureInfo.InstalledUICulture;
         * private static readonly string LOCALE = _cultureInfo.Name;
        */

        private static readonly string XML_RESOURCE_PATH = "AppAttachAPI.Exceptions.Resources.error-codes.xml";

        static Messages()
        {
            _errorTable = new Hashtable();
            LoadErrorTable();
        }

        private static void LoadErrorTable()
        {
            XmlDocument xmlDocument = new XmlDocument();
            var assembly = Assembly.GetExecutingAssembly();
            xmlDocument.Load(assembly.GetManifestResourceStream(XML_RESOURCE_PATH));

            XmlNodeList errorNodes = xmlDocument.SelectNodes("//error");
            foreach (XmlNode errorNode in errorNodes)
            {
                string errorCode = errorNode.Attributes["code"].Value;
                string errorMessage = errorNode.SelectSingleNode("message").InnerText;

                _errorTable.Add(errorCode, errorMessage);
            }
        }

        /// <summary>
        /// Returns the error message for the specified error code and locale.
        /// </summary>
        /// <param name="errorCode">The error code to retrieve the message for</param>
        /// <param name="values">The params needed if any wildcard exists in message.</param>
        /// <returns>The error message for the specified error code and locale, or <c>null</c>
        /// if no message is found</returns>
        public static string GetErrorMessage(string errorCode, params object[] values)
        {
            if (_errorTable.Contains(errorCode))
            {
                string errorMessage = (string)_errorTable[errorCode];
                if (values.Length > 0)
                {
                    errorMessage = string.Format(errorMessage, values);
                }
                return errorMessage;
            }
            else
            {
                return "Unknown error code.";
            }
        }
    }
}
