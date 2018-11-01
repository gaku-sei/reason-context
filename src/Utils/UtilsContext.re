/* Taken from https://gist.github.com/jaredly/951177b8f5518bfbd19aa1a5ce093e7b */

type pair;

[@bs.get] external provider: pair => ReasonReact.reactClass = "Provider";
[@bs.get] external consumer: pair => ReasonReact.reactClass = "Consumer";

[@bs.module "React"] external createContext: 'a => pair = "";

module type Config = {
  type t;
  /* let defaultValue: t; */
};

module MakePair = (Config: Config) => {
  /* let pair = createContext(Config.defaultValue); */
  let pair = createContext(Js.Obj.empty());

  module Provider = {
    let make = (~value: Config.t, children) =>
      ReasonReact.wrapJsForReason(
        ~reactClass=provider(pair),
        ~props={"value": value},
        children,
      );
  };

  module Consumer = {
    let make = (children: Config.t => ReasonReact.reactElement) =>
      ReasonReact.wrapJsForReason(
        ~reactClass=consumer(pair),
        ~props=Js.Obj.empty(),
        children,
      );
  };
};