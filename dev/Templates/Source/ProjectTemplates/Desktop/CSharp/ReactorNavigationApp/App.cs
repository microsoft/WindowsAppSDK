using Microsoft.UI.Reactor;
using Microsoft.UI.Reactor.Core;         // BackdropKind, Theme
using Microsoft.UI.Reactor.Layout;       // FlexColumn layout
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
            NavItem("Library", icon: "Library", tag: "library"),
            NavItem("Settings", icon: "Setting", tag: "settings"),
        };

        // Map the selected tag to the page component to show in the content area.
        Element content = selectedTag switch
        {
            "library"  => Component<LibraryPage>(),
            "settings" => Component<SettingsPage>(),
            _          => Component<HomePage>(),
        };

        return (NavigationView(items, content: content) with
        {
            SelectedTag = selectedTag,
            OnSelectedTagChanged = tag => { if (tag != null) setSelectedTag(tag); },
            PaneTitle = "$projectname$",
            // This app routes "Settings" through a normal menu item above, so the
            // built-in settings entry is turned off. Flip to true to use it.
            IsSettingsVisible = false,
        }).Backdrop(BackdropKind.Mica);
    }
}

// Each page is a plain Component — drop your own UI inside Render().
class HomePage : Component
{
    public override Element Render() =>
        Ui.Page("Home", "Welcome to your Reactor NavigationView app. Pick an item on the left to switch pages.");
}

class LibraryPage : Component
{
    public override Element Render() =>
        Ui.Page("Library", "Your content lives here. Replace this page with a list, grid, or detail view.");
}

class SettingsPage : Component
{
    public override Element Render()
    {
        // A small stateful page: toggle a setting and watch the view re-render.
        var (notify, setNotify) = UseState(true);

        return Border(
            FlexColumn(
                Heading("Settings"),
                Caption("Pages are just Components, so each one can hold its own state and hooks.")
                    .Foreground(Theme.SecondaryText),
                ToggleSwitch(notify, setNotify, header: "Send notifications")
            ) with { RowGap = 16 }
        ).Padding(32);
    }
}

static class Ui
{
    // Shared page scaffold: a heading + description inside a padded card.
    public static Element Page(string title, string description) =>
        Border(
            FlexColumn(
                Heading(title),
                Caption(description).Foreground(Theme.SecondaryText)
            ) with { RowGap = 8 }
        ).Padding(32);
}
