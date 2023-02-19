#pragma once

#include <functional>
#include <memory>
#include <string>
#include <unordered_map>

#include "Specs/SpecTestGroup.h"

namespace Specs {

    //! Represents the global scope of a library or executable using `Specs.cpp`.
    class SpecGlobalScope {
        std::shared_ptr<SpecTestGroup>                         _globalGroup;
        std::unordered_map<std::string, std::function<void()>> _globalCodeBlocks;

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
        std::shared_ptr<SpecTestGroup> GetGlobalGroup() { return _globalGroup; }

        //! Sets the global test group.
        void SetGlobalGroup(std::shared_ptr<SpecTestGroup> globalGroup) { _globalGroup = globalGroup; }

        //! Gets the global code blocks.
        std::unordered_map<std::string, std::function<void()>>& GetGlobalCodeBlocks() { return _globalCodeBlocks; }

        //! Adds a global code block.
        void AddGlobalCodeBlock(std::string name, std::function<void()> codeBlock) {
            _globalCodeBlocks[name] = codeBlock;
        }
    };
}