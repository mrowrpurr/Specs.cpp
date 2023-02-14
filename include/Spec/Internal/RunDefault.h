#pragma once

#include "Spec/SpecConfig.h"

namespace Spec::Internal {

    void RunDefault() {
        auto& config   = SpecConfig::GetDefaults();
        auto& runner   = config.GetRunner();
        auto  reporter = config.GetReporter();
        auto& session  = SpecSession::GetDefault();
        session.AddReporter(reporter);
        auto promise = std::promise<void>{};
        runner.RunSpecs(promise, session);
        promise.get_future().wait_for(std::chrono::seconds(5));
    }
}
