#pragma once

#include <vector>

#include "Spec/SpecContext.h"
#include "Spec/SpecReporter.h"
#include "Spec/SpecResults.h"

namespace Spec {

    // TODO : remove, just pass SpecContext to Runner

    //! Represents a session in which to run groups of specs
    class SpecSession {
        SpecContext                                _context;
        SpecResults                                _results;
        std::vector<std::shared_ptr<SpecReporter>> _reporters;

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

        std::vector<std::shared_ptr<SpecReporter>>& GetReporters() { return _reporters; }
        void AddReporter(std::shared_ptr<SpecReporter> reporter) { _reporters.push_back(reporter); }

        /** Session is also responsible for tracking results
         * and delegating to reporter(s) */
        void BeginTest(SpecTest& test) {
            // _results.BeginTest(test);
            for (auto& reporter : _reporters) reporter->BeginTest(test);
        }
        void EndTest(SpecTest& test, bool passed, const std::string& failureMessage) {
            // _results.EndTest(test, passed, failureMessage);
            for (auto& reporter : _reporters) reporter->EndTest(test, passed, failureMessage);
        }
        void BeginGroup(SpecGroup& group) {
            // _results.BeginGroup(group);
            for (auto& reporter : _reporters) reporter->BeginGroup(group);
        }
        void EndGroup(SpecGroup& group) {
            // _results.EndGroup(group);
            for (auto& reporter : _reporters) reporter->EndGroup(group);
        }
    };
}
