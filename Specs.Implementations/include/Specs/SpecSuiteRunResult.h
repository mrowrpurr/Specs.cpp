#pragma once

#include <Specs/API.h>

namespace SpecsCpp {

    class SpecSuiteRunResult : public ISpecSuiteRunResult {
        std::uint32_t _passed    = 0;
        std::uint32_t _failed    = 0;
        std::uint32_t _not_run   = 0;
        std::uint32_t _timed_out = 0;

    public:
        std::uint32_t passed() const override { return _passed; }
        std::uint32_t failed() const override { return _failed; }
        std::uint32_t not_run() const override { return _not_run; }
        std::uint32_t timed_out() const override { return _timed_out; }

        void increment_passed() { ++_passed; }
        void increment_failed() { ++_failed; }
        void increment_not_run() { ++_not_run; }
        void increment_timed_out() { ++_timed_out; }
    };
}
