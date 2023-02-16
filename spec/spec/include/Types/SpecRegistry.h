#pragma once

#include "Spec/SpecGroup.h"

namespace Spec::Types {
    //! Stores a tree of spec groups.
    class SpecRegistry {
        std::shared_ptr<SpecGroup> _rootSpecGroup;

    public:
        SpecRegistry() : _rootSpecGroup(std::make_shared<SpecGroup>("", nullptr)) {}

        std::shared_ptr<SpecGroup> GetRoot() { return _rootSpecGroup; }
        void                       SetRoot(std::shared_ptr<SpecGroup> root) { _rootSpecGroup = root; }
    };
}
