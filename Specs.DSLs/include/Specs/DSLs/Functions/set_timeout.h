#pragma once

#include <Specs/GlobalSpecGroup.h>
#include <Specs/SpecDataValue.h>
#include <Specs/SpecDone.h>

namespace SpecsCpp::DSLs::Functions {

    inline void set_timeout(std::uint32_t timeoutMilliseconds) {
        SpecsCpp::GlobalSpecGroup::instance().add_meta_data_for_next_component(
            SpecDataValue::create("timeout", timeoutMilliseconds)
        );
    }
}
