type remoteData('a, 'e) =
  | NotAsked
  | Loading
  | Failure('e)
  | Success('a);

/* Error should probably be something else */
type webData('a) = remoteData('a, Js.Promise.error);

let succeed = a => Success(a);

let andMap = (wrappedValue, wrappedFunction) =>
  switch (wrappedFunction, wrappedValue) {
  | (Success(f), Success(value)) => Success(f @@ value)
  | (Failure(error), _) => Failure(error)
  | (_, Failure(error)) => Failure(error)
  | (Loading, _) => Loading
  | (_, Loading) => Loading
  | (NotAsked, _) => NotAsked
  | (_, NotAsked) => NotAsked
  };

let map = (f, data) =>
  switch data {
  | Success(value) => Success(f @@ value)
  | Failure(e) => Failure(e)
  | Loading => Loading
  | NotAsked => NotAsked
  };

let map2 = (f, a, b) => map(f, a) |> andMap(b);

let map3 = (f, a, b, c) => map(f, a) |> andMap(b) |> andMap(c);

let mapError = (f, data) =>
  switch data {
  | Success(x) => Success(x)
  | Failure(e) => Failure(f @@ e)
  | Loading => Loading
  | NotAsked => NotAsked
  };

let withDefault = (default, data) =>
  switch data {
  | Success(x) => x
  | _ => default
  };

let isSuccess = data =>
  switch data {
  | Success(_a) => true
  | _ => false
  };

let isFailure = data =>
  switch data {
  | Failure(_e) => true
  | _ => false
  };

let isLoading = data =>
  switch data {
  | Loading => true
  | _ => false
  };

let isNotAsked = data =>
  switch data {
  | NotAsked => true
  | _ => false
  };
