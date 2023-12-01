#pragma once

#include <Specs/API.h>

#include <memory>

#include "SpecCodeBlock.h"

namespace SpecsCpp {

    class SpecHasCodeBlock : public virtual ISpecHasCodeBlock {
        std::unique_ptr<SpecCodeBlock> _codeBlock;

    public:
        SpecHasCodeBlock(std::unique_ptr<SpecCodeBlock> codeBlock)
            : _codeBlock(std::move(codeBlock)) {}

        ISpecCodeBlock* code_block() const override { return _codeBlock.get(); }
    };
}
