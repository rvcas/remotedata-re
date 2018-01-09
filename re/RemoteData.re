type remoteData('a, 'e) =
  | NotAsked
  | Loading
  | Failure('e)
  | Success('a);

type webData('a) = remoteData('a, Js.Promise.error);

let map = (f, data) =>
  switch data {
  | Success(value) => Success(f @@ value)
  | Failure(e) => Failure(e)
  | Loading => Loading
  | NotAsked => NotAsked
  };

let succeed = a => Success(a);

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
