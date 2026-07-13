using Microsoft.UI.Reactor;
using Microsoft.UI.Reactor.Core;         // BackdropKind, Theme
using Microsoft.UI.Reactor.Layout;       // FlexColumn layout
using Microsoft.UI.Xaml;
using Microsoft.UI.Xaml.Controls;
using static Microsoft.UI.Reactor.Factories;

// Model-View-Update (MVU): state only ever changes by dispatching a message
// through the reducer. dispatch(message) -> Update(state, message) -> a new
// immutable state -> the view re-renders. Learn more about Reactor at:
// https://github.com/microsoft/microsoft-ui-reactor
ReactorApp.Run<App>("$projectname$", width: 900, height: 600);

// ─── Model ─── the immutable, single source of truth for the component.
record CounterState(int Count);

// ─── Messages ─── the only ways the model is allowed to change.
abstract record CounterMessage;
sealed record Increment : CounterMessage;
sealed record Decrement : CounterMessage;
sealed record ResetCount : CounterMessage;

class App : Component
{
    // ─── Update ─── a pure function: (state, message) => next state.
    static CounterState Update(CounterState state, CounterMessage message) => message switch
    {
        Increment  => state with { Count = state.Count + 1 },
        Decrement  => state with { Count = state.Count - 1 },
        ResetCount => state with { Count = 0 },
        _          => state,
    };

    public override Element Render()
    {
        // UseReducer ties the Model and Update together, handing back the current
        // state plus the `dispatch` the View uses to request changes.
        var (state, dispatch) = UseReducer<CounterState, CounterMessage>(Update, new CounterState(0));

        var titleBar = TitleBar("$projectname$")
            .Flex(shrink: 0);

        // ─── View ─── a pure projection of the current state.
        var body = Border(
            FlexColumn(
                Heading($"Count: {state.Count}"),
                Caption("State flows one way: dispatch a message, the reducer returns a new state, the view re-renders.")
                    .Foreground(Theme.SecondaryText),
                HStack(8,
                    Button("Decrement", () => dispatch(new Decrement())),
                    Button("Reset", () => dispatch(new ResetCount())),
                    Button("Increment", () => dispatch(new Increment()))
                )
            ) with { RowGap = 16 }
        ).Padding(24).Flex(grow: 1, basis: 0);

        return FlexColumn(titleBar, body)
            .Backdrop(BackdropKind.Mica);
    }
}
