#include "sleep.h"

using v8::FunctionTemplate;
using v8::Handle;
using v8::Object;
using v8::String;

NAN_METHOD(Sleep) {
  Nan::HandleScope scope;

  if (info.Length() < 1 || !info[0]->IsUint32()) {
    return Nan::ThrowError("Expected number of seconds");
  }

  node_sleep(info[0]->Uint32Value());

  info.GetReturnValue().SetUndefined();
}

NAN_METHOD(MUSleep) {
  Nan::HandleScope scope;

  if (info.Length() < 1 || !info[0]->IsUint32()) {
    return Nan::ThrowError("Expected number of microseconds");
  }

  node_usleep(info[0]->Uint32Value());

  info.GetReturnValue().SetUndefined();
}

NAN_MODULE_INIT(init) {
  Nan::Set(target, Nan::New<String>("sleep").ToLocalChecked(),
    Nan::New<FunctionTemplate>(Sleep)->GetFunction());
  Nan::Set(target, Nan::New<String>("usleep").ToLocalChecked(),
    Nan::New<FunctionTemplate>(MUSleep)->GetFunction());
}

NODE_MODULE(node_sleep, init)
