# RemoteData

[![npm version](https://img.shields.io/npm/v/remotedata-re.svg?style=flat-square)](https://www.npmjs.com/package/remotedata-re)
[![Build Status](https://travis-ci.com/lrosa007/remotedata-re.svg?branch=master)](https://travis-ci.com/lrosa007/remotedata-re)
[![license](https://img.shields.io/npm/l/remotedata-re.svg?style=flat-square)](https://www.npmjs.com/package/remotedata-re)

For some background, [read this post](http://blog.jenkster.com/2016/06/how-elm-slays-a-ui-antipattern.html)

## Installation

```shell
npm install remotedata-re

# or yarn

yarn add remotedata-re
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
    let s = Js.Array.joinWith(", ", previous->Belt.List.toArray);
    {j|Loading ($s)|j};
  | Success(data) =>
    let s = Js.Array.joinWith(" + ", data->Belt.List.toArray);
    {j|Success ($s)|j};
  | Failure(_error) => "Failure"
  };

Js.log(RemoteData.NotAsked->debugLog);
/* output: Not Asked */

Js.log(RemoteData.Loading(["foo", "bar"])->debugLog);
/* output: Loading (foo, bar)*/

Js.log(RemoteData.Success(["foo", "bar", "baz"])->debugLog);
/* output: Success (foo + bar + baz)*/

Js.log(RemoteData.Failure("oops")->debugLog);
```

## Examples

* [repos](https://github.com/lrosa007/repos)

## Note

Inspiration: [remotedata](https://github.com/krisajenkins/remotedata)
