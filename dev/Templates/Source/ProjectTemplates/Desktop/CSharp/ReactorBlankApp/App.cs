using Microsoft.UI.Reactor;
using Microsoft.UI.Reactor.Core;         // BackdropKind
using Microsoft.UI.Reactor.Layout;       // FlexColumn layout
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using static Microsoft.UI.Reactor.Factories;

// Reactor apps are pure C# — no XAML. `ReactorApp.Run` opens a single window and
// renders the root <see cref="Component"/>. To learn more about Reactor, see:
// https://github.com/microsoft/microsoft-ui-reactor
ReactorApp.Run<App>("$projectname$", width: 1000, height: 700);

class App : Component
{
    public override Element Render()
    {
        var titleBar = TitleBar("$projectname$")
            .Icon("ms-appx:///Assets/AppIcon.ico")
            .Flex(shrink: 0);

        // This is the main content area of your application.
        // Add your UI elements here — for example, controls, layouts, and views.
        var content = Border(Empty()).Flex(grow: 1, basis: 0);

        return FlexColumn(titleBar, content)
            .Backdrop(BackdropKind.Mica);
    }
}
