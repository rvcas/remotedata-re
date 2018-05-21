open Jest;

open Expect;

type t = RemoteData.t(string, string, string);

describe("RemoteData", () => {
  describe("NotAsked", () => {
    let actual = RemoteData.NotAsked;
    test("isNotAsked to be true", () =>
      actual |> RemoteData.isNotAsked |> expect |> toBe(true)
    );
    test("isLoading to be false", () =>
      actual |> RemoteData.isLoading |> expect |> toBe(false)
    );
    test("isSuccess to be false", () =>
      actual |> RemoteData.isSuccess |> expect |> toBe(false)
    );
    test("isFailure to be false", () =>
      actual |> RemoteData.isFailure |> expect |> toBe(false)
    );
  });
  describe("Loading('p)", () => {
    let actual = RemoteData.Loading("");
    test("isNotAsked to be false", () =>
      actual |> RemoteData.isNotAsked |> expect |> toBe(false)
    );
    test("isLoading to be true", () =>
      actual |> RemoteData.isLoading |> expect |> toBe(true)
    );
    test("isSuccess to be false", () =>
      actual |> RemoteData.isSuccess |> expect |> toBe(false)
    );
    test("isFailure to be false", () =>
      actual |> RemoteData.isFailure |> expect |> toBe(false)
    );
  });
  describe("Success('a)", () => {
    let actual = RemoteData.Success("");
    test("isNotAsked to be false", () =>
      actual |> RemoteData.isNotAsked |> expect |> toBe(false)
    );
    test("isLoading to be false", () =>
      actual |> RemoteData.isLoading |> expect |> toBe(false)
    );
    test("isSuccess to be true", () =>
      actual |> RemoteData.isSuccess |> expect |> toBe(true)
    );
    test("isFailure to be false", () =>
      actual |> RemoteData.isFailure |> expect |> toBe(false)
    );
  });
  describe("Failure('e)", () => {
    let actual = RemoteData.Failure("");
    test("isNotAsked to be false", () =>
      actual |> RemoteData.isNotAsked |> expect |> toBe(false)
    );
    test("isLoading to be false", () =>
      actual |> RemoteData.isLoading |> expect |> toBe(false)
    );
    test("isSuccess to be false", () =>
      actual |> RemoteData.isSuccess |> expect |> toBe(false)
    );
    test("isFailure to be true", () =>
      actual |> RemoteData.isFailure |> expect |> toBe(true)
    );
  });
  describe("andMap", () => {
    test("Success", () =>
      RemoteData.andMap(
        RemoteData.Success("before"),
        RemoteData.Success(before => before ++ " after"),
      )
      |> expect
      |> toEqual(RemoteData.Success("before after"))
    );
    test("Failure before", () =>
      RemoteData.andMap(RemoteData.Failure("before"), RemoteData.NotAsked)
      |> expect
      |> toEqual(RemoteData.Failure("before"))
    );
    test("Failure after", () =>
      RemoteData.andMap(RemoteData.NotAsked, RemoteData.Failure("after"))
      |> expect
      |> toEqual(RemoteData.Failure("after"))
    );
    test("Loading before", () =>
      RemoteData.andMap(RemoteData.Loading("before"), RemoteData.NotAsked)
      |> expect
      |> toEqual(RemoteData.Loading("before"))
    );
    test("Loading after", () =>
      RemoteData.andMap(RemoteData.NotAsked, RemoteData.Loading("after"))
      |> expect
      |> toEqual(RemoteData.Loading("after"))
    );
    test("NotAsked before", () =>
      RemoteData.andMap(
        RemoteData.NotAsked,
        RemoteData.Success(before => before ++ " after"),
      )
      |> expect
      |> toEqual(RemoteData.NotAsked)
    );
    test("NotAsked after", () =>
      RemoteData.andMap(RemoteData.Success("before"), RemoteData.NotAsked)
      |> expect
      |> toEqual(RemoteData.NotAsked)
    );
  });
  describe("map", () => {
    let mapper = before => before ++ " after";
    test("Success", () =>
      RemoteData.map(mapper, RemoteData.Success("before"))
      |> expect
      |> toEqual(RemoteData.Success("before after"))
    );
    test("Failure", () =>
      RemoteData.map(mapper, RemoteData.Failure("failure"))
      |> expect
      |> toEqual(RemoteData.Failure("failure"))
    );
    test("Loading", () =>
      RemoteData.map(mapper, RemoteData.Loading("loading"))
      |> expect
      |> toEqual(RemoteData.Loading("loading"))
    );
    test("NotAsked", () =>
      RemoteData.map(mapper, RemoteData.NotAsked)
      |> expect
      |> toEqual(RemoteData.NotAsked)
    );
  });
  describe("map2", () => {
    let mapper = (before1, before2) => before1 ++ " " ++ before2 ++ " after";
    test("Success", () =>
      RemoteData.map2(
        mapper,
        RemoteData.Success("before1"),
        RemoteData.Success("before2"),
      )
      |> expect
      |> toEqual(RemoteData.Success("before1 before2 after"))
    );
    test("Failure - first", () =>
      RemoteData.map2(
        mapper,
        RemoteData.Failure("failure1"),
        RemoteData.Failure("failure2"),
      )
      |> expect
      |> toEqual(RemoteData.Failure("failure1"))
    );
    test("Failure - second", () =>
      RemoteData.map2(
        mapper,
        RemoteData.Success("failure1"),
        RemoteData.Failure("failure2"),
      )
      |> expect
      |> toEqual(RemoteData.Failure("failure2"))
    );
    test("Loading - first", () =>
      RemoteData.map2(
        mapper,
        RemoteData.Loading("loading1"),
        RemoteData.Loading("loading2"),
      )
      |> expect
      |> toEqual(RemoteData.Loading("loading1"))
    );
    test("Loading - second", () =>
      RemoteData.map2(
        mapper,
        RemoteData.Success("loading1"),
        RemoteData.Loading("loading2"),
      )
      |> expect
      |> toEqual(RemoteData.Loading("loading2"))
    );
    test("NotAsked - first", () =>
      RemoteData.map2(mapper, RemoteData.NotAsked, RemoteData.NotAsked)
      |> expect
      |> toEqual(RemoteData.NotAsked)
    );
    test("NotAsked - second", () =>
      RemoteData.map2(
        mapper,
        RemoteData.Success("notAsked1"),
        RemoteData.NotAsked,
      )
      |> expect
      |> toEqual(RemoteData.NotAsked)
    );
  });
  describe("map3", () => {
    let mapper = (before1, before2, before3) =>
      before1 ++ " " ++ before2 ++ " " ++ before3 ++ " after";
    test("Success", () =>
      RemoteData.map3(
        mapper,
        RemoteData.Success("before1"),
        RemoteData.Success("before2"),
        RemoteData.Success("before3"),
      )
      |> expect
      |> toEqual(RemoteData.Success("before1 before2 before3 after"))
    );
    test("Failure - first", () =>
      RemoteData.map3(
        mapper,
        RemoteData.Failure("failure1"),
        RemoteData.Failure("failure2"),
        RemoteData.Failure("failure3"),
      )
      |> expect
      |> toEqual(RemoteData.Failure("failure1"))
    );
    test("Failure - second", () =>
      RemoteData.map3(
        mapper,
        RemoteData.Success("failure1"),
        RemoteData.Failure("failure2"),
        RemoteData.Failure("failure3"),
      )
      |> expect
      |> toEqual(RemoteData.Failure("failure2"))
    );
    test("Failure - third", () =>
      RemoteData.map3(
        mapper,
        RemoteData.Success("failure1"),
        RemoteData.Success("failure2"),
        RemoteData.Failure("failure3"),
      )
      |> expect
      |> toEqual(RemoteData.Failure("failure3"))
    );
    test("Loading - first", () =>
      RemoteData.map3(
        mapper,
        RemoteData.Loading("loading1"),
        RemoteData.Loading("loading2"),
        RemoteData.Loading("loading3"),
      )
      |> expect
      |> toEqual(RemoteData.Loading("loading1"))
    );
    test("Loading - second", () =>
      RemoteData.map3(
        mapper,
        RemoteData.Success("loading1"),
        RemoteData.Loading("loading2"),
        RemoteData.Loading("loading3"),
      )
      |> expect
      |> toEqual(RemoteData.Loading("loading2"))
    );
    test("Loading - third", () =>
      RemoteData.map3(
        mapper,
        RemoteData.Success("loading1"),
        RemoteData.Success("loading2"),
        RemoteData.Loading("loading3"),
      )
      |> expect
      |> toEqual(RemoteData.Loading("loading3"))
    );
    test("NotAsked - first", () =>
      RemoteData.map3(
        mapper,
        RemoteData.NotAsked,
        RemoteData.NotAsked,
        RemoteData.NotAsked,
      )
      |> expect
      |> toEqual(RemoteData.NotAsked)
    );
    test("NotAsked - second", () =>
      RemoteData.map3(
        mapper,
        RemoteData.Success("notAsked1"),
        RemoteData.NotAsked,
        RemoteData.NotAsked,
      )
      |> expect
      |> toEqual(RemoteData.NotAsked)
    );
    test("NotAsked - third", () =>
      RemoteData.map3(
        mapper,
        RemoteData.Success("notAsked1"),
        RemoteData.Success("notAsked2"),
        RemoteData.NotAsked,
      )
      |> expect
      |> toEqual(RemoteData.NotAsked)
    );
  });
  describe("mapError", () => {
    let mapper = before => before ++ " after";
    test("Success", () =>
      RemoteData.mapError(mapper, RemoteData.Success("before"))
      |> expect
      |> toEqual(RemoteData.Success("before"))
    );
    test("Failure", () =>
      RemoteData.mapError(mapper, RemoteData.Failure("before"))
      |> expect
      |> toEqual(RemoteData.Failure("before after"))
    );
    test("Loading", () =>
      RemoteData.mapError(mapper, RemoteData.Loading("loading"))
      |> expect
      |> toEqual(RemoteData.Loading("loading"))
    );
    test("NotAsked", () =>
      RemoteData.mapError(mapper, RemoteData.NotAsked)
      |> expect
      |> toEqual(RemoteData.NotAsked)
    );
  });
  describe("mapBoth", () => {
    let successMapper = before => before ++ " after success";
    let errorMapper = before => before ++ " after error";
    test("Success", () =>
      RemoteData.mapBoth(
        successMapper,
        errorMapper,
        RemoteData.Success("before"),
      )
      |> expect
      |> toEqual(RemoteData.Success("before after success"))
    );
    test("Failure", () =>
      RemoteData.mapBoth(
        successMapper,
        errorMapper,
        RemoteData.Failure("before"),
      )
      |> expect
      |> toEqual(RemoteData.Failure("before after error"))
    );
    test("Loading", () =>
      RemoteData.mapBoth(
        successMapper,
        errorMapper,
        RemoteData.Loading("loading"),
      )
      |> expect
      |> toEqual(RemoteData.Loading("loading"))
    );
    test("NotAsked", () =>
      RemoteData.mapBoth(successMapper, errorMapper, RemoteData.NotAsked)
      |> expect
      |> toEqual(RemoteData.NotAsked)
    );
  });
});
