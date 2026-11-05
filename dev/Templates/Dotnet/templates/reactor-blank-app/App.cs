using Microsoft.UI.Reactor;
using Microsoft.UI.Reactor.Core;
using Microsoft.UI.Reactor.Layout;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using static Microsoft.UI.Reactor.Factories;

// To learn more about Reactor, the Reactor project structure, and more about
// our project templates, see: https://github.com/microsoft/microsoft-ui-reactor
ReactorApp.Run<App>("$projectname$");

class App : Component
{
    public override Element Render()
    {
        var titleBar = TitleBar("$projectname$")
            .Flex(shrink: 0);

        // This is the main content area of your application.
        // Add your UI elements here.
        var content = Border(Empty()).Flex(grow: 1, basis: 0);

        return FlexColumn(titleBar, content)
            .Backdrop(BackdropKind.Mica);
    }
}
