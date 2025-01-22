using System;
using System.Collections.Generic;
using System.Collections.Immutable;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Reflection;
using System.Reflection.Metadata;
using System.Reflection.Metadata.Ecma335;
using System.Reflection.PortableExecutable;
using CommandLine;
using StaticValidationCommon;

namespace PackageInspection
{
    class Options
    {
        [Option(Required = true)]
        public string PackagePath { get; set; }

        [Option(Required = true)]
        public string BuildType { get; set; }

        [Option]
        public string LogFilePath { get; set; }

        [Option]
        public bool CheckSigning { get; set; }

        [Option]
        public bool CheckDeterministic { get; set; }

        [Option]
        public string WindowsSdkBinDir { get; set; }

        public string AppxTool
        {
            get { return WindowsSdkBinDir + "\\makeappx.exe"; }
        }

        public string SignTool
        {
            get { return WindowsSdkBinDir + "\\signtool.exe"; }
        }
    }

    class CertValidation
    {
        public string File;                 
        public string IssuedToName;
        public string ExtraSignToolFlags;   // Extra flags to pass to signtool.exe.
        public int ValidationCount = 0;     // This counter is to ensure we found the files we were looking for.
    }

    class Program
    {
        private const string EXPERIMENTAL_ATTRIBUTE_NAME = "Windows.Foundation.Metadata.ExperimentalAttribute";
        private const string RootCertificate = "Microsoft Root Certificate";

        // We expect the output from signtool verify /v microsoft.internal.frameworkudk.dll to look something like this:
        //
        // Signature Index: 0 (Primary Signature)
        // Hash of file (sha256): 518CE126CA3515C1BC224B7FE4FD91B8B5A8439C7D635185257CA8D1FB1653DC

        // Signing Certificate Chain:
        //     Issued to: Microsoft Root Certificate Authority 2010
        //     Issued by: Microsoft Root Certificate Authority 2010
        //     Expires:   Sat Jun 23 14:04:01 2035
        //     SHA1 hash: 3B1EFD3A66EA28B16697394703A72CA340A05BD5

        //         Issued to: Microsoft Windows Production PCA 2011
        //         Issued by: Microsoft Root Certificate Authority 2010
        //         Expires:   Mon Oct 19 10:51:42 2026
        //         SHA1 hash: 580A6F4CC4E4B669B9EBDC1B2B3E087B80D0678D

        //             Issued to: Microsoft Windows
        //             Issued by: Microsoft Windows Production PCA 2011
        //             Expires:   Thu Nov 14 11:20:08 2024
        //             SHA1 hash: 71F53A26BB1625E466727183409A30D03D7923DF

        // The signature is timestamped: Tue Feb 27 10:55:18 2024
        // Timestamp Verified by:
        //     Issued to: Microsoft Root Certificate Authority 2010
        //     Issued by: Microsoft Root Certificate Authority 2010
        //     Expires:   Sat Jun 23 14:04:01 2035
        //     SHA1 hash: 3B1EFD3A66EA28B16697394703A72CA340A05BD5

        //         Issued to: Microsoft Time-Stamp PCA 2010
        //         Issued by: Microsoft Root Certificate Authority 2010
        //         Expires:   Mon Sep 30 10:32:25 2030
        //         SHA1 hash: 36056A5662DCADECF82CC14C8B80EC5E0BCC59A6

        //             Issued to: Microsoft Time-Stamp Service
        //             Issued by: Microsoft Time-Stamp PCA 2010
        //             Expires:   Fri Jan 10 11:07:09 2025
        //             SHA1 hash: 3623471965DB35A0CFC67CA20DB10E7224A31610

        // To validate that, declare our expectations in this data structure:
        private static CertValidation[] CertValidations = new CertValidation[] { 
            new CertValidation { 
                File = "Microsoft.Internal.FrameworkUdk.dll",
                IssuedToName = "Microsoft Windows",
                ExtraSignToolFlags = ""
                }
            };

        static int Main(string[] args)

        {
            return Parser.Default.ParseArguments<Options>(args)
                .MapResult(options => RunAndReturnExitCode(options),
                _ => 1);
        }

