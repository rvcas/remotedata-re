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
});
