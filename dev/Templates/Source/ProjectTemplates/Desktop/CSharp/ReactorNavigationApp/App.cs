using Microsoft.UI.Reactor;
using Microsoft.UI.Reactor.Core;         // BackdropKind, FontIconData
using Microsoft.UI.Reactor.Layout;       // VStack layout
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using static Microsoft.UI.Reactor.Factories;

// A NavigationView shell that swaps a page component in as the selection changes.
// Reactor apps are pure C# — no XAML. Learn more at:
// https://github.com/microsoft/microsoft-ui-reactor
ReactorApp.Run<App>("$projectname$", width: 1000, height: 700);

class App : Component
{
    public override Element Render()
    {
        var (selectedTag, setSelectedTag) = UseState("home");

        var items = new[]
        {
            NavItem("Home", icon: "Home", tag: "home"),
            NavItem("About", tag: "about") with { IconElement = new FontIconData("\uEA3A", "Segoe Fluent Icons") },
        };

        // Map the selected tag to the page component to show in the content area.
        // The built-in Settings item reports a null tag when selected.
        Element content = selectedTag switch
        {
            "about"    => Component<AboutPage>(),
            "settings" => Component<SettingsPage>(),
            _          => Component<HomePage>(),
        };

        var titleBar = TitleBar("$projectname$")
            .Icon("ms-appx:///Assets/AppIcon.ico")
            .Flex(shrink: 0);

        var nav = (NavigationView(items, content: content) with
        {
            SelectedTag = selectedTag,
            OnSelectedTagChanged = tag => setSelectedTag(tag ?? "settings"),
            IsSettingsVisible = true,
        }).Flex(grow: 1, basis: 0);

        return FlexColumn(titleBar, nav).Backdrop(BackdropKind.Mica);
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
