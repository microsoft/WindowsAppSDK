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
            fix();
            integer();
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

        public static void fix()
        {
            var zero = Decimal.Parse("0");
            var zero_value = (long)zero;
            Verify.AreEqual(0, zero.CompareTo(zero_value));

            var pos = Decimal.Parse("12.345");
            var pos_fix = Decimal.Parse("12");
            var pos_value = (long)pos;
            Verify.AreEqual(0, pos_fix.CompareTo(pos_value));

            var neg = Decimal.Parse("-12.345");
            var neg_fix = Decimal.Parse("-12");
            var neg_value = (long)neg;
            Verify.AreEqual(0, neg_fix.CompareTo(neg_value));
        }

        public static void integer()
        {
            var zero = Decimal.Parse("0");
            var zero_value = (long)zero;
            Verify.AreEqual(0, zero.CompareTo(zero_value));

            var pos = Decimal.Parse("12.345");
            var pos_integer = Decimal.Parse("12");
            var pos_value = (long)pos;
            Verify.AreEqual(0, pos_integer.CompareTo(pos_value));

            var neg = Decimal.Parse("-12.345");
            var neg_integer = Decimal.Parse("-13");
            var neg_value = (long)neg;
            if ((neg_value < 0) && (neg_value != neg))
            {
                --neg_value;
            }
            Verify.AreEqual(0, neg_integer.CompareTo(neg_value));
        }

        public static void operator_add()
        {
            // TODO operator_add tests
        }

        public static void operator_sub()
        {
            // TODO operator_sub tests
        }

        public static void operator_mul()
        {
            // TODO operator_mul tests
        }

        public static void operator_div()
        {
            // TODO operator_div tests
        }

        public static void operator_mod()
        {
            // TODO operator_mod tests
        }

        public static void round()
        {
            // TODO round tests
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
