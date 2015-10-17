#include <nan.h>
#include <boost/coroutine/all.hpp>
#include <sstream>

using v8::FunctionTemplate;
using v8::Handle;
using v8::Object;
using v8::String;

NAN_METHOD(Fibo) {
    // Lambda from the Fibonacci example:
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

    // Write the results to a string stream:
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

    // Return it to node engine
    info.GetReturnValue().Set(Nan::New<String>(ss.str().c_str()).ToLocalChecked());
}

void InitAll(Handle<Object> exports) {
  // Method that returns the generated Fibonacci sequence as a string:
  exports->Set(Nan::New<String>("fibo").ToLocalChecked(),
    Nan::New<FunctionTemplate>(Fibo)->GetFunction());
}

NODE_MODULE(addon, InitAll)