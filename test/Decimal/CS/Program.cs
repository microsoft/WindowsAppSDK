using System;
using Test.DotNet;
using Test.WinAppSDK;

namespace Test
{
    class DecimalTests
    {
        static void Main(string[] args)
        {
            if (args.Length == 0)
            {
                Help();
            }

            foreach (var arg in args)
            {
                if (arg.Equals("dotnet", StringComparison.OrdinalIgnoreCase))
                {
                    Test.DotNet.DecimalTests.Run();
                }
                else if (arg.Equals("winappsdk", StringComparison.OrdinalIgnoreCase))
                {
                    Test.WinAppSDK.DecimalTests.Run();
                }
                else
                {
                    Help();
                }
            }
        }

        private static void Help()
        {
            Console.WriteLine("Usage: DecimalTest_CS <test...>\n" +
                              "where\n" +
                              "    test = dotnet | winappsdk");
            Environment.Exit(1);
        }
    }
}
