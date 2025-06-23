// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using System;
using Test;

namespace Test.DotNet
{
    class DecimalTests
    {
        public static void Run()
        {
            ctor();
            ctor_to_assign_bool();
            ctor_to_assign_int16();
            ctor_to_assign_int32();
            ctor_to_assign_int64();
            ctor_to_assign_uint8();
            ctor_to_assign_uint16();
            ctor_to_assign_uint32();
            ctor_to_assign_uint64();
            ctor_to_assign_float();
            ctor_to_assign_double();
            ctor_to_assign_string();
            compare_int16();
            compare_int32();
            compare_int64();
            compare_uint8();
            compare_uint16();
            compare_uint32();
            compare_uint64();
            compare_float();
            compare_double();
            compare_string();
            operator_neg();
            abs();
            truncate();
            floor();
            ceiling();
            clamp();
            operator_add();
            operator_sub();
            operator_mul();
            operator_div();
            operator_mod();
            round();
        }

        public static void ctor()
        {
            var dec = new Decimal();
            var data = decimal.ToInt64(dec);
            Verify.AreEqual(dec, data);
        }

        public static void ctor_to_assign_bool()
        {
            bool data = true;
            var dec = new Decimal(data ? 1 : 0);
            var to = ((int)dec == 0) ? false : true;
            Verify.AreEqual(data, to);
        }

        public static void ctor_to_assign_int16()
        {
            var data = (short)-123;
            var dec = new Decimal(data);
            var to = (short)dec;
            Verify.AreEqual(data, to);
        }

        public static void ctor_to_assign_int32()
        {
            var data = (int)-1234567890;
            var dec = new Decimal(data);
            var to = (int)dec;
            Verify.AreEqual(data, to);
        }

        public static void ctor_to_assign_int64()
        {
            var data = (long)-1234567890123456789;
            var dec = new Decimal(data);
            var to = (long)dec;
            Verify.AreEqual(data, to);
        }

        public static void ctor_to_assign_uint8()
        {
            var data = (byte)123;
            var dec = new Decimal(data);
            var to = (byte)dec;
            Verify.AreEqual(data, to);
        }

        public static void ctor_to_assign_uint16()
        {
            var data = (ushort)32109;
            var dec = new Decimal(data);
            var to = (ushort)dec;
            Verify.AreEqual(data, to);
        }

        public static void ctor_to_assign_uint32()
        {
            var data = (uint)1234567890;
            var dec = new Decimal(data);
            var to = (uint)dec;
            Verify.AreEqual(data, to);
        }

        public static void ctor_to_assign_uint64()
        {
            var data = (ulong)0xFEDCBA0987654321;
            var dec = new Decimal(data);
            var to = (ulong)dec;
            Verify.AreEqual(data, to);
        }

        public static void ctor_to_assign_float()
        {
            var data = (float)-1.25;
            var dec = new Decimal(data);
            var to = (float)dec;
            Verify.AreEqual(data, to);
        }

        public static void ctor_to_assign_double()
        {
            var data = (double)-1.25;
            var dec = new Decimal(data);
            var to = (double)dec;
            Verify.AreEqual(data, to);
        }

        public static void ctor_to_assign_string()
        {
            var data = "-12.345";
            var dec = Decimal.Parse(data);
            var to = dec.ToString();
            Verify.AreEqual(data, to);
        }

        public static void compare_int16()
        {
            var left = new Decimal((short)-32109);
            var right = new Decimal((short)32109);
            Verify.AreEqual(0, left.CompareTo(left));
            Verify.AreEqual(0, right.CompareTo(right));
            Verify.AreEqual(-1, left.CompareTo(right));
            Verify.AreEqual(1, right.CompareTo(left));

            Verify.IsTrue(left == left);
            Verify.IsFalse(left != left);
            Verify.IsFalse(left < left);
            Verify.IsTrue(left <= left);
            Verify.IsFalse(left > left);
            Verify.IsTrue(left >= left);

            Verify.IsTrue(right == right);
            Verify.IsFalse(right != right);
            Verify.IsFalse(right < right);
            Verify.IsTrue(right <= right);
            Verify.IsFalse(right > right);
            Verify.IsTrue(right >= right);

            Verify.IsFalse(left == right);
            Verify.IsTrue(left != right);
            Verify.IsTrue(left < right);
            Verify.IsTrue(left <= right);
            Verify.IsFalse(left > right);
            Verify.IsFalse(left >= right);

            Verify.IsFalse(right == left);
            Verify.IsTrue(right != left);
            Verify.IsFalse(right < left);
            Verify.IsFalse(right <= left);
            Verify.IsTrue(right > left);
            Verify.IsTrue(right >= left);
        }

