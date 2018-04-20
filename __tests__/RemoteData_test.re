open Jest;

open Expect;

type remoteData  = RemoteData.t(string, string, string);

describe("RemoteData", () => {
  test("NotAsked", () => {
    let actual = RemoteData.NotAsked;
    actual |> expect |> toBe(RemoteData.NotAsked);
  });
  test("Loading", () => {
    let actual = RemoteData.Loading("");
    actual |> RemoteData.isLoading |> expect |> toBe(true);
  });
  test("Success", () => {
    let actual = RemoteData.Success("");
    actual |> RemoteData.isSuccess |> expect |> toBe(true);
  });
  test("Failure", () => {
    let actual = RemoteData.Failure("");
    actual |> RemoteData.isFailure |> expect |> toBe(true);
  });
});
