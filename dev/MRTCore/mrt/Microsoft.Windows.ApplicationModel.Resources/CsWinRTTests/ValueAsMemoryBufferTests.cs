// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using System;
using System.Runtime.InteropServices.WindowsRuntime;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Microsoft.Windows.ApplicationModel.Resources;

namespace MrtCoreCsWinRTTests
{
    [TestClass]
    public class ValueAsMemoryBufferTests
    {
        [TestMethod]
        public unsafe void TryGetDataUnsafeReturnsResourceBytes()
        {
            var resourceManager = new ResourceManager("resources.pri.standalone");
            var candidate = resourceManager.MainResourceMap.GetValue("Files/Controls/AlbumBasicInfoControl.xbf");
            var expected = candidate.ValueAsBytes;

            using var buffer = candidate.ValueAsMemoryBuffer();
            using var reference = buffer.CreateReference();

            Assert.IsTrue(WindowsRuntimeMarshal.TryGetDataUnsafe(reference, out IntPtr data, out uint capacity));
            Assert.AreNotEqual(IntPtr.Zero, data);
            Assert.AreEqual((uint)expected.Length, capacity);

            var bytes = new ReadOnlySpan<byte>((byte*)data, checked((int)capacity));
            Assert.IsTrue(bytes.SequenceEqual(expected));
        }

        [TestMethod]
        public unsafe void ReferenceRetainsResourceData()
        {
            Windows.Foundation.IMemoryBufferReference reference;
            byte[] expected;

            {
                var resourceManager = new ResourceManager("resources.pri.standalone");
                var candidate = resourceManager.MainResourceMap.GetValue("Files/Controls/AlbumBasicInfoControl.xbf");
                expected = candidate.ValueAsBytes;

                using var buffer = candidate.ValueAsMemoryBuffer();
                reference = buffer.CreateReference();
            }

            GC.Collect();
            GC.WaitForPendingFinalizers();
            GC.Collect();

            using (reference)
            {
                Assert.IsTrue(WindowsRuntimeMarshal.TryGetDataUnsafe(reference, out IntPtr data, out uint capacity));
                Assert.AreNotEqual(IntPtr.Zero, data);
                Assert.AreEqual((uint)expected.Length, capacity);

                var bytes = new ReadOnlySpan<byte>((byte*)data, checked((int)capacity));
                Assert.AreEqual(expected[0], bytes[0]);
                Assert.AreEqual(expected[expected.Length - 1], bytes[bytes.Length - 1]);
            }
        }

        [TestMethod]
        public unsafe void BufferClosePreservesExistingReferenceAndReturnsEmptyNewReference()
        {
            var resourceManager = new ResourceManager("resources.pri.standalone");
            var candidate = resourceManager.MainResourceMap.GetValue("Files/Controls/AlbumBasicInfoControl.xbf");
            var expected = candidate.ValueAsBytes;

            using var buffer = candidate.ValueAsMemoryBuffer();
            using var existingReference = buffer.CreateReference();
            buffer.Dispose();

            Assert.IsTrue(WindowsRuntimeMarshal.TryGetDataUnsafe(existingReference, out IntPtr data, out uint capacity));
            Assert.AreNotEqual(IntPtr.Zero, data);
            Assert.AreEqual((uint)expected.Length, capacity);

            using var emptyReference = buffer.CreateReference();
            Assert.AreEqual(0u, emptyReference.Capacity);
            Assert.IsTrue(WindowsRuntimeMarshal.TryGetDataUnsafe(emptyReference, out data, out capacity));
            Assert.AreEqual(IntPtr.Zero, data);
            Assert.AreEqual(0u, capacity);
        }

        [TestMethod]
        public void ReferenceCloseRaisesClosedBeforeInvalidatingData()
        {
            var resourceManager = new ResourceManager("resources.pri.standalone");
            var candidate = resourceManager.MainResourceMap.GetValue("Files/Controls/AlbumBasicInfoControl.xbf");

            using var buffer = candidate.ValueAsMemoryBuffer();
            var reference = buffer.CreateReference();
            var capacityBeforeClose = reference.Capacity;
            var closedRaised = false;
            var dataWasValidWhenClosedRaised = false;

            reference.Closed += (sender, args) =>
            {
                closedRaised = true;
                dataWasValidWhenClosedRaised = sender.Capacity == capacityBeforeClose;
            };

            reference.Dispose();

            Assert.IsTrue(closedRaised);
            Assert.IsTrue(dataWasValidWhenClosedRaised);
            Assert.AreEqual(0u, reference.Capacity);
        }
    }
}
