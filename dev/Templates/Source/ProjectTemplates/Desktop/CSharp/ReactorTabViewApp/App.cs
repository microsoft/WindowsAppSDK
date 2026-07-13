using Microsoft.UI.Reactor;
using Microsoft.UI.Reactor.Core;         // BackdropKind, Theme
using Microsoft.UI.Reactor.Layout;       // FlexColumn layout
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using static Microsoft.UI.Reactor.Factories;

// A TabView shell hosting one component per tab. Reactor apps are pure C# —
// no XAML. Learn more at: https://github.com/microsoft/microsoft-ui-reactor
ReactorApp.Run<App>("$projectname$", width: 1000, height: 700);

class App : Component
{
    public override Element Render()
    {
        var (selectedIndex, setSelectedIndex) = UseState(0);

        var titleBar = TitleBar("$projectname$")
            .Flex(shrink: 0);

        // Each Tab hosts a component. IsClosable=false keeps these fixed; set it to
        // true (and track the tab list in state) to support user-closable tabs.
        var tabs = TabView(
            Tab("Welcome", Component<WelcomePage>()) with { IsClosable = false },
            Tab("Documents", Component<DocumentsPage>()) with { IsClosable = false },
            Tab("Settings", Component<SettingsPage>()) with { IsClosable = false }
        ) with
        {
            SelectedIndex = selectedIndex,
            OnSelectedIndexChanged = i => setSelectedIndex(i),
        };

        return FlexColumn(titleBar, tabs.Flex(grow: 1, basis: 0))
            .Backdrop(BackdropKind.Mica);
    }
}

// Each tab's content is a plain Component — drop your own UI inside Render().
class WelcomePage : Component
{
    public override Element Render() =>
        Ui.Page("Welcome", "This is your Reactor TabView app. Switch tabs above to move between views.");
}

class DocumentsPage : Component
{
    public override Element Render() =>
        Ui.Page("Documents", "Your content lives here. Replace this tab with a list, editor, or detail view.");
}

class SettingsPage : Component
{
    public override Element Render()
    {
        // A small stateful tab: toggle a setting and watch the view re-render.
        var (notify, setNotify) = UseState(true);

        return Border(
            FlexColumn(
                Heading("Settings"),
                Caption("Each tab is just a Component, so it can hold its own state and hooks.")
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
