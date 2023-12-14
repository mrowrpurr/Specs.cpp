#pragma once

#include <Specs/GlobalSpecGroup.h>

namespace SpecsCpp::DSLs::Functions {

    inline void use_template(std::string_view templateName) {
        SpecsCpp::GlobalSpecGroup::instance().use_template(templateName);
    }
}
