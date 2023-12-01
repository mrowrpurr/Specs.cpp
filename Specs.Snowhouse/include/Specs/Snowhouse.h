#pragma once

#if __has_include(<snowhouse/snowhouse.h>)
    #include <Specs/DSLs.h>  // IWYU pragma: keep

    #include "SnowhouseExceptionHandler.h"  // IWYU pragma: keep
    #include "SnowhouseIncludes.h"          // IWYU pragma: keep

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
#endif
