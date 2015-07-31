
#include <nan.h>


using v8::FunctionTemplate;
using v8::Handle;
using v8::Object;
using v8::String;


#if defined _WIN32 || defined _WIN64
unsigned int sleep(unsigned int seconds)
{
    Sleep(seconds * 1000);
    return 0;
}
int usleep(unsigned __int64 usec)
{
    LARGE_INTEGER li;
    li.QuadPart = -10 * usec;     // negative values for relative time

    HANDLE timer = CreateWaitableTimer(NULL, TRUE, NULL);
    if(!timer) return -1;

    SetWaitableTimer(timer, &li, 0, NULL, NULL, 0);
    WaitForSingleObject(timer, INFINITE);
    CloseHandle(timer);
    return 0;
}
#else
#   include <unistd.h>
#endif


NAN_METHOD(Sleep) {
  Nan::HandleScope scope;

  if (info.Length() < 1 || !info[0]->IsUint32()) {
    return Nan::ThrowError("Expected number of seconds");
  }

  sleep(info[0]->Uint32Value());

  info.GetReturnValue().SetUndefined();
}

NAN_METHOD(USleep) {
  Nan::HandleScope scope;

  if (info.Length() < 1 || !info[0]->IsUint32()) {
    return Nan::ThrowError("Expected number of microseconds");
  }

  usleep(info[0]->Uint32Value());

  info.GetReturnValue().SetUndefined();
}


NAN_MODULE_INIT(init) {
  Nan::Set(target, Nan::New<String>("sleep").ToLocalChecked(),
    Nan::New<FunctionTemplate>(Sleep)->GetFunction());
  Nan::Set(target, Nan::New<String>("usleep").ToLocalChecked(),
    Nan::New<FunctionTemplate>(USleep)->GetFunction());
}


NODE_MODULE(node_sleep, init)

