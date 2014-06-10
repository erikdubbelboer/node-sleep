#ifndef BUILDING_NODE_EXTENSION
#define BUILDING_NODE_EXTENSION
#endif // BUILDING_NODE_EXTENSION

#include <v8.h>
#include <node.h>


// Node 0.11.8 etc
#if (NODE_MODULE_VERSION == 13)
#define SCOPE Isolate* isolate = Isolate::GetCurrent(); \
              HandleScope scope(isolate)
#define EXCEPTION(str) ThrowException(Exception::TypeError(String::New(str))) 
#define ARGUMENTS v8::FunctionCallbackInfo<Value>
#define RETURNTYPE void
#define RETURN

// Node 0.11.13 etc
#elif (NODE_MODULE_VERSION > 13)
#define SCOPE Isolate* isolate = Isolate::GetCurrent(); \
              HandleScope scope(isolate)
#define EXCEPTION(str) isolate->ThrowException(Exception::TypeError(String::NewFromUtf8(isolate, str)))
#define ARGUMENTS v8::FunctionCallbackInfo<Value>
#define RETURNTYPE void
#define RETURN

// Node 0.12 and below
#else
#define SCOPE HandleScope scope
#define EXCEPTION(str) return ThrowException(Exception::TypeError(String::New(str))) 
#define ARGUMENTS Arguments
#define RETURNTYPE Handle<Value>
#define RETURN return scope.Close(Undefined())
#endif


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


using namespace v8;
using namespace node;


RETURNTYPE Sleep(const ARGUMENTS& args) {
  SCOPE;

  if (args.Length() < 1 || !args[0]->IsUint32()) {
    EXCEPTION("Expected number of seconds");
  }

  sleep(args[0]->Uint32Value());

  RETURN;
}

RETURNTYPE USleep(const ARGUMENTS& args) {
  SCOPE;

  if (args.Length() < 1 || !args[0]->IsUint32()) {
    EXCEPTION("Expected number of micro");
  }

  usleep(args[0]->Uint32Value());

  RETURN;
}


extern "C" void init(Handle<Object> target) {
  NODE_SET_METHOD(target, "sleep", Sleep);
  NODE_SET_METHOD(target, "usleep", USleep);
}


#ifdef NODE_MODULE
NODE_MODULE(node_sleep, init)
#endif

