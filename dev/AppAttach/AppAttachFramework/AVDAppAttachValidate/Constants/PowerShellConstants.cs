using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace AVDAppAttachValidate.Constants
{
    public static class PowerShellConstants
    {
        public const string FILE_EXISTS_IN_FILESHARE = "Package already exists in File Share";
        public const string FILE_DOES_NOT_EXIST_IN_FILESHARE = "Package does not exist in File Share";
        public const string POWERSHELL_IS_RUNNING_AS_ADMIN = "PowerShell is running as an administrator";
        public const string POWERSHELL_IS_NOT_RUNNING_AS_ADMIN = "You are not running PowerShell as an administrator";
    }
}
