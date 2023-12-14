#pragma once

#include <Specs/GlobalSpecGroup.h>

inline void use_template(std::string_view templateName) {
    SpecsCpp::GlobalSpecGroup::instance().use_template(templateName);
}
