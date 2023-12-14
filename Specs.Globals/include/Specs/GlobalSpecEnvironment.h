#pragma once

#include <Specs/API.h>

namespace SpecsCpp {

    class GlobalSpecEnvironment {
        ISpecEnvironment* _environment = nullptr;

    public:
        ISpecEnvironment* get() const { return _environment; }
        void              set(ISpecEnvironment* environment) { _environment = environment; }
    };

    inline GlobalSpecEnvironment& global_spec_environment() {
        static GlobalSpecEnvironment instance;
        return instance;
    }

    // Helpers for registration of various things...

    inline void register_exception_handler(IExceptionHandler* handler) {
        global_spec_environment().get()->local_exception_handlers()->register_exception_handler(
            handler
        );
    }

    inline void register_reporter(const char* name, ISpecReporter* reporter) {
        global_spec_environment().get()->reporters()->add(name, reporter);
    }

    inline void register_runner(const char* name, ISpecRunner* runner) {
        global_spec_environment().get()->runners()->add(name, runner);
    }
}
