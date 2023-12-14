#pragma once

#include <functional>
#include <vector>

namespace SpecsCpp {

    class GlobalSpecCodeBlocks {
        std::vector<std::function<void()>> _codeBlocks;

    public:
        static GlobalSpecCodeBlocks& instance() {
            static GlobalSpecCodeBlocks instance;
            return instance;
        }

        void register_code_block(std::function<void()> codeBlock) {
            _codeBlocks.push_back(std::move(codeBlock));
        }

        void run_code_blocks() {
            for (auto& codeBlock : _codeBlocks) codeBlock();
        }
    };
}
