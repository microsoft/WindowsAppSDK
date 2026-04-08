// Copyright (c) Microsoft Corporation.
// Licensed under the MIT License.

using Microsoft.UI.Windowing;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using $safeprojectname$.Pages;

namespace $safeprojectname$;

public sealed partial class MainWindow : Window
{
    private int _tabCounter;

    public MainWindow()
    {
        InitializeComponent();

        // Extend content into the title bar and use the TabView's
        // drag region so the tab strip acts as the title bar area.
        ExtendsContentIntoTitleBar = true;
        SetTitleBar(CustomDragRegion);
        AppWindow.TitleBar.PreferredHeightOption = TitleBarHeightOption.Tall;
        AppWindow.SetIcon("Assets/AppIcon.ico");

        // Add a few default tabs on startup.
        AddTab("Home", typeof(HomePage));
        AddTab("About", typeof(AboutPage));
        TabControl.SelectedIndex = 0;
    }

    /// <summary>
    /// Creates a new tab with the given header and navigates it to the specified page type.
    /// </summary>
    private TabViewItem AddTab(string header, System.Type pageType)
    {
        var tab = new TabViewItem
        {
            Header = header,
            IconSource = new SymbolIconSource { Symbol = Symbol.Document }
        };

        var frame = new Frame();
        frame.Navigate(pageType);
        tab.Content = frame;

        TabControl.TabItems.Add(tab);
        return tab;
    }

    /// <summary>
    /// Called when the user clicks the "+" button to add a new tab.
    /// </summary>
    private void TabControl_AddTabButtonClick(TabView sender, object args)
    {
        _tabCounter++;
        var tab = AddTab($"New Tab {_tabCounter}", typeof(HomePage));
        sender.SelectedItem = tab;
    }

    /// <summary>
    /// Called when a tab's close button is clicked.
    /// Closes the window if the last tab is removed.
    /// </summary>
    private void TabControl_TabCloseRequested(TabView sender, TabViewTabCloseRequestedEventArgs args)
    {
        sender.TabItems.Remove(args.Tab);

        if (sender.TabItems.Count == 0)
        {
            Close();
        }
    }
}