        public static void compare_int32()
        {
            var left = new Decimal((int)-1234567890);
            var right = new Decimal((int)1234567890);
            Verify.AreEqual(0, left.CompareTo(left));
            Verify.AreEqual(0, right.CompareTo(right));
            Verify.AreEqual(-1, left.CompareTo(right));
            Verify.AreEqual(1, right.CompareTo(left));

            Verify.IsTrue(left == left);
            Verify.IsFalse(left != left);
            Verify.IsFalse(left < left);
            Verify.IsTrue(left <= left);
            Verify.IsFalse(left > left);
            Verify.IsTrue(left >= left);

            Verify.IsTrue(right == right);
            Verify.IsFalse(right != right);
            Verify.IsFalse(right < right);
            Verify.IsTrue(right <= right);
            Verify.IsFalse(right > right);
            Verify.IsTrue(right >= right);

            Verify.IsFalse(left == right);
            Verify.IsTrue(left != right);
            Verify.IsTrue(left < right);
            Verify.IsTrue(left <= right);
            Verify.IsFalse(left > right);
            Verify.IsFalse(left >= right);

            Verify.IsFalse(right == left);
            Verify.IsTrue(right != left);
            Verify.IsFalse(right < left);
            Verify.IsFalse(right <= left);
            Verify.IsTrue(right > left);
            Verify.IsTrue(right >= left);
        }

        public static void compare_int64()
        {
            var left = new Decimal((long)-1234567890123456789);
            var right = new Decimal((long)1234567890123456789);
            Verify.AreEqual(0, left.CompareTo(left));
            Verify.AreEqual(0, right.CompareTo(right));
            Verify.AreEqual(-1, left.CompareTo(right));
            Verify.AreEqual(1, right.CompareTo(left));

            Verify.IsTrue(left == left);
            Verify.IsFalse(left != left);
            Verify.IsFalse(left < left);
            Verify.IsTrue(left <= left);
            Verify.IsFalse(left > left);
            Verify.IsTrue(left >= left);

            Verify.IsTrue(right == right);
            Verify.IsFalse(right != right);
            Verify.IsFalse(right < right);
            Verify.IsTrue(right <= right);
            Verify.IsFalse(right > right);
            Verify.IsTrue(right >= right);

            Verify.IsFalse(left == right);
            Verify.IsTrue(left != right);
            Verify.IsTrue(left < right);
            Verify.IsTrue(left <= right);
            Verify.IsFalse(left > right);
            Verify.IsFalse(left >= right);

            Verify.IsFalse(right == left);
            Verify.IsTrue(right != left);
            Verify.IsFalse(right < left);
            Verify.IsFalse(right <= left);
            Verify.IsTrue(right > left);
            Verify.IsTrue(right >= left);
        }

