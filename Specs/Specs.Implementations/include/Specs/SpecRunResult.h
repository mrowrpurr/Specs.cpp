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

    public:
        SpecRunResult(
            ISpecComponent* component, ISpec* spec, RunResultStatus status,
            std::string_view message = ""
        )
            : _component(component), _spec(spec), _status(status), _message(message) {}

        RunResultStatus status() const override { return _status; }
        const char*     message() const override { return _message.c_str(); }
        ISpecComponent* component() const override { return _component; }
        ISpec*          spec() const override { return _spec; }

        ISpecRunResult* copy() const override {
            return new SpecRunResult(_component, _spec, _status, _message);
        }

        inline static std::unique_ptr<SpecRunResult> passed(
            ISpecComponent* component, ISpec* spec
        ) {
            return std::make_unique<SpecRunResult>(component, spec, RunResultStatus::Passed);
        }

        inline static std::unique_ptr<SpecRunResult> failed(
            ISpecComponent* component, ISpec* spec, std::string_view message = ""
        ) {
            return std::make_unique<SpecRunResult>(
                component, spec, RunResultStatus::Failed, message
            );
        }

        inline static std::unique_ptr<SpecRunResult> not_run(
            ISpecComponent* component, ISpec* spec
        ) {
            return std::make_unique<SpecRunResult>(component, spec, RunResultStatus::NotRun);
        }

        inline static std::unique_ptr<SpecRunResult> timeout(
            ISpecComponent* component, ISpec* spec
        ) {
            return std::make_unique<SpecRunResult>(
                component, spec, RunResultStatus::Timeout, "Timeout"
            );
        }
    };
}
