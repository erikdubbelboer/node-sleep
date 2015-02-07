
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
  NanScope();

  if (args.Length() < 1 || !args[0]->IsUint32()) {
    return NanThrowError("Expected number of seconds");
  }

  sleep(args[0]->Uint32Value());

  NanReturnUndefined();
}

NAN_METHOD(USleep) {
  NanScope();

  if (args.Length() < 1 || !args[0]->IsUint32()) {
    return NanThrowError("Expected number of microseconds");
  }

  usleep(args[0]->Uint32Value());

  NanReturnUndefined();
}


void init(Handle<Object> exports) {
  exports->Set(NanNew<String>("sleep"), NanNew<FunctionTemplate>(Sleep)->GetFunction());
  exports->Set(NanNew<String>("usleep"), NanNew<FunctionTemplate>(USleep)->GetFunction());
}


NODE_MODULE(node_sleep, init)

