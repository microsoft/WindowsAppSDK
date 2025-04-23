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
    }
}
