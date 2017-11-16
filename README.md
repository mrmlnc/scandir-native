# scandir-native

A `fs.scandir` method with some features.

## Donate

If you want to thank me, or promote your Issue.

[![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://paypal.me/mrmlnc)

> Sorry, but I have work and support for plugins and modules requires some time after work. I will be glad of your support or PR's.

## Install

```
$ npm i scandir-native
```

:warning: Compiling on Windows machines requires the [node-gyp prerequisites](https://github.com/nodejs/node-gyp#on-windows).

## Supports

  * Node.js (4, 6, 8 and etc.)
  * Node.js with ChakraCore (below 8.4.0 on macOS and Linux (works fine on Windows), see this [issue](https://github.com/nodejs/node-chakracore/issues/417))

## Why?

  * Temporary solution for [«A proposal to add fs.scandir method to FS module»](https://github.com/nodejs/node/issues/15699).

## Usage

```js
const scandir = require('scandir-native');

scandir.scandir('.', (err, entries) => {
	if (err) {
		console.error(err); // Standard FS errors
		return;
	}

	console.dir(entries, { colors: true });
	// [{ name: 'filepath', type: 2 }, { name: 'dirpath', type: 1 }]
});
```

## API

#### `FS_TYPE_CONSTANTS`

```js
0 is 'FS_UNKNOWN'
1 is 'FS_FILE'
2 is 'FS_DIR'
3 is 'FS_LINK'
4 is 'FS_FIFO'
5 is 'FS_SOCKET'
6 is 'FS_CHAR'
7 is 'FS_BLOCK'
```

Enum for entry type builded from and for [`uv_dirent_type_t`](https://github.com/libuv/libuv/blob/e9cda2cfe71dce809a6ecba4ff913e24e36c233e/include/uv.h#L1019-L1028).

#### `IScandirEntry`

  * name `String`
  * type [`FILE_TYPE_CONSTANTS`](https://github.com/mrmlnc/scandir-native#fs_type_constants)

TypeScript interface for each entry in the directory.

#### `.scandir(path, callback) => void`

  * path `String`
  * callback `Function`
    * err `Error`
    * entries [`IScandirEntry[]`](https://github.com/mrmlnc/scandir-native#iscandirentry)

Asynchronous [`scandir(3)`](http://man7.org/linux/man-pages/man3/scandir.3.html). Reads the contents of a directory. The callback gets two arguments (`err`, `entries`) where `entries` is an array of objects (`name` and `type`) of the files in the directory excluding `.` and `..`.

#### `.scandirSync(path) => IScandirEntry[]`

  * path `String`
  * returns [`IScandirEntry[]`](https://github.com/mrmlnc/scandir-native#iscandirentry)

Synchronous [`scandir(3)`](http://man7.org/linux/man-pages/man3/scandir.3.html). Returns an array of objects (`name` and `type`) excluding `.` and `..`.

## Example

```ts
const scandir = require('scandir-native');

const dirs: string[] = [];
const nonDirs: string[] = [];

scandir.scandir('.', (err, entries) => {
	if (err) {
		console.error(err); // Standard FS errors
		return;
	}

	entries.forEach((entry) => {
		if (entry.type === scandir.FS_TYPE_CONSTANTS.FS_DIR) {
			dirs.push(entry.name);
		} else {
			nonDirs.push(entry.name);
		}
	})
});
```

## Changelog

See the [Releases section of our GitHub project](https://github.com/mrmlnc/scandir-native/releases) for changelogs for each release version.

## License

This software is released under the terms of the MIT license.
