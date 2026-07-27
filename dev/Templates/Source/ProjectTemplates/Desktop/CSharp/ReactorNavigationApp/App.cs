using Microsoft.UI.Reactor;
using Microsoft.UI.Reactor.Core;
using Microsoft.UI.Reactor.Layout;
using Microsoft.UI.Windowing;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using static Microsoft.UI.Reactor.Factories;

// To learn more about Reactor, the Reactor project structure, and more about
// our project templates, see: https://github.com/microsoft/microsoft-ui-reactor
ReactorApp.Run<App>("$projectname$", width: 1000, height: 700);

enum AppRoute { Home, About, Settings }

class App : Component
{
    // The built-in Settings item has no tag, so it maps to and from null.
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
        var navViewRef = UseRef<NavigationView?>(null);

        // The title bar hosts the back and pane toggle buttons, so give it the
        // taller layout. Reactor extends content into the title bar while
        // mounting, so apply this once that has run.
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
                // NavigationView also opens and closes the pane on its own, so
                // flip it on the control rather than tracking a separate copy.
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
            // ones NavigationView draws itself.
            var view = (NavigationView)fe;
            view.IsBackButtonVisible = NavigationViewBackButtonVisible.Collapsed;
            view.IsPaneToggleButtonVisible = false;
            navViewRef.Current = view;
        })
        .Flex(grow: 1, basis: 0);

        return FlexColumn(titleBar, navView).Backdrop(BackdropKind.Mica);
    }
}

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
    public static Element Page(string title, string body) =>
        VStack(24,
            Title(title),
            Body(body)
        ).Padding(24, 16, 24, 16);
}
