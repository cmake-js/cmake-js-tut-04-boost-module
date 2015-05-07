#include <nan.h>
#include <boost/coroutine/all.hpp>
#include <sstream>

using v8::FunctionTemplate;
using v8::Handle;
using v8::Object;
using v8::String;

NAN_METHOD(Fibo) {
    NanScope();

    boost::coroutines::asymmetric_coroutine<int>::pull_type source(
        [&](boost::coroutines::asymmetric_coroutine<int>::push_type& sink) {
            int first = 1, second = 1;
            sink(first);
            sink(second);
            for (int i = 0; i < 8; ++i)
            {
                int third = first + second;
                first = second;
                second = third;
                sink( third);
            }
        });

    std::stringstream ss;

    bool first = true;
    for (auto i : source) {
        if (!first) {
            ss << " ";
        }
        else {
            first = false;
        }
        ss << i;
    }

    NanReturnValue(NanNew<String>(ss.str().c_str()));
}

void InitAll(Handle<Object> exports) {
  exports->Set(NanNew<String>("fibo"),
    NanNew<FunctionTemplate>(Fibo)->GetFunction());
}

NODE_MODULE(addon, InitAll)