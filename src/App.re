let component = ReasonReact.statelessComponent("Counter");

let make = _children => {
  ...component,
  render: _self =>
    <div>
      <Stores.Location.Consumer>
        ...{
             ({state: {location: {hash}}}) =>
               <div> hash->ReasonReact.string </div>
           }
      </Stores.Location.Consumer>
      /* While this one actually modify the location hash */
      <Stores.Location.Consumer>
        ...{
             ({send}) =>
               <>
                 <div onClick={_ => send(`SetHash("Thank you!"))}>
                   "Click me!"->ReasonReact.string
                 </div>
                 <div onClick={_ => send(`SetHash("ohhh..."))}>
                   "And me!"->ReasonReact.string
                 </div>
               </>
           }
      </Stores.Location.Consumer>
      /* Using provider with two counter consumers */
      <Stores.Counter>
        <Components.Counter />
        <Components.Counter />
        /* Nesting providers also works, providing default values as well */
        <Stores.Counter counter=2> <Components.Counter /> </Stores.Counter>
      </Stores.Counter>
      /* Just an other counter */
      <Stores.Counter> <Components.Counter /> </Stores.Counter>
      <Components.Articles />
    </div>,
  /* This one just displays location hash */
};