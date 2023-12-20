#pragma once

#include <Specs/API.h>

#include "SpecComponent.h"
#include "SpecHasCodeBlock.h"

namespace SpecsCpp {

    class SpecSetup : public ISpecSetup, public SpecComponent, public SpecHasCodeBlock {
    public:
        SpecSetup(ISpecGroup* parent, std::unique_ptr<SpecCodeBlock> codeBlock)
            : SpecComponent(SpecComponentType::Setup, parent),
              SpecHasCodeBlock(std::move(codeBlock)) {}
    };
}
