#pragma once

#include <Specs/API.h>

namespace SpecsCpp {

    class SpecDone {
        ISpecCodeBlock::SpecCodeBlockAsyncDoneFn* _doneFn;

    public:
        SpecDone(ISpecCodeBlock::SpecCodeBlockAsyncDoneFn* doneFn) : _doneFn(doneFn) {}

        void operator()() { _doneFn->invoke(); }
    };
}