        public static void compare_uint8()
        {
            var left = new Decimal((byte)123);
            var right = new Decimal((byte)234);
            Verify.AreEqual(0, left.CompareTo(left));
            Verify.AreEqual(0, right.CompareTo(right));
            Verify.AreEqual(-1, left.CompareTo(right));
            Verify.AreEqual(1, right.CompareTo(left));

            Verify.IsTrue(left == left);
            Verify.IsFalse(left != left);
            Verify.IsFalse(left < left);
            Verify.IsTrue(left <= left);
            Verify.IsFalse(left > left);
            Verify.IsTrue(left >= left);

            Verify.IsTrue(right == right);
            Verify.IsFalse(right != right);
            Verify.IsFalse(right < right);
            Verify.IsTrue(right <= right);
            Verify.IsFalse(right > right);
            Verify.IsTrue(right >= right);

            Verify.IsFalse(left == right);
            Verify.IsTrue(left != right);
            Verify.IsTrue(left < right);
            Verify.IsTrue(left <= right);
            Verify.IsFalse(left > right);
            Verify.IsFalse(left >= right);

            Verify.IsFalse(right == left);
            Verify.IsTrue(right != left);
            Verify.IsFalse(right < left);
            Verify.IsFalse(right <= left);
            Verify.IsTrue(right > left);
            Verify.IsTrue(right >= left);
        }

        public static void compare_uint16()
        {
            var left = new Decimal((ushort)32109);
            var right = new Decimal((ushort)65432);
            Verify.AreEqual(0, left.CompareTo(left));
            Verify.AreEqual(0, right.CompareTo(right));
            Verify.AreEqual(-1, left.CompareTo(right));
            Verify.AreEqual(1, right.CompareTo(left));

            Verify.IsTrue(left == left);
            Verify.IsFalse(left != left);
            Verify.IsFalse(left < left);
            Verify.IsTrue(left <= left);
            Verify.IsFalse(left > left);
            Verify.IsTrue(left >= left);

            Verify.IsTrue(right == right);
            Verify.IsFalse(right != right);
            Verify.IsFalse(right < right);
            Verify.IsTrue(right <= right);
            Verify.IsFalse(right > right);
            Verify.IsTrue(right >= right);

            Verify.IsFalse(left == right);
            Verify.IsTrue(left != right);
            Verify.IsTrue(left < right);
            Verify.IsTrue(left <= right);
            Verify.IsFalse(left > right);
            Verify.IsFalse(left >= right);

            Verify.IsFalse(right == left);
            Verify.IsTrue(right != left);
            Verify.IsFalse(right < left);
            Verify.IsFalse(right <= left);
            Verify.IsTrue(right > left);
            Verify.IsTrue(right >= left);
        }

        public static void compare_uint32()
        {
            var left = new Decimal((uint)1234567890);
            var right = new Decimal((uint)4019283756);
            Verify.AreEqual(0, left.CompareTo(left));
            Verify.AreEqual(0, right.CompareTo(right));
            Verify.AreEqual(-1, left.CompareTo(right));
            Verify.AreEqual(1, right.CompareTo(left));

            Verify.IsTrue(left == left);
            Verify.IsFalse(left != left);
            Verify.IsFalse(left < left);
            Verify.IsTrue(left <= left);
            Verify.IsFalse(left > left);
            Verify.IsTrue(left >= left);

            Verify.IsTrue(right == right);
            Verify.IsFalse(right != right);
            Verify.IsFalse(right < right);
            Verify.IsTrue(right <= right);
            Verify.IsFalse(right > right);
            Verify.IsTrue(right >= right);

            Verify.IsFalse(left == right);
            Verify.IsTrue(left != right);
            Verify.IsTrue(left < right);
            Verify.IsTrue(left <= right);
            Verify.IsFalse(left > right);
            Verify.IsFalse(left >= right);

            Verify.IsFalse(right == left);
            Verify.IsTrue(right != left);
            Verify.IsFalse(right < left);
            Verify.IsFalse(right <= left);
            Verify.IsTrue(right > left);
            Verify.IsTrue(right >= left);
        }

