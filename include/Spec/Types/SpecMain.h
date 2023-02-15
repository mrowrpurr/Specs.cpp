#pragma once

#include "Spec/Types/SpecApp.h"
#include "Spec/Types/SpecDefinitionBlocks.h"

namespace Spec::Types {
    class SpecMain {
    public:
        static int RunDefault() {
            auto app = SpecApp::GetDefaultInstance();
            SpecDiscovery::SetGlobalInstance(app->Discovery);
            SpecDefinitionBlocks::GetGlobalInstance().EvaluateBlocks();
            Print("RUN!");
            app->Run();
            return 0;
        }
    };
}