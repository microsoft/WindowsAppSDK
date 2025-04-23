using System;
using System.Diagnostics;

namespace Test
{
    class Verify
    {
        public static bool IsTrue(bool value, string message = null)
        {
            if (value)
            {
                if (String.IsNullOrEmpty(message))
                {
                    Console.WriteLine($"Verify: IsTrue ({value})");
                }
                else
                {
                    Console.WriteLine($"ERROR: IsTrue ({value}) - {message}");
                }
            }
            else
            {
                if (String.IsNullOrEmpty(message))
                {
                    Console.WriteLine($"ERROR: IsTrue ({value})");
                }
                else
                {
                    Console.WriteLine($"ERROR: IsTrue({value}) - {message}");
                }
            }
            return value;
        }

        public static bool IsFalse(bool value, string message = null)
        {
            if (!value)
            {
                if (String.IsNullOrEmpty(message))
                {
                    Console.WriteLine($"Verify: IsFalse ({value})");
                }
                else
                {
                    Console.WriteLine($"ERROR: IsFalse ({value}) - {message}");
                }
            }
            else
            {
                if (String.IsNullOrEmpty(message))
                {
                    Console.WriteLine($"ERROR: IsFalse ({value})");
                }
                else
                {
                    Console.WriteLine($"ERROR: IsFalse ({value}) - {message}");
                }
            }
            return !value;
        }

        public static bool AreEqual<T>(T left, T right, string message = null)
        {
            var ok = left.Equals(right);
            if (ok)
            {
                Console.WriteLine($"Verify: AreEqual ({left}, {right})");
            }
            else
            {
                if (String.IsNullOrEmpty(message))
                {
                    Console.WriteLine($"ERROR: Not equal ({left}, {right})");
                }
                else
                {
                    Console.WriteLine($"ERROR: Not equal ({left}, {right}) - {message}");
                }
            }
            return ok;
        }
    }
}
