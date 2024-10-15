#include <node.h>
#include "helloworld.h"

namespace voiceaddon
{
	using v8::FunctionCallbackInfo;
	using v8::Isolate;
	using v8::Local;
	using v8::Object;
	using v8::String;
	using v8::Value;

	// Hello World example
	void HelloWorld(const FunctionCallbackInfo<Value>& args) {

		Isolate* isolate = args.GetIsolate();
		args.GetReturnValue().Set(String::NewFromUtf8(
													  isolate, helloworld()).ToLocalChecked());
	}

	void Init(Local<Object> exports) {
		NODE_SET_METHOD(exports, "hello", HelloWorld);
	}

	NODE_MODULE(NODE_GYP_MODULE_NAME, Init);
	
}
