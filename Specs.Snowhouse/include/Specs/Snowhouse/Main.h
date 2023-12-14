#pragma once

#include <Specs/DSLs/TopLevel/Configure.h>
#include <Specs/GlobalSpecEnvironment.h>

#include "SnowhouseExceptionHandler.h"

namespace _Specs_Snowhouse_Configuration {
    inline static auto snowhouseExceptionHandler =
        SpecsCpp::ExceptionHandlers::SnowhouseExceptionHandler();
}

Configure {
    if (auto* specsEnv = SpecsCpp::global_spec_environment().get()) {
        specsEnv->local_exception_handlers()->register_exception_handler(
            &_Specs_Snowhouse_Configuration::snowhouseExceptionHandler
        );
    }
}
