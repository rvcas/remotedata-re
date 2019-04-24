# RemoteData

[![Build Status][travis-image]][travis-url]
[![npm][npm-image]][npm-url]
[![Coveralls][coveralls-image]][coveralls-url]

For some background, [read this post](http://blog.jenkster.com/2016/06/how-elm-slays-a-ui-antipattern.html)

## Installation

```shell
npm install --save-dev remotedata-re
# or yarn
yarn add --dev remotedata-re
```
Then add it to `bsconfig.json`

```json
{
  ...
  "bs-dependencies": [
    "remotedata-re"
  ]
  ...
}
```

## Usage

```re
type data = list(string);
type error = string;
type remoteData = RemoteData.t(data, data, error);

let debugLog = (v: remoteData) =>
  switch (v) {
  | RemoteData.NotAsked => "Not Asked"
  | Loading(previous) => 
    let s = previous->Js.Array.joinWith(", ");
    {j|Loading ($s)|j}
  | Success(data) => 
    let s = data->Js.Array.joinWith(" + ");
    {j|Success ($s)|j}
  | Failure(error) => "Failure"
  };

Js.log(RemoteData.NotAsked->debugLog);
/* output: Not Asked */

Js.log(RemoteData.Loading(["foo","bar"])->debugLog);
/* output: Loading (foo, bar)*/

Js.log(RemoteData.Success(["foo", "bar", "baz"])->debugLog);
/* output: Success (foo + bar + baz)*/

Js.log(RemoteData.Failure("oops")->debugLog);
/* output: Failure */
```

## Examples

* [repos](https://github.com/lrosa007/repos)

## Note

Inspiration: [remotedata](https://github.com/krisajenkins/remotedata)