        public static void compare_uint64()
        {
            var left = new Decimal((ulong)0x1234567890ABCDEF);
            var right = new Decimal((ulong)0xFEDCBA0987654321);
            Verify.AreEqual(0, left.CompareTo(left));
            Verify.AreEqual(0, right.CompareTo(right));
            Verify.AreEqual(-1, left.CompareTo(right));
            Verify.AreEqual(1, right.CompareTo(left));

            Verify.IsTrue(left == left);
            Verify.IsFalse(left != left);
            Verify.IsFalse(left < left);
            Verify.IsTrue(left <= left);
            Verify.IsFalse(left > left);
            Verify.IsTrue(left >= left);

            Verify.IsTrue(right == right);
            Verify.IsFalse(right != right);
            Verify.IsFalse(right < right);
            Verify.IsTrue(right <= right);
            Verify.IsFalse(right > right);
            Verify.IsTrue(right >= right);

            Verify.IsFalse(left == right);
            Verify.IsTrue(left != right);
            Verify.IsTrue(left < right);
            Verify.IsTrue(left <= right);
            Verify.IsFalse(left > right);
            Verify.IsFalse(left >= right);

            Verify.IsFalse(right == left);
            Verify.IsTrue(right != left);
            Verify.IsFalse(right < left);
            Verify.IsFalse(right <= left);
            Verify.IsTrue(right > left);
            Verify.IsTrue(right >= left);
        }

        public static void compare_float()
        {
            var left = new Decimal((float)-1.25);
            var right = new Decimal((float)1.25);
            Verify.AreEqual(0, left.CompareTo(left));
            Verify.AreEqual(0, right.CompareTo(right));
            Verify.AreEqual(-1, left.CompareTo(right));
            Verify.AreEqual(1, right.CompareTo(left));

            Verify.IsTrue(left == left);
            Verify.IsFalse(left != left);
            Verify.IsFalse(left < left);
            Verify.IsTrue(left <= left);
            Verify.IsFalse(left > left);
            Verify.IsTrue(left >= left);

            Verify.IsTrue(right == right);
            Verify.IsFalse(right != right);
            Verify.IsFalse(right < right);
            Verify.IsTrue(right <= right);
            Verify.IsFalse(right > right);
            Verify.IsTrue(right >= right);

            Verify.IsFalse(left == right);
            Verify.IsTrue(left != right);
            Verify.IsTrue(left < right);
            Verify.IsTrue(left <= right);
            Verify.IsFalse(left > right);
            Verify.IsFalse(left >= right);

            Verify.IsFalse(right == left);
            Verify.IsTrue(right != left);
            Verify.IsFalse(right < left);
            Verify.IsFalse(right <= left);
            Verify.IsTrue(right > left);
            Verify.IsTrue(right >= left);
        }

        public static void compare_double()
        {
            var left = new Decimal((double)-1.25);
            var right = new Decimal((double)1.25);
            Verify.AreEqual(0, left.CompareTo(left));
            Verify.AreEqual(0, right.CompareTo(right));
            Verify.AreEqual(-1, left.CompareTo(right));
            Verify.AreEqual(1, right.CompareTo(left));

            Verify.IsTrue(left == left);
            Verify.IsFalse(left != left);
            Verify.IsFalse(left < left);
            Verify.IsTrue(left <= left);
            Verify.IsFalse(left > left);
            Verify.IsTrue(left >= left);

            Verify.IsTrue(right == right);
            Verify.IsFalse(right != right);
            Verify.IsFalse(right < right);
            Verify.IsTrue(right <= right);
            Verify.IsFalse(right > right);
            Verify.IsTrue(right >= right);

            Verify.IsFalse(left == right);
            Verify.IsTrue(left != right);
            Verify.IsTrue(left < right);
            Verify.IsTrue(left <= right);
            Verify.IsFalse(left > right);
            Verify.IsFalse(left >= right);

            Verify.IsFalse(right == left);
            Verify.IsTrue(right != left);
            Verify.IsFalse(right < left);
            Verify.IsFalse(right <= left);
            Verify.IsTrue(right > left);
            Verify.IsTrue(right >= left);
        }

