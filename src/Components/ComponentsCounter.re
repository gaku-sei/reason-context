open Stores;

let component = ReasonReact.statelessComponent("Counter");

let make = _children => {
  ...component,
  render: _self =>
    <Counter.Consumer>
      ...{
           ({send, state}) =>
             <div>
               <div> {state.counter->string_of_int->ReasonReact.string} </div>
               <div onClick={_ => send(`Increment)}>
                 "+"->ReasonReact.string
               </div>
               <div onClick={_ => send(`Decrement)}>
                 "-"->ReasonReact.string
               </div>
             </div>
         }
    </Counter.Consumer>,
};