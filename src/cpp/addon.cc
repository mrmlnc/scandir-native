#include <nan.h>

#include "scandir.cc"
#include "async.cc"
#include "sync.cc"

NAN_MODULE_INIT(init)
{
	Nan::Export(target, "scandir", ScandirAsyncMethod::scandir);
	Nan::Export(target, "scandirSync", ScandirSyncMethod::scandir);
}

NODE_MODULE(scandir, init);
