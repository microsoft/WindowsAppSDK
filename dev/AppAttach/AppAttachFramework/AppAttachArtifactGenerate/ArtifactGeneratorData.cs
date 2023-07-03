namespace AppAttachArtifactGenerate
{
    public class PackageInfo
    {
        public string packageLocation { get; set; }
        public string msBuildPath { get; set; }
        public string projFilePath { get; set; }
        public string configuration { get; set; }
        public string platform { get; set; }
        public string certificatePath { get; set; }
        public string certificatePassword { get; set; }
        public string packageVersion { get; set; }
    }

    public class AppAttachImageInfo
    {
        public string packagePath { get; set; }
        public string msixMgrPath { get; set; }
    }

}