        public static void compare_string()
        {
            var left = Decimal.Parse("-12.345");
            var right = Decimal.Parse("12.345");
            Verify.AreEqual(0, left.CompareTo(left));
            Verify.AreEqual(0, right.CompareTo(right));
            Verify.AreEqual(-1, left.CompareTo(right));
            Verify.AreEqual(1, right.CompareTo(left));

            Verify.IsTrue(left == left);
            Verify.IsFalse(left != left);
            Verify.IsFalse(left < left);
            Verify.IsTrue(left <= left);
            Verify.IsFalse(left > left);
            Verify.IsTrue(left >= left);

            Verify.IsTrue(right == right);
            Verify.IsFalse(right != right);
            Verify.IsFalse(right < right);
            Verify.IsTrue(right <= right);
            Verify.IsFalse(right > right);
            Verify.IsTrue(right >= right);

            Verify.IsFalse(left == right);
            Verify.IsTrue(left != right);
            Verify.IsTrue(left < right);
            Verify.IsTrue(left <= right);
            Verify.IsFalse(left > right);
            Verify.IsFalse(left >= right);

            Verify.IsFalse(right == left);
            Verify.IsTrue(right != left);
            Verify.IsFalse(right < left);
            Verify.IsFalse(right <= left);
            Verify.IsTrue(right > left);
            Verify.IsTrue(right >= left);
        }

        public static void operator_neg()
        {
            var zero = Decimal.Parse("0");
            var pos = Decimal.Parse("12.345");
            var neg = Decimal.Parse("-12.345");

            var zero_value = -zero;
            Verify.AreEqual(0, zero_value.CompareTo(zero));
            Verify.AreEqual(-1, zero_value.CompareTo(pos));
            Verify.AreEqual(1, zero_value.CompareTo(neg));

            var pos_value = -neg;
            Verify.AreEqual(1, pos_value.CompareTo(zero));
            Verify.AreEqual(0, pos_value.CompareTo(pos));
            Verify.AreEqual(1, pos_value.CompareTo(neg));

            var neg_value = -pos;
            Verify.AreEqual(-1, neg_value.CompareTo(zero));
            Verify.AreEqual(-1, neg_value.CompareTo(pos));
            Verify.AreEqual(0, neg_value.CompareTo(neg));
        }

        public static void abs()
        {
            var zero = Decimal.Parse("0");
            var pos = Decimal.Parse("12.345");
            var neg = Decimal.Parse("-12.345");

            var zero_value = abs(zero);
            Verify.AreEqual(0, zero_value.CompareTo(zero));
            Verify.AreEqual(-1, zero_value.CompareTo(pos));
            Verify.AreEqual(1, zero_value.CompareTo(neg));

            var pos_value = abs(pos);
            Verify.AreEqual(1, pos_value.CompareTo(zero));
            Verify.AreEqual(0, pos_value.CompareTo(pos));
            Verify.AreEqual(1, pos_value.CompareTo(neg));

            var neg_value = abs(neg);
            Verify.AreEqual(1, neg_value.CompareTo(zero));
            Verify.AreEqual(0, neg_value.CompareTo(pos));
            Verify.AreEqual(1, neg_value.CompareTo(neg));
        }

        public static void truncate()
        {
            var zero = Decimal.Parse("0");
            var zero_value = Decimal.Truncate(zero);
            Verify.AreEqual(zero, zero_value);

            var pos = Decimal.Parse("12.345");
            var pos_expected = Decimal.Parse("12");
            var pos_value = Decimal.Truncate(pos);
            Verify.AreEqual(pos_expected, pos_value);

            var neg = Decimal.Parse("-12.345");
            var neg_expected = Decimal.Parse("-12");
            var neg_value = Decimal.Truncate(neg);
            Verify.AreEqual(neg_expected, neg_value);
        }

        public static void floor()
        {
            var zero = Decimal.Parse("0");
            var zero_value = Decimal.Floor(zero);
            Verify.AreEqual(zero, zero_value);

            var pos = Decimal.Parse("12.345");
            var pos_expected = Decimal.Parse("12");
            var pos_value = Decimal.Floor(pos);
            Verify.AreEqual(pos_expected, pos_value);

            var neg = Decimal.Parse("-12.345");
            var neg_expected = Decimal.Parse("-13");
            var neg_value = Decimal.Floor(neg);
            Verify.AreEqual(neg_expected, neg_value);
        }

