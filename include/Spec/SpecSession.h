#pragma once

#include <vector>

#include "Spec/SpecContext.h"
#include "Spec/SpecReporter.h"
#include "Spec/SpecResults.h"

namespace Spec {

    // TODO : remove, just pass SpecContext to Runner

    //! Represents a session in which to run groups of specs
    class SpecSession {
        SpecContext               _context;
        SpecResults               _results;
        std::vector<SpecReporter> _reporters;

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

        std::vector<SpecReporter>& GetReporters() { return _reporters; }
        void                       AddReporter(SpecReporter& reporter) { _reporters.push_back(reporter); }

        /** Session is also responsible for tracking results
         * and delegating to reporter(s) */
        void BeginTest(SpecTest& test) { Print("START {}", test.description); }
        void EndTest(SpecTest& test, bool passed, const std::string& failureMessage) {
            Print("END {}", test.description);
        }
        void BeginGroup(SpecGroup& group) { Print(group.description); }
        void EndGroup(SpecGroup& group) { Print(group.description); }
    };
}
