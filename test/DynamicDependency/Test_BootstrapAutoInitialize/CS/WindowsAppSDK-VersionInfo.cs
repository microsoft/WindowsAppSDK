// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

namespace Microsoft.WindowsAppSDK
{
    // Release information
    public class Release
    {
        public const ushort Major = 1;
        public const ushort Minor = 1;
        public const ushort Patch = 0;
        public const uint MajorMinor = 0x00010001;

        public const string Channel = "preview";

        public const string VersionTag = "preview1";

        public const string VersionShortTag = "p1";
    }

    // Runtime information
    namespace Runtime
    {
        public class Identity
        {
            public const string Publisher = "CN=Microsoft Corporation, O=Microsoft Corporation, L=Redmond, S=Washington, C=US";
            public const string PublisherId = "8wekyb3d8bbwe";
        }

        public class Version
        {
            public const ushort Major = 1000;
            public const ushort Minor = 446;
            public const ushort Build = 804;
            public const ushort Revision = 0;
            public const ulong UInt64 = 0x03E801BE03240000;
            public const string DotQuadString = "1000.446.804.0";
        }

        namespace Packages
        {
            public class Framework
            {
                public const string PackageFamilyName = "Microsoft.WindowsAppRuntime.1.1-preview1_8wekyb3d8bbwe";
            }
            public class Main
            {
                public const string PackageFamilyName = "MicrosoftCorporationII.WinAppRuntime.Main.1.1-p1_8wekyb3d8bbwe";
            }
            public class Singleton
            {
                public const string PackageFamilyName = "MicrosoftCorporationII.WinAppRuntime.Singleton-p1_8wekyb3d8bbwe";
            }
        }
    }
}