        private static int RunAndReturnExitCode(Options options)
        {
            string libDirectory = options.PackagePath + "\\lib";
            string buildType = options.BuildType;
            ValidationTestCommon.InitializeLogging(options.LogFilePath);

            // Checking experimental attributes
            string[] winmds = Directory.GetFiles(libDirectory, "*.winmd", SearchOption.AllDirectories);
            bool found = false;
            foreach (string file in winmds)
            {
                ValidationTestCommon.LogLine(file);
                found |= CheckExperimentalAttributes(file);
                ValidationTestCommon.LogLine("");
            }

            string[] dlls = Directory.GetFiles(libDirectory, "*.dll", SearchOption.AllDirectories);
            foreach (string file in dlls)
            {
                ValidationTestCommon.LogLine(file);
                found |= CheckExperimentalAttributes(file);
                ValidationTestCommon.LogLine("");
            }

            bool signError = false;
            bool isNotDeterministic = false;
            // Unpack MSIXs
            string[] curMSIX = Directory.GetFiles(options.PackagePath, "*.msix", SearchOption.AllDirectories);
            foreach (string file in curMSIX)
            {
                ValidationTestCommon.LogLine("Unpacking " + file);
                string outPath = Path.GetDirectoryName(file) + "\\" + Path.GetFileNameWithoutExtension(file);
                if (!ValidationTestCommon.AppxUnpack(options.AppxTool, file, outPath))
                {
                    Console.Error.WriteLine("Fail to unpack MSIX: " + file);
                }
            }

            winmds = Directory.GetFiles(options.PackagePath, "*.winmd", SearchOption.AllDirectories);
            foreach (string file in winmds)
            {
                ValidationTestCommon.LogLine(file);
                signError |= CheckDigitalSignature(options.SignTool, file);
                ValidationTestCommon.LogLine("");
            }

            dlls = Directory.GetFiles(options.PackagePath, "*.dll", SearchOption.AllDirectories);
            foreach (string file in dlls)
            {
                ValidationTestCommon.LogLine(file);
                signError |= CheckDigitalSignature(options.SignTool, file);
                isNotDeterministic |= !CheckDeterministicProperty(file);
                ValidationTestCommon.LogLine("");
            }

            string[] exes = Directory.GetFiles(options.PackagePath, "*.exe", SearchOption.AllDirectories);
            foreach (string file in exes)
            {
                ValidationTestCommon.LogLine(file);
                signError |= CheckDigitalSignature(options.SignTool, file);
                isNotDeterministic |= !CheckDeterministicProperty(file);
                ValidationTestCommon.LogLine("");
            }

            foreach (var validation in CertValidations)
            {
                if (validation.ValidationCount == 3) // 3 times because we are checking for amd64, x86 and arm64.
                {
                    ValidationTestCommon.LogLine($"Verified that extra cert validations for {validation.File} were processed.");
                }
                else
                {
                    ValidationTestCommon.LogLine($"ERROR: {validation.File} was validated {validation.ValidationCount} time, this is unexpected.");
                    Environment.ExitCode = 1;
                }
            }

            if (isNotDeterministic && options.CheckDeterministic)
            {
                Console.Error.WriteLine("ERROR: Non-derministic exe or dll was Found: Please see https://www.osgwiki.com/wiki/Deterministic_Compilation");
                Environment.ExitCode = 1;
            }

            if (found && !buildType.Equals("experimental"))
            {
                Console.Error.WriteLine("ERROR: Experimental Attribute Was Found");
                Environment.ExitCode = 1;
            }

            if (signError && options.CheckSigning)
            {
                Console.Error.WriteLine("ERROR: Signing errors found");
                Environment.ExitCode = 1;
            }

            return Environment.ExitCode;
        }

