using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Text;
using System.Threading;

namespace StaticValidationCommon
{
    public class CommandLineProcess : IDisposable
    {
        private static char[] lineSeparators = new char[] { '\n', '\r' };

        private Process process = null;
        private object runLock = new object();

        private TimeSpan timeout = TimeSpan.FromMinutes(3);
        private string[] standardOut;
        private string[] standardError;

        private string rawOut;
        private int exitCode;

        public string Command { get; set; }

        public string Arguments { get; set; }

        public string OutputAsString
        {
            get { return rawOut; }
        }
        public int ExitCode
        {
            get { return exitCode; }
        }

        public string[] StandardOut
        {
            get { return standardOut; }
        }

        public string[] StandardError
        {
            get { return standardError; }
        }

        public CommandLineProcess(string command, string arguments)
        {
            this.Command = command;
            this.Arguments = arguments;
        }

        public void StdOutputStreamThreadFunc()
        {
            string output = this.process.StandardOutput.ReadToEnd();
            if (!string.IsNullOrEmpty(output) && !string.IsNullOrEmpty(output.Trim()))
            {
                this.rawOut = output;
                this.standardOut = output.Split(CommandLineProcess.lineSeparators, StringSplitOptions.RemoveEmptyEntries);
            }
        }

        public void StdErrorStreamThreadFunc()
        {
            string output = this.process.StandardError.ReadToEnd();
            if (!string.IsNullOrEmpty(output) && !string.IsNullOrEmpty(output.Trim()))
            {
                this.standardError = output.Split(CommandLineProcess.lineSeparators, StringSplitOptions.RemoveEmptyEntries);
            }
        }

        void StartProcess()
        {
            this.process = new Process();
            this.process.StartInfo = new ProcessStartInfo(this.Command, this.Arguments);
            this.process.StartInfo.UseShellExecute = false;
            this.process.StartInfo.CreateNoWindow = true;
            this.process.StartInfo.RedirectStandardOutput = true;
            this.process.StartInfo.RedirectStandardError = true;
            this.process.Start();
        }

        public bool Run()
        {
            Thread outputStreamThread = null;
            Thread errorStreamThread = null;
            var outputStreamTimeout = TimeSpan.FromSeconds(5);
            bool succeeded = false;

            lock(this.runLock)
            {
                try
                {
                    this.StartProcess();

                    outputStreamThread = new Thread(new ThreadStart(this.StdOutputStreamThreadFunc));
                    outputStreamThread.Start();

                    errorStreamThread = new Thread(new ThreadStart(this.StdErrorStreamThreadFunc));
                    errorStreamThread.Start();

                    if (this.process.WaitForExit((int)timeout.TotalMilliseconds))
                    {
                        exitCode = this.process.ExitCode;
                        if (this.process.HasExited && this.process.ExitCode == 0)
                        {
                            succeeded = true;
                        }
                    }
                }
                finally
                {
                    if (null != outputStreamThread)
                    {
                        outputStreamThread.Join(outputStreamTimeout);
                    }
                    if (null != errorStreamThread)
                    {
                        errorStreamThread.Join(outputStreamTimeout);
                    }
                }
            }
            return succeeded;
        }

        public void Dispose()
        {
            if (process != null)
            {
                process.Dispose();
                process = null;
            }

            GC.SuppressFinalize(this);
        }
    }
}
