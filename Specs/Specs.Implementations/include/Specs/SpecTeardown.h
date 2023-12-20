#pragma once

#include <Specs/API.h>

#include "SpecComponent.h"
#include "SpecHasCodeBlock.h"

namespace SpecsCpp {

    class SpecTeardown : public ISpecTeardown, public SpecComponent, public SpecHasCodeBlock {
    public:
        SpecTeardown(ISpecGroup* parent, std::unique_ptr<SpecCodeBlock> codeBlock)
            : SpecComponent(SpecComponentType::Teardown, parent),
              SpecHasCodeBlock(std::move(codeBlock)) {}
    };
}