        public static void ceiling()
        {
            var zero = Decimal.Parse("0");
            var zero_value = Decimal.Ceiling(zero);
            Verify.AreEqual(zero, zero_value);

            var pos = Decimal.Parse("12.345");
            var pos_expected = Decimal.Parse("13");
            var pos_value = Decimal.Ceiling(pos);
            Verify.AreEqual(pos_expected, pos_value);

            var neg = Decimal.Parse("-12.345");
            var neg_expected = Decimal.Parse("-12");
            var neg_value = Decimal.Ceiling(neg);
            Verify.AreEqual(neg_expected, neg_value);
        }

        public static void clamp()
        {
            var n1 = new Decimal(1);
            var n2 = new Decimal(2);
            var n3 = new Decimal(3);

            Output(36, $"clamp {n1} {n2} {n3} = {clamp(n1,n2,n3)} vs {n2}", n2, clamp(n1,n2,n3));
            Output(36, $"clamp {n2} {n1} {n3} = {clamp(n2,n1,n3)} vs {n2}", n2, clamp(n2,n1,n3));
            Output(36, $"clamp {n3} {n1} {n2} = {clamp(n3,n1,n2)} vs {n2}", n2, clamp(n3,n1,n2));
        }

        private static Decimal clamp(Decimal value, Decimal min, Decimal max)
        {
            return value < min ? min : (value > max ? max : value);
        }

        private static void Output(int expressionLength, string expression, decimal expected, decimal result)
        {
            var pad = new string(' ', expressionLength - expression.Length);
            Console.Write($"{expression}{pad}");
            Verify.AreEqual(expected, result);
        }

        struct Values
        {
            public string left;
            public string right;
            public string result;

            public Values(string left, string right, string result)
            {
                this.left = left;
                this.right = right;
                this.result = result;
            }
        }

        public static void operator_add()
        {
            var values = new Values[]{
                new Values( "0",      "0",       "0"     ),
                new Values( "1",      "2",       "3"     ),
                new Values( "123",    "4567",    "4690"  ),
                new Values( "1",      "-2",      "-1"    ),
                new Values( "-1",     "-2",      "-3"    ),
                new Values( "-1",     "2",       "1"     ),
                new Values( "-0",     "-0",      "0"     ),
                new Values( "-0",     "0",       "0"     ),
                new Values( "0",      "-0",      "0"     ),
                new Values( "1.2",    "3.45",    "4.65"  ),
                new Values( "-1.2",   "3.45",    "2.25"  ),
                new Values( "1.2",    "-3.45",   "-2.25" ),
                new Values( "-1.2",   "-3.45",   "-4.65" ),
                new Values( ".2",     ".45",     ".65"   ),
                new Values( "-.2",    ".45",     ".25"   ),
                new Values( ".2",     "-.45",    "-.25"  ),
                new Values( "-.2",    "-.45",    "-.65"  )
            };

            foreach (var value in values)
            {
                var left = Decimal.Parse(value.left);
                var right = Decimal.Parse(value.right);
                var expected = Decimal.Parse(value.result);
                var result = left + right;
                Output(36, $"{left} + {right} = {result} vs {expected}", expected, result);

                var result2 = left;
                result2 += right;
                Output(36, $"{left} + {right} = {result} vs {expected}", expected, result);
            }
        }

