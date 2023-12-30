#pragma once

#include <Specs/API.h>

#include <memory>
#include <string>
#include <string_view>

namespace SpecsCpp {

    class SpecRunResult : public ISpecRunResult {
        RunResultStatus _status  = RunResultStatus::NotRun;
        std::string     _message = "";
        ISpecComponent* _component;
        ISpec*          _spec;
        ISpecGroup*     _group;

    public:
        SpecRunResult(
            ISpecComponent* component, ISpecGroup* group, ISpec* spec, RunResultStatus status,
            std::string_view message = ""
        )
            : _component(component),
              _group(group),
              _spec(spec),
              _status(status),
              _message(message) {}

        RunResultStatus status() const override { return _status; }
        const char*     message() const override { return _message.c_str(); }
        ISpecComponent* component() const override { return _component; }
        ISpec*          spec() const override { return _spec; }
        ISpecGroup*     group() const override { return _group; }

        ISpecRunResult* copy() const override {
            return new SpecRunResult(_component, _group, _spec, _status, _message);
        }

        inline static std::unique_ptr<SpecRunResult> passed(
            ISpecComponent* component, ISpecGroup* group, ISpec* spec
        ) {
            return std::make_unique<SpecRunResult>(component, group, spec, RunResultStatus::Passed);
        }

        inline static std::unique_ptr<SpecRunResult> failed(
            ISpecComponent* component, ISpecGroup* group, ISpec* spec, std::string_view message = ""
        ) {
            return std::make_unique<SpecRunResult>(
                component, group, spec, RunResultStatus::Failed, message
            );
        }

        inline static std::unique_ptr<SpecRunResult> not_run(
            ISpecComponent* component, ISpecGroup* group, ISpec* spec
        ) {
            return std::make_unique<SpecRunResult>(component, group, spec, RunResultStatus::NotRun);
        }

        inline static std::unique_ptr<SpecRunResult> timeout(
            ISpecComponent* component, ISpecGroup* group, ISpec* spec
        ) {
            return std::make_unique<SpecRunResult>(
                component, group, spec, RunResultStatus::Timeout, "Timeout"
            );
        }
    };
}
