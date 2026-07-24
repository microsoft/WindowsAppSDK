using System;
using System.Linq;
using Microsoft.UI.Reactor;
using Microsoft.UI.Reactor.Core;         // BackdropKind
using Microsoft.UI.Reactor.Layout;       // VStack layout
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using static Microsoft.UI.Reactor.Factories;

// A TabView shell whose tabs live in the title bar (Edge/Terminal style). Tabs
// are closable and a new one is added with the "+" button. Reactor apps are
// pure C# — no XAML. Learn more at: https://github.com/microsoft/microsoft-ui-reactor
ReactorApp.Run<App>("$projectname$", width: 1000, height: 700);

// One open tab: a stable id, the header text, and which page it shows.
record TabModel(int Id, string Title, string Page);

class App : Component
{
    public override Element Render()
    {
        var (tabs, setTabs) = UseState(new[]
        {
            new TabModel(0, "Home", "Home"),
            new TabModel(1, "About", "About"),
        });
        var (selectedIndex, setSelectedIndex) = UseState(0);
        var (nextId, setNextId) = UseState(2);

        // Put the tabs up in the title bar: extend content into the caption area
        // and register the tab strip's trailing footer as the draggable region.
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
            .Select(t => Tab(t.Title, Ui.Page(t.Page, $"This is the {t.Page} page")) with
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
                .VAlign(VerticalAlignment.Center),
            TabStripFooter = Border(Empty()).Set(b => dragRef.Current = b),
        }).Backdrop(BackdropKind.MicaAlt);
    }
}

static class Ui
{
    // Shared page scaffold: a title heading + body text on a solid surface.
    // The opaque tertiary background covers the window's Mica in the tab content
    // area (matching the WinUI TabView template); the title bar / tab strip still
    // show Mica.
    public static Element Page(string title, string body) =>
        Border(
            VStack(24,
                Title(title),
                Body(body)
            )
        )
        .Background(Theme.Ref("SolidBackgroundFillColorTertiaryBrush"))
        .Padding(24, 16, 24, 16);
}
