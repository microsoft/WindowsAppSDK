// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using System;

namespace Microsoft.Windows.Foundation
{
    class DecimalCalculator
    {
        public static void Main(string[] args)
        {
            if (args.Length < 2)
            {
                Help();
            }

            int index = 0;
            string op = args[index++];
            System.Decimal left = System.Decimal.Parse(args[index++]);
            System.Decimal mid = new System.Decimal(0);
            System.Decimal right = (args.Length > index ? System.Decimal.Parse(args[index++]) : new System.Decimal(0));
            if (op == "clamp")
            {
                mid = right;
                right = (args.Length > index ? System.Decimal.Parse(args[index++]) : new System.Decimal(0));
            }
            string expected = (args.Length > index ? args[index++] : null);
            System.Decimal result = new System.Decimal(0);
            if (args.Length == 3)
            {
                // NOTE: Decimal unary operators not supported by C#: ! ~
                switch (op)
                {
                    case "+":        result = +left; Output($"{op}{left} = {result}"); break;
                    case "-":        result = -left; Output($"{op}{left} = {result}"); break;
                    case "++":       result = ++left; Output($"{op}{left} = {result}"); break;
                    case "--":       result = --left; Output($"{op}{left} = {result}"); break;
                    case "int32":    expected = null; Console.WriteLine($"{op} {left} = {(int)left}"); break;
                    case "int64":    expected = null; Console.WriteLine($"{op} {left} = {(long)left}"); break;
                    case "uint32":   expected = null; Console.WriteLine($"{op} {left} = {(uint)left}"); break;
                    case "uint64":   expected = null; Console.WriteLine($"{op} {left} = {(ulong)left}"); break;
                    case "float":    expected = null; Console.WriteLine($"{op} {left} = {(float)left}"); break;
                    case "double":   expected = null; Console.WriteLine($"{op} {left} = {(double)left}"); break;
                    case "truncate": expected = null; Console.WriteLine($"{op} {left} = {Math.Truncate(left)}"); break;
                    case "floor":    expected = null; Console.WriteLine($"{op} {left} = {Math.Floor(left)}"); break;
                    case "ceiling":  expected = null; Console.WriteLine($"{op} {left} = {Math.Ceiling(left)}"); break;
                    default:   UnknownOperator($"{op} {left}"); break;
                }
            }
            else if (args.Length == 4)
            {
                // NOTE: Decimal binary operators not supported by C#: << >> >>> & | ^
                switch (op)
                {
                    case "+":   result = left + right; Output($"{left} {op} {right} = {result}"); break;
                    case "-":   result = left - right; Output($"{left} {op} {right} = {result}"); break;
                    case "*":   result = left * right; Output($"{left} {op} {right} = {result}"); break;
                    case "/":   result = left / right; Output($"{left} {op} {right} = {result}"); break;
                    case "%":   result = left % right; Output($"{left} {op} {right} = {result}"); break;
                    case "mod": result = left % right; Output($"{left} {op} {right} = {result}"); break;
                    case "==":  expected = null; Console.WriteLine($"{left} {op} {right} = {left == right}"); break;
                    case "!=":  expected = null; Console.WriteLine($"{left} {op} {right} = {left != right}"); break;
                    case "<":   expected = null; Console.WriteLine($"{left} {op} {right} = {left < right}"); break;
                    case "<=":  expected = null; Console.WriteLine($"{left} {op} {right} = {left <= right}"); break;
                    case ">":   expected = null; Console.WriteLine($"{left} {op} {right} = {left > right}"); break;
                    case ">=":  expected = null; Console.WriteLine($"{left} {op} {right} = {left >= right}"); break;
                    default:    UnknownOperator($"{op} {left} {right}"); break;
                }
            }
            else if (args.Length == 5)
            {
                switch (op)
                {
                    case "clamp":  expected = null; Console.WriteLine($"{op} {left} {mid} {right} = {Math.Clamp(left, mid, right)}"); break;
                    default:    UnknownOperator($"{op} {left} {mid} {right}"); break;
                }
            }
            else
            {
                Help();
            }
            if (expected != null)
            {
                System.Decimal expectedValue = System.Decimal.Parse(expected);
                Console.WriteLine($"==> {result} == {expectedValue} = {expectedValue == result}");
            }
        }

        private static void Output(string evaluation)
        {
            Console.Write($"{evaluation,-32}");
        }

        private static void UnknownOperator(string message)
        {
            Console.WriteLine($"ERROR: Unknown operator {message}");
            Environment.Exit(2);
        }

        private static void Help()
        {
            Console.WriteLine("Usage:  DecimalCalculator_CS.exe <operator> <left> [[<mid>] <right>]\n" +
                              "where\n" +
                              "    operator =  unary: + - ++ -- int32 int64 uint32 uint32 float double truncate floor ceiling\n" +
                              "               binary: + - * / % mod == != < <= > >=\n" +
                              "              ternary: clamp\n" +
                              "        left = decimal value\n" +
                              "         mid = decimal value\n" +
                              "       right = decimal value");
            Environment.Exit(1);
        }
    }
}
