using Microsoft.UI.Reactor;
using Microsoft.UI.Reactor.Core;         // BackdropKind, FontIconData
using Microsoft.UI.Reactor.Layout;       // VStack layout
using Microsoft.UI.Windowing;            // TitleBarHeightOption
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using static Microsoft.UI.Reactor.Factories;

// A NavigationView shell whose back button and pane toggle live in the title bar.
// Reactor apps are pure C# — no XAML. Learn more at:
// https://github.com/microsoft/microsoft-ui-reactor
ReactorApp.Run<App>("$projectname$", width: 1000, height: 700);

// The pages this app can show. Reactor's navigation handle keeps the back stack.
enum AppRoute { Home, About, Settings }

class App : Component
{
    // The built-in Settings item has no tag, so it maps to/from null.
    static string? RouteToTag(AppRoute route) => route switch
    {
        AppRoute.About => "about",
        AppRoute.Settings => null,
        _ => "home",
    };

    static AppRoute TagToRoute(string? tag) => tag switch
    {
        "about" => AppRoute.About,
        null => AppRoute.Settings,
        _ => AppRoute.Home,
    };

    static Element RouteToPage(AppRoute route) => route switch
    {
        AppRoute.About => Component<AboutPage>(),
        AppRoute.Settings => Component<SettingsPage>(),
        _ => Component<HomePage>(),
    };

    public override Element Render()
    {
        var nav = UseNavigation(AppRoute.Home);
        var navViewRef = UseRef<Microsoft.UI.Xaml.Controls.NavigationView?>(null);

        // The title bar hosts the back and pane toggle buttons, so give it the
        // taller title bar layout the WinUI template uses. Reactor extends content
        // into the title bar while mounting, so apply this once that has run.
        var window = UseWindow();
        UseEffect(() =>
        {
            if (window is not { } win)
                return;
            win.NativeWindow?.DispatcherQueue.TryEnqueue(() =>
                win.AppWindow.TitleBar.PreferredHeightOption = TitleBarHeightOption.Tall);
        });

        var items = new[]
        {
            NavItem("Home", icon: "Home", tag: "home"),
            NavItem("About", tag: "about") with { IconElement = new FontIconData("\uEA3A", "Segoe Fluent Icons") },
        };

        var titleBar = TitleBar("$projectname$")
            .Icon("ms-appx:///Assets/AppIcon.ico")
            .WithNavigation(nav)
            .PaneToggleButtonVisible(true)
            .PaneToggleRequested(() =>
            {
                // Flip the pane on the control itself: NavigationView also opens and
                // closes it on its own (light dismiss, display mode changes), so a
                // separate state copy would drift out of sync.
                if (navViewRef.Current is { } view)
                    view.IsPaneOpen = !view.IsPaneOpen;
            })
            .Height(48)
            .Flex(shrink: 0);

        var navView = (NavigationView(items, NavigationHost(nav, RouteToPage)) with
        {
            SelectedTag = RouteToTag(nav.CurrentRoute),
            OnSelectedTagChanged = tag => nav.Navigate(TagToRoute(tag)),
            IsSettingsVisible = true,
        })
        .OnMount(fe =>
        {
            // The title bar owns the back and pane toggle buttons, so hide the
            // ones NavigationView draws itself (matching the WinUI template).
            var view = (Microsoft.UI.Xaml.Controls.NavigationView)fe;
            view.IsBackButtonVisible = NavigationViewBackButtonVisible.Collapsed;
            view.IsPaneToggleButtonVisible = false;
            navViewRef.Current = view;
        })
        .Flex(grow: 1, basis: 0);

        return FlexColumn(titleBar, navView).Backdrop(BackdropKind.Mica);
    }
}

// Each page is a plain Component — drop your own UI inside Render().
class HomePage : Component
{
    public override Element Render() => Ui.Page("Home", "This is the Home page");
}

class AboutPage : Component
{
    public override Element Render() => Ui.Page("About", "This is the About page");
}

class SettingsPage : Component
{
    public override Element Render() => Ui.Page("Settings", "This is the Settings page");
}

static class Ui
{
    // Shared page scaffold: a title heading + body text.
    public static Element Page(string title, string body) =>
        VStack(24,
            Title(title),
            Body(body)
        ).Padding(24, 16, 24, 16);
}
