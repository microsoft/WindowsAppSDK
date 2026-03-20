// Copyright (c) Microsoft Corporation and Contributors.
// Licensed under the MIT License

using System;
using Microsoft.VisualStudio;
using Microsoft.VisualStudio.Imaging;
using Microsoft.VisualStudio.Shell;
using Microsoft.VisualStudio.Shell.Interop;

#if CSHARP_EXTENSION
using Resources = WindowsAppSDK.Cs.Extension.Dev17.VSPackage;
#elif CPP_EXTENSION
using Resources = WindowsAppSDK.Cpp.Extension.Dev17.VSPackage;
#endif

namespace WindowsAppSDK.TemplateUtilities
{
    internal sealed class BuildGuard : IVsUpdateSolutionEvents2, IVsUpdateSolutionEvents4, IVsInfoBarUIEvents, IVsShellPropertyEvents, IDisposable
    {
        private IVsSolutionBuildManager2 _solutionBuildManager;
        private IVsSolutionBuildManager5 _solutionBuildManager5;
        private uint _adviseCookie;
        private uint _adviseCookie4;
        private bool _isBlocking;
        private bool _isAdvised;
        private bool _isAdvised4;
        private bool _disposed;
        private bool _infoBarShown;
        private IVsInfoBarUIElement _infoBarUIElement;
        private Func<bool> _shouldRelease;
        private string _infoBarMessage;
        private IVsShell _shell;
        private uint _shellPropertyCookie;
        private bool _isShellPropertyAdvised;
        private bool _wasJustReleased;

        public bool IsBlocking => _isBlocking;

        public void SetReleaseCondition(Func<bool> condition)
        {
            _shouldRelease = condition;
        }

        public void SetInfoBarMessage(string message)
        {
            ThreadHelper.ThrowIfNotOnUIThread();
            _infoBarMessage = message;
            if (_isBlocking)
            {
                ShowInfoBarWhenShellReady();
            }
        }

        public void DisableBuilds()
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            if (_isBlocking)
            {
                return;
            }

            _solutionBuildManager = ServiceProvider.GlobalProvider.GetService(typeof(SVsSolutionBuildManager)) as IVsSolutionBuildManager2;
            if (_solutionBuildManager == null)
            {
                System.Diagnostics.Debug.WriteLine("Warning: Could not obtain IVsSolutionBuildManager2 service.");
                return;
            }

            int hr = _solutionBuildManager.AdviseUpdateSolutionEvents(this, out _adviseCookie);
            if (hr == VSConstants.S_OK)
            {
                _isAdvised = true;
                _isBlocking = true;
                _infoBarShown = false;
            }

            _solutionBuildManager5 = _solutionBuildManager as IVsSolutionBuildManager5;
            if (_solutionBuildManager5 != null)
            {
                _solutionBuildManager5.AdviseUpdateSolutionEvents4(this, out _adviseCookie4);
                _isAdvised4 = true;
            }
        }

        public void EnableBuilds()
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            _isBlocking = false;
            _wasJustReleased = true;

            UnadviseShellPropertyChanges();

