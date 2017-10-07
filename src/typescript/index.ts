import * as bindings from 'bindings';

export enum FS_TYPE_CONSTANTS {
	FS_UNKNOWN,
	FS_FILE,
	FS_DIR,
	FS_LINK,
	FS_FIFO,
	FS_SOCKET,
	FS_CHAR,
	FS_BLOCK
}

export interface IScandirEntry {
	name: string;
	type: FS_TYPE_CONSTANTS;
}

export interface IAddon {
	scandir(path: string, callback?: (err: NodeJS.ErrnoException, entries: IScandirEntry[]) => void): void;
	scandirSync(path: string): IScandirEntry[];
}

const addon = bindings<IAddon>('addon.node');

/**
 * Asynchronous scandir(3) – scan a directory for matching entries.
 * @param path A path to a file.
 * @param callback
 */
export const scandir = addon.scandir;

/**
 * Synchronous scandir(3) – scan a directory for matching entries.
 * @param path A path to a file.
 * @return {IScandirEntry[]}
 */
export const scandirSync = addon.scandirSync;
