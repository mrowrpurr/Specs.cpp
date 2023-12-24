#pragma once

#include <Specs/API.h>

#include "SpecDataValueCollection.h"
#include "SpecTagCollection.h"

namespace SpecsCpp {

    class SpecComponent : public virtual ISpecComponent {
        bool                      _skip = false;
        SpecComponentType         _type;
        ISpecGroup*               _parentGroup;
        SpecDataValueCollection   _metaData;
        ISpecDataValueCollection* _metaDataPtr = &_metaData;
        SpecTagCollection         _tags;
        ISpecTagCollection*       _tagsPtr = &_tags;

    public:
        SpecComponent(SpecComponentType type, ISpecGroup* parentGroup, bool skip = false)
            : _type(type), _parentGroup(parentGroup), _skip(skip) {}

        ISpecGroup*               group() const override { return _parentGroup; }
        ISpecDataValueCollection* data() const override { return _metaDataPtr; }
        ISpecTagCollection*       tags() const override { return _tagsPtr; }
        SpecComponentType         type() const override { return _type; }
        bool                      skip() const override { return _skip; }
        void                      mark_skipped(bool skip = true) override { _skip = skip; }
    };
}
