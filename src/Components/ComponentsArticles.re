let component = ReasonReact.statelessComponent("Articles");

let make = _children => {
  ...component,
  render: _self =>
    <Stores.Articles.Consumer>
      ...{
           ({send, state: {articles, fetchingArticles}}) =>
             switch (articles) {
             | Some(articles) =>
               articles
               |> List.map(({Stores.Articles.title}) =>
                    <div> title->ReasonReact.string </div>
                  )
               |> Belt.List.toArray
               |> ReasonReact.array
             | None =>
               <div>
                 <div>
                   {j|Is fetching: $fetchingArticles|j}->ReasonReact.string
                 </div>
                 <div onClick=(_ => send(`FetchAll))>
                   "Click on me!"->ReasonReact.string
                 </div>
               </div>
             }
         }
    </Stores.Articles.Consumer>,
};