using System;
using System.Linq;
using Microsoft.UI.Reactor;
using Microsoft.UI.Reactor.Core;
using Microsoft.UI.Reactor.Layout;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using static Microsoft.UI.Reactor.Factories;

// To learn more about Reactor, the Reactor project structure, and more about
// our project templates, see: https://github.com/microsoft/microsoft-ui-reactor
ReactorApp.Run<App>("$projectname$", width: 1000, height: 700);

record TabModel(int Id, string Title, string Page);

class App : Component
{
    public override Element Render()
    {
        var (tabs, setTabs) = UseState(UseMemo(() => new[]
        {
            new TabModel(0, "Home", "Home"),
            new TabModel(1, "About", "About"),
        }, []));
        var (selectedIndex, setSelectedIndex) = UseState(0);
        var (nextId, setNextId) = UseState(2);

        // Extend content into the title bar and use the tab strip's trailing
        // footer as the drag region, so the tab strip acts as the title bar.
        var window = UseWindow();
        var dragRef = UseRef<FrameworkElement?>(null);
        var wired = UseRef(false);
        var dpi = UseDpi();
        var (winW, winH) = UseWindowSize();
        UseEffect(() =>
        {
            if (window is not { } win || win.NativeWindow is not { } w || dragRef.Current is not { } drag)
                return;
            if (!wired.Current)
            {
                w.ExtendsContentIntoTitleBar = true;
                w.SetTitleBar(drag);
                wired.Current = true;
            }

            // RightInset is in physical pixels; convert to DIPs so the caption
            // buttons don't overlap tabs on high-DPI displays.
            drag.MinWidth = win.AppWindow.TitleBar.RightInset / (dpi / 96.0);
        }, dpi, winW, winH);

        void AddTab()
        {
            var id = nextId;
            setNextId(id + 1);
            setTabs([.. tabs, new TabModel(id, $"New Tab {id - 1}", "Home")]);
            setSelectedIndex(tabs.Length);
        }

        void CloseTab(int index)
        {
            var remaining = tabs.Where((_, i) => i != index).ToArray();
            setTabs(remaining);
            if (remaining.Length == 0)
                window?.NativeWindow?.Close();
            else if (selectedIndex >= remaining.Length)
                setSelectedIndex(remaining.Length - 1);
        }

        var tabItems = tabs
            .Select(t => Tab(t.Title, Ui.Page(t.Page, $"This is the {t.Page} page", winH)) with
            {
                Icon = "Document",
                IsClosable = true,
            })
            .ToArray();

        return (TabView(tabItems) with
        {
            SelectedIndex = Math.Min(selectedIndex, tabs.Length - 1),
            OnSelectedIndexChanged = setSelectedIndex,
            IsAddTabButtonVisible = true,
            OnAddTabButtonClick = AddTab,
            OnTabCloseRequested = CloseTab,
            TabStripHeader = Image("ms-appx:///Assets/AppIcon.ico")
                .Width(16)
                .Margin(16, 4, 12, 0)
                .VAlign(VerticalAlignment.Center)
                .AccessibilityHidden(),
            TabStripFooter = Border(Empty()).Set(b => dragRef.Current = b),
        }).Backdrop(BackdropKind.MicaAlt);
    }
}

static class Ui
{
    // The opaque background covers the window's Mica in the tab content area,
    // and the MinHeight fills it, since tab content otherwise shrinks to its text.
    public static Element Page(string title, string body, double minHeight) =>
        Border(
            VStack(24,
                Title(title),
                Body(body)
            )
        )
        .Background(Theme.Ref("SolidBackgroundFillColorTertiaryBrush"))
        .Padding(24, 16, 24, 16)
        .MinHeight(minHeight);
}
