// Copyright (c) Microsoft Corporation. All rights reserved.
// Licensed under the MIT License. See LICENSE in the project root for license information.

using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Linq;
using System.Runtime.InteropServices.WindowsRuntime;
using Windows.ApplicationModel;
using Windows.ApplicationModel.Activation;
using Windows.Foundation;
using Windows.Foundation.Collections;
using Microsoft.ApplicationModel.Resources;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using Microsoft.UI.Xaml.Controls.Primitives;
using Microsoft.UI.Xaml.Data;
using Microsoft.UI.Xaml.Input;
using Microsoft.UI.Xaml.Media;
using Microsoft.UI.Xaml.Navigation;
using Microsoft.UI.Xaml.Shapes;

// To learn more about WinUI, the WinUI project structure,
// and more about our project templates, see: http://aka.ms/winui-project-info.

namespace winui_desktop_packaged_app
{
    /// <summary>
    /// Provides application-specific behavior to supplement the default Application class.
    /// </summary>
    public partial class App : Application
    {
        /// <summary>
        /// Initializes the singleton application object.  This is the first line of authored code
        /// executed, and as such is the logical equivalent of main() or WinMain().
        /// </summary>
        public App()
        {
            this.InitializeComponent();
            this.Suspending += OnSuspending;
        }

        /// <summary>
        /// Invoked when the application is launched normally by the end user.  Other entry points
        /// will be used such as when the application is launched to open a specific file.
        /// </summary>
        /// <param name="args">Details about the launch request and process.</param>
        protected override void OnLaunched(Microsoft.UI.Xaml.LaunchActivatedEventArgs args)
        {
            m_resourceLoader = new ResourceLoader();
            m_resourceManager = new ResourceManager();

            // Fall back to other resource loaders if the resource is not found in MRT, in this case .net.
            // This enables carrying forward existing assets without the need to convert them.
            /*m_resourceManager.ResourceNotFound += (sender, args) =>
            {
                var candidate = new ResourceCandidate(
                    ResourceCandidateKind.String,
                    LegacyResources.ResourceManager.GetString(args.Name, LegacyResources.Culture));

                args.SetResolvedCandidate(candidate);
            };*/

            m_window = new MainWindow(m_resourceLoader, m_resourceManager);
            m_window.Activate();
        }

        /// <summary>
        /// Invoked when application execution is being suspended.  Application state is saved
        /// without knowing whether the application will be terminated or resumed with the contents
        /// of memory still intact.
        /// </summary>
        /// <param name="sender">The source of the suspend request.</param>
        /// <param name="e">Details about the suspend request.</param>
        private void OnSuspending(object sender, SuspendingEventArgs e)
        {
            // Save application state and stop any background activity
        }

        private Window m_window;

        // These do disk I/O and should be centrally cached.
        // Since both end up loading the same file, ideally an app should only use one.
        // The resource manager is a superset of the resource loader in terms of functionality.
        private ResourceLoader m_resourceLoader;
        private ResourceManager m_resourceManager;
    }
}
