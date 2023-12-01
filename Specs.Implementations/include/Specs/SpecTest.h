#pragma once

#include <Specs/API.h>
#include <string_format.h>

#include <string>
#include <string_view>

#include "SpecCodeBlock.h"
#include "SpecComponent.h"
#include "SpecDocumented.h"
#include "SpecHasCodeBlock.h"

namespace SpecsCpp {

    class SpecTest : public ISpec,
                     public SpecComponent,
                     public SpecDocumented,
                     public SpecHasCodeBlock {
        std::string _fullDescription;

    public:
        SpecTest(
            ISpecGroup* parent, std::string_view description,
            std::unique_ptr<SpecCodeBlock> codeBlock
        )
            : SpecComponent(SpecComponentType::Spec, parent),
              SpecDocumented(description),
              SpecHasCodeBlock(std::move(codeBlock)) {
            if (parent == nullptr || !parent->full_description()) _fullDescription = description;
            else
                _fullDescription =
                    string_format("{} > {}", parent->full_description(), description);
        }

        const char* full_description() const override {
            return _fullDescription.empty() ? nullptr : _fullDescription.c_str();
        }
    };
}
