using Microsoft.UI.Reactor;
using Microsoft.UI.Reactor.Core;
using Microsoft.UI.Reactor.Layout;
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using static Microsoft.UI.Reactor.Factories;

// To learn more about Reactor, the Reactor project structure, and more about
// our project templates, see: https://github.com/microsoft/microsoft-ui-reactor
ReactorApp.Run<App>("$projectname$", width: 1000, height: 700);

record CounterState(int Count);

abstract record CounterMessage;
sealed record Increment : CounterMessage;
sealed record Decrement : CounterMessage;

/// <summary>
/// Sample component using the Model-View-Update pattern. State changes only by
/// dispatching a message through <see cref="Update"/>, which returns the next
/// state and re-renders the view.
/// </summary>
class App : Component
{
    static CounterState Update(CounterState state, CounterMessage message) => message switch
    {
        Increment => state with { Count = state.Count + 1 },
        Decrement => state with { Count = state.Count - 1 },
        _         => state,
    };

    public override Element Render()
    {
        var (state, dispatch) = UseReducer<CounterState, CounterMessage>(Update, new CounterState(0));

        var titleBar = TitleBar("$projectname$")
            .Icon("ms-appx:///Assets/AppIcon.ico")
            .Flex(shrink: 0);

        var content = VStack(16,
            Title("Hello, Reactor!").HAlign(HorizontalAlignment.Center),
            HStack(8,
                Button(Icon(FontIcon("\uE710", "Segoe Fluent Icons")), () => dispatch(new Increment()))
                    .AutomationName("Increment"),
                BodyStrong($"{state.Count}")
                    .Width(40)
                    .VAlign(VerticalAlignment.Center)
                    .Set(tb => tb.TextAlignment = TextAlignment.Center),
                Button(Icon(FontIcon("\uE738", "Segoe Fluent Icons")), () => dispatch(new Decrement()))
                    .AutomationName("Decrement")
            ).HAlign(HorizontalAlignment.Center)
        ).HAlign(HorizontalAlignment.Center).VAlign(VerticalAlignment.Center);

        return FlexColumn(titleBar, Border(content).Flex(grow: 1, basis: 0))
            .Backdrop(BackdropKind.Mica);
    }
}
