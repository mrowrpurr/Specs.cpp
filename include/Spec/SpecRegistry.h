#pragma once

#include "Spec/SpecGroup.h"

namespace Spec {

    //! Stores groups of specs
    class SpecRegistry {
        std::shared_ptr<SpecGroup> _rootSpecGroup;

    public:
        SpecRegistry() : _rootSpecGroup(std::make_shared<SpecGroup>()) {}

        /** Spec groups are stored as a tree and this is the root node */
        std::shared_ptr<SpecGroup> GetRoot() { return _rootSpecGroup; }
    };
}
