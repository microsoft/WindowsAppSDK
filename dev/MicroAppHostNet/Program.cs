using System;
using System.IO;
using Newtonsoft.Json.Linq;

namespace MicroAppHostNet
{
    class MicroAppHost
    {
        static void Main(string[] args)
        {
            if (args.Length < 1)
            {
                Console.WriteLine("Usage: MicroAppHost.exe <registration_json>");
                return;
            }

            // Read the contents of the JSON file into a string
            string content = File.ReadAllText(args[0]);

            // Parse the JSON string into a JToken object
            JToken jsonToken = JToken.Parse(content);

            // Print the contents of the JSON file
            Console.WriteLine(jsonToken.ToString());
        }
    }
}