        private static bool CheckExperimentalAttributes(string file)
        {
            using var fs = new FileStream(file, FileMode.Open, FileAccess.Read, FileShare.ReadWrite);
            using var peReader = new PEReader(fs);

            MetadataReader metadataReader = peReader.GetMetadataReader();
            bool found = false;
            foreach (TypeDefinitionHandle typeDefH in metadataReader.TypeDefinitions)
            {
                TypeDefinition typeDef = metadataReader.GetTypeDefinition(typeDefH);

                CustomAttributeHandleCollection attributes = typeDef.GetCustomAttributes();
                foreach (CustomAttributeHandle customAttributeH in attributes)
                {
                    CustomAttribute customAttribute = metadataReader.GetCustomAttribute(customAttributeH);

                    if (IsAttributeOfType(metadataReader, customAttribute, EXPERIMENTAL_ATTRIBUTE_NAME))
                    {
                        string typeDefNameSpace = metadataReader.GetString(typeDef.Namespace);
                        string typeDefName = metadataReader.GetString(typeDef.Name);
                        ValidationTestCommon.LogLine($"Experimental Attribute found in {typeDefNameSpace}.{typeDefName}");
                        found = true;
                    }
                }
            }
            return found;
        }

        private static bool IsAttributeOfType(MetadataReader metadataReader, CustomAttribute customAttribute, string attribute)
        {
            switch (customAttribute.Constructor.Kind)
            {
                case HandleKind.MemberReference:
                    MemberReference memberReference = metadataReader.GetMemberReference((MemberReferenceHandle)customAttribute.Constructor);
                    TypeReference typeRef = metadataReader.GetTypeReference((TypeReferenceHandle)memberReference.Parent);

                    string typeRefNameSpace = metadataReader.GetString(typeRef.Namespace);
                    string typeRefName = metadataReader.GetString(typeRef.Name);
                    string typeRefType = $"{typeRefNameSpace}.{typeRefName}";
                    if (typeRefType.Equals(attribute))
                    {
                        return true;
                    }
                    return false;

                default:
                    return false;
            }
        }

        private static bool OutputContainsLine(CommandLineProcess cmd, string line)
        {
            foreach (string s in cmd.StandardOut)
            {
                if (s.Trim().Contains(line))
                {
                    return true;
                }
            }
            return false;
        }

        private static bool CheckDigitalSignature(string signtool, string file)
        {
            CertValidation extraValidation = CertValidations.Where(c => string.Equals(c.File, Path.GetFileName(file), StringComparison.OrdinalIgnoreCase)).FirstOrDefault();

            string extraOptions = extraValidation?.ExtraSignToolFlags ?? "";
            string arguments = $"verify /pa /v {extraOptions} /r \"{RootCertificate}\" \"{file}\"";
            bool hasValidDigitalSignature = false;

            try
            {
                var cmd = new CommandLineProcess(signtool, arguments);
                hasValidDigitalSignature = cmd.Run();
                if (!hasValidDigitalSignature)
                {
                    ValidationTestCommon.LogLine("ERROR: SignTool verify returned error.");
                    ValidationTestCommon.LogLine($"SignTool command line: signtool {arguments}");
                    ValidationTestCommon.LogLine("SignTool output:");
                    ValidationTestCommon.LogLine("=====================");
                    ValidationTestCommon.LogLine(string.Join("\r\n", cmd.StandardOut));
                    ValidationTestCommon.LogLine("=====================");
                }

                if (extraValidation != null)
                {
                    if (OutputContainsLine(cmd, $"Issued to: {extraValidation.IssuedToName}"))
                    {
                        ValidationTestCommon.LogLine($"Successfully validated that {file} is signed with a '{extraValidation.IssuedToName}' certificate.");
                    }
                    else
                    {
                        ValidationTestCommon.LogLine($"ERROR: {file} is not signed with a '{extraValidation.IssuedToName}' certificate.");
                        hasValidDigitalSignature = false;
                    }

                    extraValidation.ValidationCount++;
                }
            }
            catch (Exception e)
            {
                ValidationTestCommon.LogLine("ERROR: Exception in getting DigitalSignature: " + e.ToString() + " for file " + file + ".\n");
            }

            if (!hasValidDigitalSignature)
            {
                ValidationTestCommon.LogLine("Validation failed.");
            }

            return !hasValidDigitalSignature;
        }

        private static bool CheckDeterministicProperty(string file)
        {
            PEReader reader = new PEReader(File.OpenRead(file));

            foreach (DebugDirectoryEntry entry in reader.ReadDebugDirectory())
            {
                if (entry.Type == DebugDirectoryEntryType.Reproducible)
                {
                    return true;
                }
            }
            ValidationTestCommon.LogLine("File is not compiled with the deterministic build option");
            return false;
        }
    }
}
