import * as assert from 'assert';

import * as scandir from './index';

describe('ScandirAddon', () => {
	describe('FS_TYPE_CONSTANTS', () => {
		it('should return 0 for FS_UNKNOWN', () => {
			assert.equal(0, scandir.FS_TYPE_CONSTANTS.FS_UNKNOWN);
		});

		it('should return 7 for FS_BLOCK', () => {
			assert.equal(7, scandir.FS_TYPE_CONSTANTS.FS_BLOCK);
		});
	});

	describe('Asynchronous', () => {
		it('should throw error when first argument is not a string', () => {
			assert.throws(() => scandir.scandir(<any>123, null), /path must be a string/);
		});

		it('should throw error when second argument is not a function', () => {
			assert.throws(() => scandir.scandir('.', null), /'callback' argument must be a function/);
		});

		it('should return entries for provided directory', (done) => {
			const expected = ['a.txt', 'b.txt', 'c.txt'];

			scandir.scandir('./fixtures', (err, entries) => {
				if (err) {
					assert.fail(err.message);
					done();
				}

				assert.deepEqual(entries.map((entry) => entry.name), expected);
				done();
			});
		});

		it('should throw error where directory is not exists', (done) => {
			scandir.scandir('./non-exists', (err) => {
				if (err) {
					assert.equal(err.message, 'ENOENT: no such file or directory, scandir');
					return done();
				}

				assert.fail('Error is not handled!');
			});
		});

		it('should throw error where provided path is not a directory', (done) => {
			scandir.scandir('./.clang-format', (err) => {
				if (err) {
					assert.equal(err.message, 'ENOTDIR: not a directory, scandir');
					return done();
				}

				assert.fail('Error is not handled!');
			});
		});
	});

	describe('Synchronous', () => {
		it('should throw error when first argument is not a string', () => {
			assert.throws(() => scandir.scandirSync(<any>123), /path must be a string/);
		});

		it('should return entries for provided directory', () => {
			const expected = ['a.txt', 'b.txt', 'c.txt'];

			const actual = scandir.scandirSync('./fixtures');

			assert.deepEqual(actual.map((entry) => entry.name), expected);
		});

		it('should throw error where directory is not exists', () => {
			assert.throws(() => scandir.scandirSync('./non-exists'), /ENOENT: no such file or directory, scandir/);
		});

		it('should throw error where provided path is not a directory', () => {
			assert.throws(() => scandir.scandirSync('./.clang-format'), /ENOTDIR: not a directory, scandir/);
		});
	});
});
