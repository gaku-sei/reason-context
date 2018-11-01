type state = {location: ReasonReact.Router.url};

type publicAction = [ | `SetHash(string)];

type action = [ publicAction | `SetLocation(ReasonReact.Router.url)];

include {
          module Pair = {
            type t = {
              send: publicAction => unit,
              state,
            };
          };

          include Utils.Context.MakePair(Pair);
        };

let component = ReasonReact.reducerComponent("Location");

let locationToString: ReasonReact.Router.url => string =
  ({hash, path, search}) => {
    let path = path |> Belt.List.toArray |> Js.Array.joinWith("/");
    let hash = String.length(hash) > 0 ? {j|#$hash|j} : "";
    let search = String.length(search) > 0 ? {j|?$search|j} : "";

    {j|$path$search$hash|j};
  };

let make = children => {
  ...component,
  initialState: () => {
    location: ReasonReact.Router.dangerouslyGetInitialUrl(),
  },
  didMount: self => {
    let id =
      ReasonReact.Router.watchUrl(location =>
        self.send(`SetLocation(location))
      );
    self.onUnmount(() => ReasonReact.Router.unwatchUrl(id));
  },
  reducer:
    Utils.Extensions.flip @@
    (
      ({location: {hash: _hash, path, search}} as _state) =>
        fun
        | `SetHash(hash) => {
            let location: ReasonReact.Router.url = {hash, path, search};

            ReasonReact.UpdateWithSideEffects(
              {location: location},
              (_self => ReasonReact.Router.push(locationToString(location))),
            );
          }
        | `SetLocation(location) => ReasonReact.Update({location: location})
    ),
  render: ({send, state}) =>
    <Provider value={send: action => send((action :> action)), state}>
      children
    </Provider>,
};