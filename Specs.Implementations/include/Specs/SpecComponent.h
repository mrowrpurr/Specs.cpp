#pragma once

#include <Specs/API.h>

#include "SpecKeyValueCollection.h"

namespace SpecsCpp {

    class SpecComponent : public virtual ISpecComponent {
        bool                     _skip = false;
        SpecComponentType        _type;
        ISpecGroup*              _parentGroup;
        SpecKeyValueCollection   _metaData;
        ISpecKeyValueCollection* _metaDataPtr = &_metaData;

    public:
        SpecComponent(SpecComponentType type, ISpecGroup* parentGroup, bool skip = false)
            : _type(type), _parentGroup(parentGroup), _skip(skip) {}

        ISpecGroup*              group() const override { return _parentGroup; }
        ISpecKeyValueCollection* meta_data() const override { return _metaDataPtr; }
        SpecComponentType        type() const override { return _type; }
        bool                     skip() const override { return _skip; }
        void                     mark_skipped(bool skip = true) override { _skip = skip; }
    };
}
