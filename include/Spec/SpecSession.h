#pragma once

#include "Spec/SpecContext.h"
#include "Spec/SpecResults.h"

namespace Spec {

    // TODO : remove, just pass SpecContext to Runner

    //! Represents a session in which to run groups of specs
    class SpecSession {
        SpecContext _context;
        SpecResults _results;

    public:
        SpecSession(SpecContext& context) : _context(context) {}
        SpecSession() : SpecSession(SpecContext::GetDefault()) {}

        /** Global, default SpecSession */
        static SpecSession& GetDefault() {
            static SpecSession session;
            return session;
        }

        SpecContext& GetContext() { return _context; }
        SpecResults& GetResults() { return _results; }
    };
}
