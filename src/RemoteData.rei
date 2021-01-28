type t('a, 'p, 'e) =
  | NotAsked
  | Loading('p)
  | Failure('e)
  | Success('a);

let andMap: (t('a, 'p, 'e), t('a => 'b, 'p, 'e)) => t('b, 'p, 'e);

let map: ('a => 'b, t('a, 'p, 'e)) => t('b, 'p, 'e);

let map2: (('a, 'b) => 'c, t('a, 'p, 'e), t('b, 'p, 'e)) => t('c, 'p, 'e);

let map3:
  (('a, 'b, 'c) => 'd, t('a, 'p, 'e), t('b, 'p, 'e), t('c, 'p, 'e)) =>
  t('d, 'p, 'e);

let mapError: ('e => 'f, t('a, 'p, 'e)) => t('a, 'p, 'f);

let mapBoth: ('a => 'b, 'e => 'f, t('a, 'p, 'e)) => t('b, 'p, 'f);

let andThen: ('a => t('b, 'p, 'e), t('a, 'p, 'e)) => t('b, 'p, 'e);

let withDefault: ('a, t('a, 'p, 'e)) => 'a;

let fromResult: Belt.Result.t('a, 'e) => t('a, 'p, 'e);

let toOption: t('a, 'p, 'e) => option('a);

let append: (t('a, 'p, 'e), t('b, 'p, 'e)) => t(('a, 'b), 'p, 'e);

let succeed: 'a => t('a, 'p, 'e);

let isSuccess: t('a, 'p, 'e) => bool;

let isFailure: t('a, 'p, 'e) => bool;

let isLoading: t('a, 'p, 'e) => bool;

let isNotAsked: t('a, 'p, 'e) => bool;
