#pragma once

#include <Specs/GlobalSpecGroup.h>
#include <Specs/SpecDataValue.h>

#include "MacrosCore.h"  // IWYU pragma: keep

#define _SPEC_META_DATA(metaDataKey, metaDataValue)                                          \
    _GLOBAL_MACRO_FUNCTIONS_NEW_NAMED_FUNCTION_RUNNER_VARIABLE_NAME(_SPEC_META_DATA_){[]() { \
        SpecsCpp::GlobalSpecGroup::instance().add_meta_data_for_next_component(              \
            SpecsCpp::SpecDataValue::create(metaDataKey, metaDataValue)                      \
        );                                                                                   \
    }};
