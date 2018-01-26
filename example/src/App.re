type webData('a) = Remotedata.RemoteData.remoteData('a, string);

type repo = {
  id: int,
  name: string,
  stars: int,
  description: option(string)
};

type action =
  | ChangeUsername(string)
  | SearchEnterKeyDown
  | Loading
  | ReposLoaded(list(repo))
  | ReposError(string);

type state = {
  username: string,
  repos: webData(list(repo))
};

let component = ReasonReact.reducerComponent("App");

let make = _children => {
  let repoItems = repos =>
    repos
    |> List.map(repo =>
         <div key=(string_of_int(repo.id))>
           (ReasonReact.stringToElement(repo.name))
         </div>
       );
  let fetchRepos = ({ReasonReact.state, send}) => {
    Js.Promise.(
      Fetch.fetch(
        "https://api.github.com/users/"
        ++ state.username
        ++ "/repos?type=all&sort=updated"
      )
      |> then_(Fetch.Response.json)
      |> then_(json =>
           json
           |> Json.Decode.array(json =>
                Json.Decode.{
                  id: json |> field("id", int),
                  name: json |> field("name", string),
                  stars: json |> field("stargazers_count", int),
                  description: json |> optional(field("description", string))
                }
              )
           |> Array.to_list
           |> (
             repos => {
               send(ReposLoaded(repos));
               resolve();
             }
           )
         )
      |> ignore
    );
    send(Loading);
  };
  {
    ...component,
    initialState: () => {username: "", repos: Remotedata.RemoteData.NotAsked},
    reducer: (action, state) =>
      switch action {
      | ChangeUsername(username) => ReasonReact.Update({...state, username})
      | SearchEnterKeyDown =>
        ReasonReact.SideEffects((self => fetchRepos(self)))
      | Loading =>
        ReasonReact.Update({...state, repos: Remotedata.RemoteData.Loading})
      | ReposLoaded(repos) =>
        ReasonReact.Update({
          ...state,
          repos: Remotedata.RemoteData.Success(repos)
        })
      | ReposError(err) =>
        ReasonReact.Update({
          ...state,
          repos: Remotedata.RemoteData.Failure(err)
        })
      },
    render: ({state, send}) =>
      <div>
        <input
          placeholder="github username"
          value=state.username
          onKeyDown=(
            event =>
              if (ReactEventRe.Keyboard.keyCode(event) === 13) {
                ReactEventRe.Keyboard.preventDefault(event);
                send(SearchEnterKeyDown);
              }
          )
          onChange=(
            event =>
              send(
                ChangeUsername(
                  ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value
                )
              )
          )
        />
        (
          switch state.repos {
          | NotAsked => ReasonReact.nullElement
          | Loading => <p> (ReasonReact.stringToElement("Loading...")) </p>
          | Failure(e) => <p> (ReasonReact.stringToElement(e)) </p>
          | Success(repos) =>
            ReasonReact.arrayToElement(repos |> repoItems |> Array.of_list)
          }
        )
      </div>
  };
};
