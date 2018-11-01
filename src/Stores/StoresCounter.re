type state = {counter: int};

type publicAction = [ | `Increment | `Decrement];

type action = [ publicAction];

include {
          module Pair = {
            type t = {
              send: publicAction => unit,
              state,
            };
          };

          include Utils.Context.MakePair(Pair);
        };

let component = ReasonReact.reducerComponent("Counter");

let make = (~counter=0, children) => {
  ...component,
  initialState: () => {counter: counter},
  reducer:
    Utils.Extensions.flip @@
    (
      state =>
        fun
        | `Increment => ReasonReact.Update({counter: state.counter + 1})
        | `Decrement => ReasonReact.Update({counter: state.counter - 1})
    ),
  render: ({send, state}) =>
    <Provider value={send, state}> children </Provider>,
};