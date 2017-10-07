#include <iostream>
#include <nan.h>
#include <node.h>
#include <vector>

namespace ScandirSyncMethod {
using v8::Local;
using v8::Value;
using v8::Array;
using v8::Object;
using v8::Number;
using v8::String;

#define STR(s) Nan::New<String>(s).ToLocalChecked()
#define NUM(s) Nan::New<Number>(s)

NAN_METHOD(scandir)
{
	if (!info[0]->IsString()) {
		return Nan::ThrowTypeError("path must be a string");
	}
	Local<String> nan_directory = info[0].As<String>();
	std::string directory = std::string(*String::Utf8Value(nan_directory));

	std::vector<Scandir::DirEntry> dir_entries;
	int status = Scandir::scandir(directory, dir_entries);
	if (status != 0) {
		Local<Value> error = node::UVException(status, "scandir");
		Nan::ThrowError(error);
		return;
	}

	Local<Array> entries = Nan::New<Array>(dir_entries.size());

	for (unsigned i = 0; i < entries->Length(); i++) {
		Local<Object> hash = Nan::New<Object>();

		Nan::Set(hash, STR("name"), STR(dir_entries.at(i).name));
		Nan::Set(hash, STR("type"), NUM(dir_entries.at(i).type));

		Nan::Set(entries, i, hash);
	}

	info.GetReturnValue().Set(entries);
}
}
