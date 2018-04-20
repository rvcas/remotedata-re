open Jest;

open Expect;

type t = RemoteData.t(string, string, string);

describe("RemoteData", () => {
  describe("NotAsked", () =>
    test("isNotAsked", () => {
      let actual = RemoteData.NotAsked;
      actual |> RemoteData.isNotAsked |> expect |> toBe(true);
    })
  );
  describe("Loading('p)", () =>
    test("isLoading", () => {
      let actual = RemoteData.Loading("");
      actual |> RemoteData.isLoading |> expect |> toBe(true);
    })
  );
  describe("Success('a)", () =>
    test("Success", () => {
      let actual = RemoteData.Success("");
      actual |> RemoteData.isSuccess |> expect |> toBe(true);
    })
  );
  describe("Failure('e)", () =>
    test("Failure", () => {
      let actual = RemoteData.Failure("");
      actual |> RemoteData.isFailure |> expect |> toBe(true);
    })
  );
});
