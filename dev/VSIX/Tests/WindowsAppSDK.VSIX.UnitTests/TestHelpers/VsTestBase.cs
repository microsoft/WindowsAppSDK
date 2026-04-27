// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

using System;
using System.Globalization;
using System.Reflection;
using System.Threading;
using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.TestTools.UnitTesting;
using Microsoft.VisualStudio.Threading;

namespace WindowsAppSDK.VSIX.UnitTests.TestHelpers
{
    /// <summary>
    /// Base class for tests that interact with VS SDK types.
    /// Configures ThreadHelper to treat the test thread as the main (UI) thread
    /// so that ThrowIfNotOnUIThread() passes, and pins the culture to en-US so
    /// resource strings and formatting are deterministic regardless of system locale.
    /// </summary>
    [TestClass]
    public abstract class VsTestBase
    {
        [TestInitialize]
        public void BaseTestInit()
        {
            // Pin culture to English so resource strings and string formatting
            // are deterministic regardless of the developer's system locale.
            Thread.CurrentThread.CurrentCulture = CultureInfo.GetCultureInfo("en-US");
            Thread.CurrentThread.CurrentUICulture = CultureInfo.GetCultureInfo("en-US");

            // Create a JoinableTaskContext with the current test thread as the main thread.
            var context = new JoinableTaskContext(
                Thread.CurrentThread,
                SynchronizationContext.Current ?? new SynchronizationContext());

            // Set ThreadHelper's cached context via reflection.
            SetThreadHelperContext(context);
        }

        [TestCleanup]
        public void BaseTestCleanup()
        {
            // Reset to avoid cross-test contamination
        }

        private static void SetThreadHelperContext(JoinableTaskContext context)
        {
            var helperType = typeof(ThreadHelper);

            // 1. Call SetUIThread() to mark the current thread as the UI thread
            var setUIThread = helperType.GetMethod("SetUIThread",
                BindingFlags.Static | BindingFlags.NonPublic | BindingFlags.Public);
            if (setUIThread is object)
            {
                setUIThread.Invoke(null, null);
            }

            // 2. Set the _joinableTaskContextCache field
            var cacheField = helperType.GetField("_joinableTaskContextCache",
                BindingFlags.Static | BindingFlags.NonPublic);
            if (cacheField is object)
            {
                cacheField.SetValue(null, context);
            }

            // 3. Also set the _generic instance's context if it exists
            var genericField = helperType.GetField("_generic",
                BindingFlags.Static | BindingFlags.NonPublic);
            if (genericField is object)
            {
                var generic = genericField.GetValue(null);
                if (generic is object)
                {
                    var genericType = generic.GetType();
                    foreach (var field in genericType.GetFields(BindingFlags.Instance | BindingFlags.NonPublic))
                    {
                        if (field.FieldType == typeof(JoinableTaskContext))
                        {
                            field.SetValue(generic, context);
                        }
                    }
                }
            }
        }
    }
}
