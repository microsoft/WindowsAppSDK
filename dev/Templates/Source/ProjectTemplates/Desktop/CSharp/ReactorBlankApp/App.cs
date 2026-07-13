using Microsoft.UI.Reactor;
using Microsoft.UI.Reactor.Core;         // BackdropKind
using Microsoft.UI.Reactor.Layout;       // FlexDirection, FlexJustify, FlexAlign
using Microsoft.UI.Xaml;                  // Thickness, HorizontalAlignment, VerticalAlignment
using Microsoft.UI.Xaml.Controls;         // Orientation, InfoBarSeverity, etc.
using static Microsoft.UI.Reactor.Factories;

// Reactor apps are pure C# — no XAML. `ReactorApp.Run` opens a single window and
// renders the root <see cref="Component"/>. To learn more about Reactor, see:
// https://github.com/microsoft/microsoft-ui-reactor
ReactorApp.Run<App>("$projectname$", width: 900, height: 600);

class App : Component
{
    public override Element Render()
    {
        var (name, setName) = UseState("World");

        var titleBar = TitleBar("$projectname$")
            .Flex(shrink: 0);

        var body = Border(
            FlexColumn(
                Heading($"Hello, {name}!"),
                TextBox(name, setName, placeholderText: "Your name")
                    .AutomationName("NameInput")
            ) with { RowGap = 16 }
        ).Padding(24).Flex(grow: 1, basis: 0);

        return FlexColumn(titleBar, body)
            .Backdrop(BackdropKind.Mica);
    }
}
