#pragma once

#include "Spec/Types/Reporters/OneLineReporter.h"
#include "Spec/Types/Runners/SimpleRunner.h"
#include "Spec/Types/SpecApp.h"

namespace Spec::Types {
    class SpecMain {
    public:
        static int RunDefault() {
            auto app = SpecApp::GetDefaultInstance();
            app->LoadDefinitionBlocks();
            app->Runner    = std::make_shared<Runners::SimpleRunner>();
            app->Reporters = std::vector<std::shared_ptr<ISpecReporter>>();
            app->Reporters.push_back(std::make_shared<Reporters::OneLineReporter>());
            return app->RunAndWait();
        }
    };
}