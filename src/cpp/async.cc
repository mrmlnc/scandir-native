#include <iostream>
#include <nan.h>
#include <node.h>
#include <vector>

namespace ScandirAsyncMethod {
using v8::Local;
using v8::Value;
using v8::Function;
using v8::Array;
using v8::Object;
using v8::Number;
using v8::String;

#define STR(s) Nan::New<String>(s).ToLocalChecked()
#define NUM(s) Nan::New<Number>(s)

class ScandirWorker: public Nan::AsyncWorker
{
public:
	ScandirWorker(Nan::Callback *callback, const std::string &directory): Nan::AsyncWorker(callback), directory(directory) {}
	~ScandirWorker() {}

	void
	Execute()
	{
		int status = Scandir::scandir(directory, dir_entries);
		if (status != 0) {
			error_code = status;
			SetErrorMessage("scandir");
		}
	}

	void
	HandleOKCallback()
	{
		Nan::HandleScope scope;

		Local<Array> entries = Nan::New<Array>(dir_entries.size());

		for (unsigned i = 0; i < entries->Length(); i++) {
			Local<Object> hash = Nan::New<Object>();

			Nan::Set(hash, STR("name"), STR(dir_entries.at(i).name));
			Nan::Set(hash, STR("type"), NUM(dir_entries.at(i).type));

			Nan::Set(entries, i, hash);
		}

		Local<Value> argv[] = { Nan::Null(), entries };

		Nan::AsyncResource resource("scandir-native:addon.async");
		callback->Call(2, argv, &resource);
	}

	void
	HandleErrorCallback()
	{
		Nan::HandleScope scope;

		Local<Value> argv[] = {
			node::UVException(error_code, "scandir"),
			Nan::Null()
		};

		Nan::AsyncResource resource("scandir-native:addon.async");
		callback->Call(1, argv, &resource);
	}

private:
	int error_code;

	std::string directory;
	std::vector<Scandir::DirEntry> dir_entries;
};

NAN_METHOD(scandir)
{
	if (!info[0]->IsString()) {
		return Nan::ThrowTypeError("path must be a string");
	}
	Local<String> nan_directory = info[0].As<String>();
	std::string directory = std::string(*Nan::Utf8String(nan_directory));

	if (!info[1]->IsFunction()) {
		return Nan::ThrowTypeError("'callback' argument must be a function");
	}
	Local<Function> callback = info[1].As<Function>();

	Nan::AsyncQueueWorker(new ScandirWorker(new Nan::Callback(callback), directory));
}
}
