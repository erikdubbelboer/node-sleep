
#include <nan.h>


using v8::FunctionTemplate;
using v8::Handle;
using v8::Object;
using v8::String;


#if defined _WIN32 || defined _WIN64

NAN_METHOD(MSleep) {
  Nan::HandleScope scope;

  if (info.Length() < 1 || !info[0]->IsUint32()) {
    Nan::ThrowError("Expected number of seconds");
    return;
  }

  Sleep(info[0]->Uint32Value() * 1000);

  info.GetReturnValue().SetUndefined();
}

NAN_METHOD(MUSleep) {
  Nan::HandleScope scope;

  if (info.Length() < 1 || !info[0]->IsUint32()) {
    Nan::ThrowError("Expected number of microseconds");
    return;
  }

  LARGE_INTEGER li;
  li.QuadPart = -10 * info[0]->IntegerValue(); // negative values for relative time

  HANDLE timer = CreateWaitableTimer(NULL, TRUE, NULL);
  if (!timer) {
    Nan::ThrowError("Unable to create waitable timer");
    return;
  }

  SetWaitableTimer(timer, &li, 0, NULL, NULL, 0);
  WaitForSingleObject(timer, INFINITE);
  CloseHandle(timer);

  info.GetReturnValue().SetUndefined();
}

#else

#include <unistd.h>
#include <sys/time.h>

static void _sleep(useconds_t left) {
  useconds_t done;
  struct timeval start, end;

  while (left > 0) {
    gettimeofday(&start, NULL);
    usleep(left);
    gettimeofday(&end, NULL);

    done = (end.tv_sec - start.tv_sec) * 1000000 + (end.tv_usec - start.tv_usec);
    if (done > left) {
      left = 0;
    } else {
      left -= done;
    }
  }
}

NAN_METHOD(MSleep) {
  Nan::HandleScope scope;

  if (info.Length() < 1 || !info[0]->IsUint32()) {
    Nan::ThrowError("Expected number of seconds");
    return;
  }

  _sleep(Nan::To<uint32_t>(info[0]).FromJust() * 1000000);

  info.GetReturnValue().SetUndefined();
}

NAN_METHOD(MUSleep) {
  Nan::HandleScope scope;

  if (info.Length() < 1 || !info[0]->IsUint32()) {
    Nan::ThrowError("Expected number of microseconds");
    return;
  }

  _sleep(Nan::To<uint32_t>(info[0]).FromJust());

  info.GetReturnValue().SetUndefined();
}
#endif


NAN_MODULE_INIT(init) {
  Nan::Set(target, Nan::New<String>("sleep").ToLocalChecked(),
    Nan::New<FunctionTemplate>(MSleep)->GetFunction());
  Nan::Set(target, Nan::New<String>("usleep").ToLocalChecked(),
    Nan::New<FunctionTemplate>(MUSleep)->GetFunction());
}


NODE_MODULE(node_sleep, init)

