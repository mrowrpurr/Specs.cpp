#pragma once

#include <functional>

namespace Spec::Types {

    //! Stores arbitrary functions which define specs when invoked.
    class SpecDefinitionBlocks {
        std::vector<std::function<void()>> _blocks;

    public:
        static SpecDefinitionBlocks& GetGlobalInstance() {
            static SpecDefinitionBlocks instance;
            return instance;
        }

        void RegisterBlock(std::function<void()> block) { _blocks.push_back(block); }

        void EvaluateBlocks() {
            for (auto& block : _blocks) block();
        }
    };
}
