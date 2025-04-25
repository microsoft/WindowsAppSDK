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

            string op = args[0];
            Decimal left = Decimal.Parse(args[1]);
            Decimal right = (args.Length >= 3 ? Decimal.Parse(args[2]) : new Decimal(0));
            string expected = (args.Length >= 4 ? args[3] : null);
            Decimal result = new Decimal(0);
            if (args.Length == 3)
            {
                // NOTE: Decimal unary operators not supported by C#: ! ~
                switch (op)
                {
                    case "+":      result = +left; Console.Write($"{op}{left} = {result}"); break;
                    case "-":      result = -left; Console.Write($"{op}{left} = {result}"); break;
                    case "++":     result = ++left; Console.Write($"{op}{left} = {result}"); break;
                    case "--":     result = --left; Console.Write($"{op}{left} = {result}"); break;
                    case "int32":  expected = null; Console.WriteLine($"{op} {left} = {(int)left}"); break;
                    case "int64":  expected = null; Console.WriteLine($"{op} {left} = {(long)left}"); break;
                    case "uint32": expected = null; Console.WriteLine($"{op} {left} = {(uint)left}"); break;
                    case "uint64": expected = null; Console.WriteLine($"{op} {left} = {(ulong)left}"); break;
                    case "float":  expected = null; Console.WriteLine($"{op} {left} = {(float)left}"); break;
                    case "double": expected = null; Console.WriteLine($"{op} {left} = {(double)left}"); break;
                    default:   UnknownOperator($"{op} {left}"); break;
                }
            }
            else if (args.Length == 4)
            {
                // NOTE: Decimal unary operators not supported by C#: << >> >>> & | ^
                switch (op)
                {
                    case "+":   result = left + right; Console.Write($"{left} {op} {right} = {result}"); break;
                    case "-":   result = left - right; Console.Write($"{left} {op} {right} = {result}"); break;
                    case "*":   result = left * right; Console.Write($"{left} {op} {right} = {result}"); break;
                    case "/":   result = left / right; Console.Write($"{left} {op} {right} = {result}"); break;
                    case "%":   result = left % right; Console.Write($"{left} {op} {right} = {result}"); break;
                    case "mod": result = left % right; Console.Write($"{left} {op} {right} = {result}"); break;
                    case "==":  expected = null; Console.WriteLine($"{left} {op} {right} = {left == right}"); break;
                    case "!=":  expected = null; Console.WriteLine($"{left} {op} {right} = {left != right}"); break;
                    case "<":   expected = null; Console.WriteLine($"{left} {op} {right} = {left < right}"); break;
                    case "<=":  expected = null; Console.WriteLine($"{left} {op} {right} = {left <= right}"); break;
                    case ">":   expected = null; Console.WriteLine($"{left} {op} {right} = {left > right}"); break;
                    case ">=":  expected = null; Console.WriteLine($"{left} {op} {right} = {left >= right}"); break;
                    default:    UnknownOperator($"{op} {left} {right}"); break;
                }
            }
            else
            {
                Help();
            }
            if (expected != null)
            {
                Decimal expectedValue = Decimal.Parse(expected);
                Console.WriteLine($"\t\t    ==> {result} == {expectedValue} = {expectedValue == result}");
            }
        }

        private static void UnknownOperator(string message)
        {
            Console.WriteLine($"ERROR: Unknown operator {message}");
            Environment.Exit(2);
        }

        private static void Help()
        {
            Console.WriteLine("Usage:  DecimalCalculator_CS.exe <operator> <left> [<right>]\n" +
                              "where\n" +
                              "    operator =  unary: + - ++ -- int32 int64 uint32 uint32 float double\n" +
                              "               binary: + - * / % mod == != < <= > >=\n" +
                              "        left = decimal value\n" +
                              "       right = decimal value");
            Environment.Exit(1);
        }
    }
}
