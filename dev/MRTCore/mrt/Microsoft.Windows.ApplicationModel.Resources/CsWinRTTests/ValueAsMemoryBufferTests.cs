// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License.

using System;
using Microsoft.Windows.ApplicationModel.Resources;
using WEX.TestExecution;
using WEX.TestExecution.Markup;

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

            Verify.IsTrue(BufferMarshal.TryGetDataUnsafe(reference, out IntPtr data, out uint capacity));
            Verify.AreNotEqual(IntPtr.Zero, data);
            Verify.AreEqual((uint)expected.Length, capacity);

            var bytes = new ReadOnlySpan<byte>((byte*)data, checked((int)capacity));
            Verify.IsTrue(bytes.SequenceEqual(expected));
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
                Verify.IsTrue(BufferMarshal.TryGetDataUnsafe(reference, out IntPtr data, out uint capacity));
                Verify.AreNotEqual(IntPtr.Zero, data);
                Verify.AreEqual((uint)expected.Length, capacity);

                var bytes = new ReadOnlySpan<byte>((byte*)data, checked((int)capacity));
                Verify.AreEqual(expected[0], bytes[0]);
                Verify.AreEqual(expected[expected.Length - 1], bytes[bytes.Length - 1]);
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

            Verify.IsTrue(BufferMarshal.TryGetDataUnsafe(existingReference, out IntPtr data, out uint capacity));
            Verify.AreNotEqual(IntPtr.Zero, data);
            Verify.AreEqual((uint)expected.Length, capacity);

            using var emptyReference = buffer.CreateReference();
            Verify.AreEqual(0u, emptyReference.Capacity);
            Verify.IsTrue(BufferMarshal.TryGetDataUnsafe(emptyReference, out data, out capacity));
            Verify.AreEqual(IntPtr.Zero, data);
            Verify.AreEqual(0u, capacity);
        }

        [TestMethod]
#if NET10_0_OR_GREATER
        // CsWinRT 3.0 (3.0.0-preview.261029.1) doesn't generate the event source for IMemoryBufferReference.Closed,
        // so subscribing throws TypeLoadException. Re-enable once fixed in CsWinRT.
        [TestProperty("Ignore", "True")]
#endif
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

            Verify.IsTrue(closedRaised);
            Verify.IsTrue(dataWasValidWhenClosedRaised);
            Verify.AreEqual(0u, reference.Capacity);
        }
    }
}
