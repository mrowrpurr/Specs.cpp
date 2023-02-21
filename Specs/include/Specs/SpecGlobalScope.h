#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "Specs/SpecTestGroup.h"

namespace Specs {

    //! Managed everything in the global scope of a `Specs.cpp` application.
    class SpecGlobalScope {
        std::shared_ptr<SpecTestGroup>     _testGroup;
        std::vector<std::function<void()>> _codeBlocks;

        SpecGlobalScope()                                  = default;
        ~SpecGlobalScope()                                 = default;
        SpecGlobalScope(const SpecGlobalScope&)            = delete;
        SpecGlobalScope(SpecGlobalScope&&)                 = delete;
        SpecGlobalScope& operator=(const SpecGlobalScope&) = delete;
        SpecGlobalScope& operator=(SpecGlobalScope&&)      = delete;

    public:
        //! Gets the singleton instance of the global scope.
        static SpecGlobalScope& Get() {
            static SpecGlobalScope singleton;
            return singleton;
        }

        //! Gets the global test group.
        std::shared_ptr<SpecTestGroup> GetGlobalGroup() { return _testGroup; }

        //! Sets the global test group.
        void SetGlobalGroup(std::shared_ptr<SpecTestGroup> testGroup) { _testGroup = testGroup; }

        //! Registers a code block.
        void RegisterCodeBlock(std::function<void()> codeBlock) { _codeBlocks.push_back(codeBlock); }

        //! Runs all registered code blocks using the provided test group as the global test group.
        void RunCodeBlocksUsingGroup(std::shared_ptr<SpecTestGroup> testGroup) {
            auto previousTestGroup = _testGroup;
            _testGroup             = testGroup;
            for (auto& codeBlock : _codeBlocks) codeBlock();
            _testGroup = previousTestGroup;
        }
    };
}