        public static void operator_sub()
        {
            var values = new Values[]{
                new Values( "0",      "0",       "0"     ),
                new Values( "1",      "2",       "-1"    ),
                new Values( "123",    "4567",    "-4444" ),
                new Values( "1",      "-2",      "3"     ),
                new Values( "-1",     "-2",      "1"     ),
                new Values( "-1",     "2",       "-3"    ),
                new Values( "-0",     "-0",      "0"     ),
                new Values( "-0",     "0",       "0"     ),
                new Values( "0",      "-0",      "0"     ),
                new Values( "1.2",    "3.45",    "-2.25" ),
                new Values( "-1.2",   "3.45",    "-4.65" ),
                new Values( "1.2",    "-3.45",   "4.65"  ),
                new Values( "-1.2",   "-3.45",   "2.25"  ),
                new Values( ".2",     ".45",     "-.25"  ),
                new Values( "-.2",    ".45",     "-.65"  ),
                new Values( ".2",     "-.45",    ".65"   ),
                new Values( "-.2",    "-.45",    ".25"   )
            };

            foreach (var value in values)
            {
                var left = Decimal.Parse(value.left);
                var right = Decimal.Parse(value.right);
                var expected = Decimal.Parse(value.result);
                var result = left - right;
                Output(36, $"{left} - {right} = {result} vs {expected}", expected, result);

                var result2 = left;
                result2 -= right;
                Output(36, $"{left} - {right} = {result} vs {expected}", expected, result);
            }
        }

        public static void operator_mul()
        {
            var values = new Values[]{
                new Values( "0",      "0",       "0"      ),
                new Values( "1",      "2",       "2"      ),
                new Values( "123",    "4567",    "561741" ),
                new Values( "1",      "-2",      "-2"     ),
                new Values( "-1",     "-2",      "2"      ),
                new Values( "-1",     "2",       "-2"     ),
                new Values( "-0",     "-0",      "0"      ),
                new Values( "-0",     "0",       "0"      ),
                new Values( "0",      "-0",      "0"      ),
                new Values( "1.2",    "3.45",    "4.140"  ),
                new Values( "-1.2",   "3.45",    "-4.140" ),
                new Values( "1.2",    "-3.45",   "-4.140" ),
                new Values( "-1.2",   "-3.45",   "4.140"  ),
                new Values( ".2",     ".45",     "0.090"  ),
                new Values( "-.2",    ".45",     "-0.090" ),
                new Values( ".2",     "-.45",    "-0.090" ),
                new Values( "-.2",    "-.45",    "0.090"  )
            };

            foreach (var value in values)
            {
                var left = Decimal.Parse(value.left);
                var right = Decimal.Parse(value.right);
                var expected = Decimal.Parse(value.result);
                var result = left * right;
                Output(36, $"{left} * {right} = {result} vs {expected}", expected, result);

                var result2 = left;
                result2 *= right;
                Output(36, $"{left} * {right} = {result} vs {expected}", expected, result);
            }
        }

        public static void operator_div()
        {
            var values = new Values[]{
                new Values( "1",         "2",       "0.5"                             ),
                new Values( "123",       "4567",    "0.0269323407050580249616816291"  ),
                new Values( "1",         "-2",      "-0.5"                            ),
                new Values( "-1",        "-2",      "0.5"                             ),
                new Values( "-1",        "2",       "-0.5"                            ),
                new Values( "1.2",       "3.45",    "0.3478260869565217391304347826"  ),
                new Values( "-1.2",      "3.45",    "-0.3478260869565217391304347826" ),
                new Values( "1.2",       "-3.45",   "-0.3478260869565217391304347826" ),
                new Values( "-1.2",      "-3.45",   "0.3478260869565217391304347826"  ),
                new Values( ".2",        ".45",     "0.4444444444444444444444444444"  ),
                new Values( "-.2",       ".45",     "-0.4444444444444444444444444444" ),
                new Values( ".2",        "-.45",    "-0.4444444444444444444444444444" ),
                new Values( "-.2",       "-.45",    "0.4444444444444444444444444444"  )
            };

            foreach (var value in values)
            {
                var left = Decimal.Parse(value.left);
                var right = Decimal.Parse(value.right);
                var expected = Decimal.Parse(value.result);
                var result = left / right;
                Output(90, $"{left} / {right} = {result} vs {expected}", expected, result);

                var result2 = left;
                result2 /= right;
                Output(90, $"{left} / {right} = {result} vs {expected}", expected, result);
            }
        }

