using Microsoft.UI.Reactor;
using Microsoft.UI.Reactor.Core;
using Microsoft.UI.Reactor.Layout;
using Microsoft.UI.Xaml.Controls;
using static Microsoft.UI.Reactor.Factories;

// To learn more about Reactor, the Reactor project structure, and more about
// our project templates, see: https://github.com/microsoft/microsoft-ui-reactor
ReactorApp.Run<App>("$projectname$", width: 1000, height: 700);

enum AppRoute { Home, About, Settings }

class App : Component
{
    // The built-in Settings item is selected via the SettingsTag sentinel.
    static string RouteToTag(AppRoute route) => route switch
    {
        AppRoute.About => "about",
        AppRoute.Settings => NavigationViewElement.SettingsTag,
        _ => "home",
    };

    static AppRoute TagToRoute(string? tag) => tag switch
    {
        "about" => AppRoute.About,
        NavigationViewElement.SettingsTag => AppRoute.Settings,
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
        var (isPaneOpen, setIsPaneOpen) = UseState(true);

        var items = new[]
        {
            NavItem("Home", icon: "Home", tag: "home"),
            NavItem("About", tag: "about") with { IconElement = new FontIconData("\uEA3A") },
        };

        var titleBar = TitleBar("$projectname$")
            .Icon("ms-appx:///Assets/AppIcon.ico")
            .WithNavigation(nav)
            .PaneToggleButtonVisible(true)
            .PaneToggleRequested(() => setIsPaneOpen(!isPaneOpen))
            .Tall()
            .Flex(shrink: 0);

        var navView = (NavigationView(items, NavigationHost(nav, RouteToPage)) with
        {
            SelectedTag = RouteToTag(nav.CurrentRoute),
            OnSelectedTagChanged = tag => nav.Navigate(TagToRoute(tag)),
            IsSettingsVisible = true,
            IsBackButtonVisible = NavigationViewBackButtonVisible.Collapsed,
            IsPaneToggleButtonVisible = false,
        })
        .IsPaneOpen(isPaneOpen, setIsPaneOpen)
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
