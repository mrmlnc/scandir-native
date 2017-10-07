#include <nan.h>
#include <uv.h>
#include <vector>

namespace Scandir {
struct DirEntry
{
	std::string name;
	uv_dirent_type_t type;
};

int
scandir(const std::string& directory, std::vector<Scandir::DirEntry>& entries)
{
	uv_fs_t req;
	const int code = uv_fs_scandir(uv_default_loop(), &req, directory.c_str(), 0, nullptr);
	if (code < 0) {
		return code;
	}

	uv_dirent_t ent;
	while (uv_fs_scandir_next(&req, &ent) != UV_EOF) {
		entries.push_back(Scandir::DirEntry{ ent.name, ent.type });
	}

	uv_fs_req_cleanup(&req);

	return 0;
}
}