        public static void operator_mod()
        {
            var values = new Values[]{
                new Values( "1",     "2",       "1"     ),
                new Values( "123",   "4567",    "123"   ),
                new Values( "1",     "-2",      "1"     ),
                new Values( "-1",    "-2",      "-1"    ),
                new Values( "-1",    "2",       "-1"    ),
                new Values( "1.2",   "3.45",    "1.2"   ),
                new Values( "-1.2",  "3.45",    "-1.2"  ),
                new Values( "1.2",   "-3.45",   "1.2"   ),
                new Values( "-1.2",  "-3.45",   "-1.2"  ),
                new Values( ".2",    ".45",     "0.2"   ),
                new Values( "-.2",   ".45",     "-0.2"  ),
                new Values( ".2",    "-.45",    "0.2"   ),
                new Values( "-.2",   "-.45",    "-0.2"  ),

                new Values( "2",     "1",       "0"     ),
                new Values( "4567",  "123",     "16"    ),
                new Values( "3.45",  "1.2",     "1.05"  ),
                new Values( "2",     "-1",      "0"     ),
                new Values( "-2",    "1",       "0"     ),
                new Values( "-2",    "-1",      "0"     ),
                new Values( "3.45",  "-1.2",    "1.05"  ),
                new Values( "-3.45", "1.2",     "-1.05" ),
                new Values( "-3.45", "-1.2",    "-1.05" ),
                new Values( ".45",   ".2",      "0.05"  ),
                new Values( ".45",   "-.2",     "0.05"  ),
                new Values( "-.45",  ".2",      "-0.05" ),
                new Values( "-.45",  "-.2",     "-0.05" )
            };

            foreach (var value in values)
            {
                var left = Decimal.Parse(value.left);
                var right = Decimal.Parse(value.right);
                var expected = Decimal.Parse(value.result);
                var result = left % right;
                Output(36, $"{left} % {right} = {result} vs {expected}", expected, result);

                var result2 = left;
                result2 %= right;
                Output(36, $"{left} % {right} = {result} vs {expected}", expected, result);
            }
        }

        public static void round()
        {
            var n_1_888 = Decimal.Parse("1.888");
            var n_neg1_888 = Decimal.Parse("-1.888");
            var n_1_25 = Decimal.Parse("1.25");
            var n_neg1_25 = Decimal.Parse("-1.25");

            var n_2 = Decimal.Parse("2");
            var n_1_9 = Decimal.Parse("1.9");
            var n_1_89 = Decimal.Parse("1.89");
            var n_neg1_9 = Decimal.Parse("1.9");
            var n_neg1_89 = Decimal.Parse("1.89");

            var n_1_888_round_0 = Decimal.Round(n_1_888, 0);
            Output(36, $"{n_1_888}.round(0) = {n_1_888_round_0} vs {n_2}", n_2, n_1_888_round_0);

            var n_1_888_round_1 = Decimal.Round(n_1_888, 1);
            Output(36, $"${n_1_888}.round(1) = {n_1_888_round_1} vs {n_1_9}", n_1_9, n_1_888_round_1);

            var n_1_888_round_2 = Decimal.Round(n_1_888, 2);
            Output(36, $"${n_1_888}.round(2) = {n_1_888_round_2} vs {n_1_89}", n_1_89, n_1_888_round_2);

            var n_1_888_round_3 = Decimal.Round(n_1_888, 3);
            Output(36, $"${n_1_888}.round(3) = {n_1_888_round_3} vs {n_1_888}", n_1_888, n_1_888_round_3);

            var n_1_888_round_4 = Decimal.Round(n_1_888, 4);
            Output(36, $"${n_1_888}.round(4) = {n_1_888_round_4} vs {n_1_888}", n_1_888, n_1_888_round_4);
        }

        private static Decimal abs(Decimal value)
        {
            var zero = new Decimal(0);
            return value.CompareTo(zero) < 0 ? -value : value;
        }

        public static void ToDecimal()
        {
            // TODO ToDecimal tests
        }

        public static void ToDecimalValue()
        {
            // TODO ToDecimalValue tests
        }

        public static void FromDecimal()
        {
            // TODO FromDecimal tests
        }

        public static void FromDecimalValue()
        {
            // TODO FromDecimalValue tests
        }
    }
}
