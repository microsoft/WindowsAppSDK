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

            decimal? expected = null;

            int index = 0;
            string op = args[index++];
            if ((op.Length > 0) && (op[0] == ':'))
            {
                expected = System.Decimal.Parse(op.Substring(1));
                if (args.Length < 3)
                {
                    Help();
                }
                op = args[index++];
            }
            if (!IsValidOperator(op))
            {
                UnknownOperator($"{op}");
            }

            System.Decimal left = System.Decimal.Parse(args[index++]);
            System.Decimal? mid = null;
            System.Decimal? right = (args.Length > index ? System.Decimal.Parse(args[index++]) : null);
            if (op == "clamp")
            {
                mid = right;
                right = (args.Length > index ? System.Decimal.Parse(args[index++]) : null);
            }
            Object result = Calculate(op, left, mid, right);
            if (result == null)
            {
                Help();
            }
            if (expected != null)
            {
                if (result is decimal)
                {
                    Console.WriteLine($"==> {result} == {expected} = {expected == (decimal)result}");
                }
                else if (result is bool)
                {
                    bool dexpected = (((decimal)expected) != 0);
                    Console.WriteLine($"==> {result} == {expected} = {dexpected == (bool)result}");
                }
            }
        }

        private static Object Calculate(string op, decimal left, decimal? mid, decimal? right)
        {
            // NOTE: Decimal unary operators not supported by C#: ! ~
            // NOTE: Decimal binary operators not supported by C#: << >> >>> & | ^
            switch (op)
            {
                case "+":        { if (right == null)
                                   { var result = +left; Output($"{op}{left} = {result}"); return result; }
                                   else
                                   { var result = left + right; Output($"{left} {op} {right} = {result}"); return result; }
                                 }
                case "-":        { if (right == null)
                                   { var result = -left; Output($"{op}{left} = {result}"); return result; }
                                   else
                                   { var result = left - right; Output($"{left} {op} {right} = {result}"); return result; }
                                 }
                case "++":       { var result = ++left; Output($"{op}{left} = {result}"); return result; }
                case "--":       { var result = --left; Output($"{op}{left} = {result}"); return result; }
                case "int32":    { var result = (int)left; Output($"{op} {left} = {result}"); return result; }
                case "int64":    { var result = (long)left; Output($"{op} {left} = {result}"); return result; }
                case "uint32":   { var result = (uint)left; Output($"{op} {left} = {result}"); return result; }
                case "uint64":   { var result = (ulong)left; Output($"{op} {left} = {result}"); return result; }
                case "float":    { var result = (float)left; Output($"{op} {left} = {result}"); return result; }
                case "double":   { var result = (double)left; Output($"{op} {left} = {result}"); return result; }
                case "truncate": { var result = Math.Truncate(left); Output($"{op} {left} = {result}"); return result; }
                case "floor":    { var result = Math.Floor(left); Output($"{op} {left} = {result}"); return result; }
                case "ceiling":  { var result = Math.Ceiling(left); Output($"{op} {left} = {result}"); return result; }
                case "*":        { var result = left * right; Output($"{left} {op} {right} = {result}"); return result; }
                case "/":        { var result = left / right; Output($"{left} {op} {right} = {result}"); return result; }
                case "%":        { var result = left % right; Output($"{left} {op} {right} = {result}"); return result; }
                case "mod":      { var result = left % right; Output($"{left} {op} {right} = {result}"); return result; }
                case "==":       { var result = (left == right); Output($"{left} {op} {right} = {left == right}"); return result; }
                case "!=":       { var result = (left != right); Output($"{left} {op} {right} = {left != right}"); return result; }
                case "<":        { var result = (left < right); Output($"{left} {op} {right} = {left < right}"); return result; }
                case "<=":       { var result = (left <= right); Output($"{left} {op} {right} = {left <= right}"); return result; }
                case ">":        { var result = (left > right); Output($"{left} {op} {right} = {left > right}"); return result; }
                case ">=":       { var result = (left >= right); Output($"{left} {op} {right} = {left >= right}"); return result; }
                case "clamp":    { var result = Math.Clamp(left, (Decimal)mid, (Decimal)right); Output($"{op} {left} {mid} {right} = {result}"); return result; }
            }
            return null;
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

        private static string[] operators = new string[]{
            "+", "-", "++", "--", "int32", "int64", "uint32", "uint64", "float", "double", "truncate", "floor", "ceiling",
            "+", "-", "*", "/", "%", "mod", "==", "!=", "<", "<=", ">", ">=",
            "clamp"
        };
        private static bool IsValidOperator(string op)
        {
            foreach (string oper in operators)
            {
                if (op == oper)
                {
                    return true;
                }
            }
            return false;
        }

        private static void Help()
        {
            Console.WriteLine("Usage:  DecimalCalculator_CS.exe [:expected] <operator> <left> [[<mid>] <right>]\n" +
                              "where\n" +
                              "    operator =  unary: + - ++ -- int32 int64 uint32 uint32 float double truncate floor ceiling\n" +
                              "               binary: + - * / % mod == != < <= > >=\n" +
                              "              ternary: clamp\n" +
                              "        left = decimal value\n" +
                              "         mid = decimal value\n" +
                              "       right = decimal value\n" +
                              "    expected = extended result");
            Environment.Exit(1);
        }
    }
}
