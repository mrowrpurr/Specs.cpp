#pragma once

#include <Specs/API.h>
#include <_Log_.h>

#include <memory>
#include <string_view>

#include "SpecCommandLineOptionCollection.h"
#include "SpecEnvironment.h"

namespace SpecsCpp {

    class SpecApplication : public ISpecApplication {
        std::unique_ptr<ISpecEnvironment>                 _environment;
        std::unique_ptr<ISpecCommandLineOptionCollection> _options;

    public:
        SpecApplication()
            : _environment(std::make_unique<SpecEnvironment>()),
              _options(std::make_unique<SpecCommandLineOptionCollection>()) {}

        int main(int argc, char** argv) override {
            if (!_environment) {
                _Log_("SpecApplication::main() called without an environment set");
                return 1;
            }

            return 0;
        }

        int main() override { return main(0, nullptr); }

        ISpecCommandLineOptionCollection* options() const override { return _options.get(); }
        ISpecEnvironment* environment() const override { return _environment.get(); }
    };
}
