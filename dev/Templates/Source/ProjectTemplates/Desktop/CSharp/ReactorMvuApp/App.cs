using Microsoft.UI.Reactor;
using Microsoft.UI.Reactor.Core;         // BackdropKind
using Microsoft.UI.Reactor.Layout;       // VStack / HStack layout
using Microsoft.UI.Xaml;                  // HorizontalAlignment, VerticalAlignment, TextAlignment
using Microsoft.UI.Xaml.Controls;
using static Microsoft.UI.Reactor.Factories;

// Model-View-Update (MVU): state only ever changes by dispatching a message
// through the reducer. dispatch(message) -> Update(state, message) -> a new
// immutable state -> the view re-renders. Learn more about Reactor at:
// https://github.com/microsoft/microsoft-ui-reactor
ReactorApp.Run<App>("$projectname$", width: 1000, height: 700);

// ─── Model ─── the immutable, single source of truth for the component.
record CounterState(int Count);

// ─── Messages ─── the only ways the model is allowed to change.
abstract record CounterMessage;
sealed record Increment : CounterMessage;
sealed record Decrement : CounterMessage;

class App : Component
{
    // ─── Update ─── a pure function: (state, message) => next state.
    static CounterState Update(CounterState state, CounterMessage message) => message switch
    {
        Increment => state with { Count = state.Count + 1 },
        Decrement => state with { Count = state.Count - 1 },
        _         => state,
    };

    public override Element Render()
    {
        // UseReducer ties the Model and Update together, handing back the current
        // state plus the `dispatch` the View uses to request changes.
        var (state, dispatch) = UseReducer<CounterState, CounterMessage>(Update, new CounterState(0));

        var titleBar = TitleBar("$projectname$")
            .Icon("ms-appx:///Assets/AppIcon.ico")
            .Flex(shrink: 0);

        // ─── View ─── a pure projection of the current state, centered in the window.
        var content = VStack(16,
            Heading("Hello, WinUI!").HAlign(HorizontalAlignment.Center),
            HStack(8,
                Button(Icon(FontIcon("\uE710", "Segoe Fluent Icons")), () => dispatch(new Increment())),
                TextBlock($"{state.Count}")
                    .SemiBold()
                    .Width(40)
                    .VAlign(VerticalAlignment.Center)
                    .Set(tb => tb.TextAlignment = TextAlignment.Center),
                Button(Icon(FontIcon("\uE738", "Segoe Fluent Icons")), () => dispatch(new Decrement()))
            ).HAlign(HorizontalAlignment.Center)
        ).HAlign(HorizontalAlignment.Center).VAlign(VerticalAlignment.Center);

        return FlexColumn(titleBar, Border(content).Flex(grow: 1, basis: 0))
            .Backdrop(BackdropKind.Mica);
    }
}
