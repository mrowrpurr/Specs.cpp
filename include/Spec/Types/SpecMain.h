#pragma once

#include "Spec/Types/SpecApp.h"

namespace Spec::Types {
    class SpecMain {
    public:
        static int RunDefault() {
            auto app = SpecApp::GetDefaultInstance();
            app->LoadDefinitionBlocks();
            Print("RUN!");
            app->Run();
            return 0;
        }
    };
}