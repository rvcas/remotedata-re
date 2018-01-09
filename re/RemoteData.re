type remoteData('e, 'a) =
  | NotAsked
  | Loading
  | Failure('e)
  | Success('a);
