type article = {
  body: string,
  id: int,
  title: string,
};

type state = {
  articles: option(list(article)),
  fetchingArticles: bool,
};

type publicAction = [ | `FetchAll];

type action = [
  publicAction
  | `FetchAllFailure
  | `FetchAllSuccess(list(article))
];

include {
          module Pair = {
            type t = {
              send: publicAction => unit,
              state,
            };
          };

          include Utils.Context.MakePair(Pair);
        };

let component = ReasonReact.reducerComponent("Articles");

let make = children => {
  ...component,
  initialState: () => {articles: None, fetchingArticles: false},
  reducer:
    Utils.Extensions.flip @@
    (
      state =>
        fun
        | `FetchAll =>
          ReasonReact.UpdateWithSideEffects(
            {...state, fetchingArticles: true},
            (
              self =>
                Js.Global.setTimeout(
                  () =>
                    self.send(
                      `FetchAllSuccess([
                        {body: "With a body", id: 1, title: "First article!"},
                        {
                          body: "With a body as well!",
                          id: 2,
                          title: "Second article!",
                        },
                      ]),
                    ),
                  1000,
                )
                |> ignore
            ),
          )
        | `FetchAllFailure =>
          ReasonReact.Update({...state, fetchingArticles: false})
        | `FetchAllSuccess(articles) =>
          ReasonReact.Update({
            articles: Some(articles),
            fetchingArticles: false,
          })
    ),
  render: ({send, state}) =>
    <Provider value={send: action => send((action :> action)), state}>
      children
    </Provider>,
};