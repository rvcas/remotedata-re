type remoteData('a, 'e) =
  | NotAsked
  | Loading
  | Failure('e)
  | Success('a);

let andMap:
  (remoteData('a, 'e), remoteData('a => 'b, 'e)) => remoteData('b, 'e);

let map: ('a => 'b, remoteData('a, 'e)) => remoteData('b, 'e);

let map2:
  (('a, 'b) => 'c, remoteData('a, 'e), remoteData('b, 'e)) =>
  remoteData('c, 'e);

let map3:
  (
    ('a, 'b, 'c) => 'd,
    remoteData('a, 'e),
    remoteData('b, 'e),
    remoteData('c, 'e)
  ) =>
  remoteData('d, 'e);

let mapError: ('e => 'f, remoteData('a, 'e)) => remoteData('a, 'f);

let mapBoth: ('a => 'b, 'e => 'f, remoteData('a, 'e)) => remoteData('b, 'f);

let andThen:
  ('a => remoteData('b, 'e), remoteData('a, 'e)) => remoteData('b, 'e);

let withDefault: ('a, remoteData('a, 'e)) => 'a;

let fromResult: Js.Result.t('a, 'e) => remoteData('a, 'e);

let toOption: remoteData('a, 'e) => option('a);

let append:
  (remoteData('a, 'e), remoteData('b, 'e)) => remoteData(('a, 'b), 'e);

let succeed: 'a => remoteData('a, 'e);

let isSuccess: remoteData('a, 'e) => bool;

let isFailure: remoteData('a, 'e) => bool;

let isLoading: remoteData('a, 'e) => bool;

let isNotAsked: remoteData('a, 'e) => bool;
