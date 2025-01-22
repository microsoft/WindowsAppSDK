using System;
using System.IO;
using System.Reflection.PortableExecutable;
using System.Reflection.Metadata;

namespace StaticValidationCommon
{
    public static class ValidationTestCommon
    {
        private static FileStream ostrm;
        private static StreamWriter writer;
        private static TextWriter ogOut = Console.Out;

        public static void InitializeLogging(string logFilePath)
        {
            try
            {
                string dir = Path.GetDirectoryName(logFilePath);
                // Determine whether the directory exists.
                if (Directory.Exists(dir))
                {
                    Console.WriteLine("That path exists already.");
                }
                else
                {
                    // Try to create the directory.
                    Directory.CreateDirectory(dir);
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("The process failed: {0}", e.ToString());
            }
            ogOut = Console.Out;
            try
            {
                ostrm = new FileStream(logFilePath, FileMode.OpenOrCreate, FileAccess.Write);
                writer = new StreamWriter(ostrm);
                AppDomain.CurrentDomain.ProcessExit += new EventHandler(ValidationTestCommon.DeinitializeLogging);
            }
            catch (Exception e)
            {
                Console.WriteLine("Cannot open " + logFilePath);
                Console.WriteLine(e.Message);
                return;
            }
        }

        public static void DeinitializeLogging(object sender, EventArgs e)
        {
            writer.Close();
            ostrm.Close();
            Console.WriteLine("Stream closed");
        }

        public static void LogLine(string log)
        {
            if (writer != null)
            {
                Console.SetOut(writer);
                System.Console.WriteLine(log);
            }

            Console.SetOut(ogOut);
            System.Console.WriteLine(log);
        }

        public static bool AppxUnpack(string appxTool, string appxFilePath, string outputDirectory)
        {
            string arguments = "unpack /o /p \"" + appxFilePath + "\" /d \"" + outputDirectory + "\"";
            bool success = false;
            try
            {
                var cmd = new CommandLineProcess(appxTool, arguments);
                success = cmd.Run();
            }
            catch (Exception e)
            {
                ValidationTestCommon.LogLine("Exception in command below: ");
                ValidationTestCommon.LogLine(appxTool + " " + arguments);
                ValidationTestCommon.LogLine(e.ToString());
            }

            return success;
        }
    }
}
