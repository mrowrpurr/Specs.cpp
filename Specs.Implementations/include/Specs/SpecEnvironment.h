#pragma once

#include <Specs/API.h>

#include <memory>

#include "LocalSpecExceptionHandlerCollection.h"
#include "SpecGroup.h"
#include "SpecReporterCollection.h"
#include "SpecRunnerCollection.h"

namespace SpecsCpp {

    class SpecEnvironment : public ISpecEnvironment {
        std::unique_ptr<SpecGroup>                           _root_group;
        std::unique_ptr<SpecReporterCollection>              _reporters;
        std::unique_ptr<SpecRunnerCollection>                _runners;
        std::unique_ptr<LocalSpecExceptionHandlerCollection> _local_exception_handlers;

    public:
        SpecEnvironment()
            : _root_group(std::make_unique<SpecGroup>()),
              _reporters(std::make_unique<SpecReporterCollection>()),
              _runners(std::make_unique<SpecRunnerCollection>()),
              _local_exception_handlers(std::make_unique<LocalSpecExceptionHandlerCollection>()) {}

        ISpecGroup* root_group() const override { return _root_group.get(); }

        ILocalSpecExceptionHandlerCollection* local_exception_handlers() const override {
            return _local_exception_handlers.get();
        }

        ISpecRunnerCollection* runners() const override { return _runners.get(); }

        ISpecReporterCollection* reporters() const override { return _reporters.get(); }

        void run(
            ISpecRunner* runner, ISpecReporterCollection* reporters,
            ISpecDataValueCollection* options, ISpecSuiteRunResultCallbackFn* callback
        ) override {
            runner->run(root_group(), reporters, options, callback);
        }
    };
}