            // Don't unadvise from build events yet - we need to stay subscribed
            // so we can dismiss the info bar when the build actually starts
        }

        public int UpdateSolution_Begin(ref int pfCancelUpdate)
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            if (_wasJustReleased)
            {
                _wasJustReleased = false;
                DismissInfoBar();
                UnadviseFromBuildEvents();
                return VSConstants.S_OK;
            }

            if (_isBlocking)
            {
                if (_shouldRelease != null && _shouldRelease())
                {
                    EnableBuilds();
                    return VSConstants.S_OK;
                }

                // When Events4 is available, delay via QueryDelayFirstUpdateAction
                // instead of canceling here (canceling triggers "build errors" dialogs).
                if (!_isAdvised4)
                {
                    pfCancelUpdate = 1;
                }

                ShowInfoBar();
            }

            return VSConstants.S_OK;
        }

        private void ShowInfoBarWhenShellReady()
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            if (_shell == null)
            {
                _shell = ServiceProvider.GlobalProvider.GetService(typeof(SVsShell)) as IVsShell;
            }

            if (_shell == null)
            {
                return;
            }

            if (_shell.GetProperty((int)__VSSPROPID.VSSPROPID_Zombie, out object zombie) == VSConstants.S_OK
                && zombie is bool isZombie && !isZombie)
            {
                ShowInfoBar();
                return;
            }

            // Shell not yet initialized; defer until it is
            if (!_isShellPropertyAdvised)
            {
                _shell.AdviseShellPropertyChanges(this, out _shellPropertyCookie);
                _isShellPropertyAdvised = true;
            }
        }

        public int OnShellPropertyChange(int propid, object var)
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            if (propid == (int)__VSSPROPID.VSSPROPID_Zombie && var is bool isZombie && !isZombie)
            {
                ShowInfoBar();
                UnadviseShellPropertyChanges();
            }

            return VSConstants.S_OK;
        }

        private void UnadviseShellPropertyChanges()
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            if (_isShellPropertyAdvised && _shell != null)
            {
                _shell.UnadviseShellPropertyChanges(_shellPropertyCookie);
                _isShellPropertyAdvised = false;
            }
        }

        private void ShowInfoBar()
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            if (_infoBarShown)
            {
                return;
            }

            try
            {
                var infoBarModel = new InfoBarModel(
                    textSpans: new[]
                    {
                        new InfoBarTextSpan(_infoBarMessage ?? Resources._1055)
                    },
                    image: KnownMonikers.StatusInformation,
                    isCloseButtonVisible: true);

                IVsInfoBarUIFactory infoBarUIFactory = ServiceProvider.GlobalProvider.GetService(typeof(SVsInfoBarUIFactory)) as IVsInfoBarUIFactory;
                if (infoBarUIFactory == null)
                {
                    return;
                }

                _infoBarUIElement = infoBarUIFactory.CreateInfoBar(infoBarModel);
                if (_infoBarUIElement == null)
                {
                    return;
                }

                _infoBarUIElement.Advise(this, out _);

                IVsShell shell = _shell ?? ServiceProvider.GlobalProvider.GetService(typeof(SVsShell)) as IVsShell;
                if (shell == null)
                {
                    return;
                }

                shell.GetProperty((int)__VSSPROPID7.VSSPROPID_MainWindowInfoBarHost, out object infoBarHostObj);
                if (infoBarHostObj is IVsInfoBarHost infoBarHost)
                {
                    infoBarHost.AddInfoBar(_infoBarUIElement);
                    _infoBarShown = true;
                }
            }
            catch (Exception)
            {
                // Best-effort: if we can't show the InfoBar, the build is still canceled
            }
        }

        private void DismissInfoBar()
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            if (_infoBarUIElement != null)
            {
                _infoBarUIElement.Close();
                _infoBarUIElement = null;
            }
        }

        private void UnadviseFromBuildEvents()
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            if (_isAdvised && _solutionBuildManager != null)
            {
                _solutionBuildManager.UnadviseUpdateSolutionEvents(_adviseCookie);
                _isAdvised = false;
            }

            if (_isAdvised4 && _solutionBuildManager5 != null)
            {
                _solutionBuildManager5.UnadviseUpdateSolutionEvents4(_adviseCookie4);
                _isAdvised4 = false;
            }
        }

        public void OnActionItemClicked(IVsInfoBarUIElement infoBarUIElement, IVsInfoBarActionItem actionItem)
        {
        }

        public void OnClosed(IVsInfoBarUIElement infoBarUIElement)
        {
            _infoBarUIElement = null;
        }

        public int UpdateSolution_Done(int fSucceeded, int fModified, int fCancelCommand)
        {
            return VSConstants.S_OK;
        }

        public int UpdateSolution_StartUpdate(ref int pfCancelUpdate)
        {
            if (_isBlocking)
            {
                if (_shouldRelease != null && _shouldRelease())
                {
                    return VSConstants.S_OK;
                }

                if (!_isAdvised4)
                {
                    pfCancelUpdate = 1;
                }
            }

            return VSConstants.S_OK;
        }

        public int UpdateSolution_Cancel()
        {
            return VSConstants.S_OK;
        }

        public int OnActiveProjectCfgChange(IVsHierarchy pIVsHierarchy)
        {
            return VSConstants.S_OK;
        }

        public int UpdateProjectCfg_Begin(IVsHierarchy pHierProj, IVsCfg pCfgProj, IVsCfg pCfgSln, uint dwAction, ref int pfCancel)
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            if (_wasJustReleased)
            {
                _wasJustReleased = false;
                DismissInfoBar();
                UnadviseFromBuildEvents();
                return VSConstants.S_OK;
            }

            if (_isBlocking)
            {
                if (_shouldRelease != null && _shouldRelease())
                {
                    return VSConstants.S_OK;
                }

                if (!_isAdvised4)
                {
                    pfCancel = 1;
                }
            }

            return VSConstants.S_OK;
        }

        public int UpdateProjectCfg_Done(IVsHierarchy pHierProj, IVsCfg pCfgProj, IVsCfg pCfgSln, uint dwAction, int fSuccess, int fCancel)
        {
            return VSConstants.S_OK;
        }

        public void UpdateSolution_QueryDelayFirstUpdateAction(out int pfDelay)
        {
            ThreadHelper.ThrowIfNotOnUIThread();

            pfDelay = 0;

            if (_wasJustReleased)
            {
                _wasJustReleased = false;
                DismissInfoBar();
                UnadviseFromBuildEvents();
                return;
            }

            if (_isBlocking)
            {
                if (_shouldRelease != null && _shouldRelease())
                {
                    EnableBuilds();
                    return;
                }

                pfDelay = 1;
            }
        }

        public void UpdateSolution_BeginFirstUpdateAction()
        {
        }

        public void UpdateSolution_EndLastUpdateAction()
        {
        }

        public void UpdateSolution_BeginUpdateAction(uint dwAction)
        {
        }

        public void UpdateSolution_EndUpdateAction(uint dwAction)
        {
        }

        public void OnActiveProjectCfgChangeBatchBegin()
        {
        }

        public void OnActiveProjectCfgChangeBatchEnd()
        {
        }

        public void Dispose()
        {
            if (!_disposed)
            {
                _disposed = true;
                ThreadHelper.JoinableTaskFactory.Run(async () =>
                {
                    await ThreadHelper.JoinableTaskFactory.SwitchToMainThreadAsync();
                    _isBlocking = false;
                    _wasJustReleased = false;
                    DismissInfoBar();
                    UnadviseFromBuildEvents();
                    UnadviseShellPropertyChanges();
                });
            }
        }
    }
}
