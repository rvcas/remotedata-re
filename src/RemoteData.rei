type t('a, 'e) =
  | NotAsked
  | Loading
  | Failure('e)
  | Success('a);

let andMap: (t('a, 'e), t('a => 'b, 'e)) => t('b, 'e);

let map: ('a => 'b, t('a, 'e)) => t('b, 'e);

let map2: (('a, 'b) => 'c, t('a, 'e), t('b, 'e)) => t('c, 'e);

let map3: (('a, 'b, 'c) => 'd, t('a, 'e), t('b, 'e), t('c, 'e)) => t('d, 'e);

let mapError: ('e => 'f, t('a, 'e)) => t('a, 'f);

let mapBoth: ('a => 'b, 'e => 'f, t('a, 'e)) => t('b, 'f);

let andThen: ('a => t('b, 'e), t('a, 'e)) => t('b, 'e);

let withDefault: ('a, t('a, 'e)) => 'a;

let fromResult: Js.Result.t('a, 'e) => t('a, 'e);

let toOption: t('a, 'e) => option('a);

let append: (t('a, 'e), t('b, 'e)) => t(('a, 'b), 'e);

let succeed: 'a => t('a, 'e);

let isSuccess: t('a, 'e) => bool;

let isFailure: t('a, 'e) => bool;

let isLoading: t('a, 'e) => bool;

let isNotAsked: t('a, 'e) => bool;