using NuGet.Common;
using NuGet.Configuration;
using NuGet.Packaging.Core;
using NuGet.Protocol;
using NuGet.Protocol.Core.Types;
using NuGet.Versioning;
using System.Linq;
using System.Threading;
using System.Threading.Tasks;

namespace WindowsAppSDK.TemplateUtilities
{
    public static class NugetClientHelper
    {
        private static ISettings? settings = Settings.LoadDefaultSettings(null);
        public static string globalPackagesFolder = SettingsUtility.GetGlobalPackagesFolder(settings);

        [System.Runtime.InteropServices.DllImport("wininet.dll")]
        private extern static bool InternetGetConnectedState(out int Description, int ReservedValue);

        public static bool IsInternetAvailable()
        {
            int desc;
            return InternetGetConnectedState(out desc, 0);
        }

        public async static Task<IPackageSearchMetadata> GetPackageMetaDataAsync(string packageId, bool includePrerelease = false)
        {
            var repository = Repository.Factory.GetCoreV3("https://api.nuget.org/v3/index.json");
            var resource = await repository.GetResourceAsync<PackageSearchResource>();
            var searchFilter = new SearchFilter(includePrerelease: includePrerelease);

            var results = await resource.SearchAsync(
                packageId,
                searchFilter,
                skip: 0,
                take: 1,
                NullLogger.Instance,
                CancellationToken.None);

            return results?.FirstOrDefault();
        }

        public static bool IsCacheAvailableForPackage(string packageId, string packageVersion)
        {
            NuGetVersion version = new NuGetVersion(packageVersion);
            var package = GlobalPackagesFolderUtility.GetPackage(new PackageIdentity(packageId, version), globalPackagesFolder);
            return package != null;
        }
    }
}
