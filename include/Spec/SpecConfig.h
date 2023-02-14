#pragma once

#include <atomic>

#include "Spec/Reporters/SimpleReporter.h"
#include "Spec/Runners/SimpleRunner.h"
#include "Spec/SpecReporter.h"
#include "Spec/SpecRunner.h"

namespace Spec {

    class SpecConfig {
        std::shared_ptr<SpecReporter> _reporter;
        std::shared_ptr<SpecRunner>   _runner;

    public:
        static SpecConfig& GetDefaults() {
            static SpecConfig config;
            if (!config._reporter) config._reporter = std::make_shared<Reporters::SimpleReporter>();
            if (!config._runner) config._runner = std::make_shared<Runners::SimpleRunner>();
            return config;
        }

        SpecConfig(SpecReporter reporter, SpecRunner runner)
            : _reporter(std::make_shared<SpecReporter>(std::move(reporter))),
              _runner(std::make_shared<SpecRunner>(std::move(runner))) {}

        SpecConfig() {}

        void SetReporter(SpecReporter reporter) { _reporter = std::make_shared<SpecReporter>(std::move(reporter)); }
        void SetRunner(SpecRunner runner) { _runner = std::make_shared<SpecRunner>(std::move(runner)); }

        SpecReporter& GetReporter() { return *_reporter; }
        SpecRunner&   GetRunner() { return *_runner; }
    };
}
