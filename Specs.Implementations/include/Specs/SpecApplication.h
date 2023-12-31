#pragma once

#include <Specs/API.h>
#include <Specs/SpecCommandLineOptionCollection.h>
#include <Specs/SpecEnvironment.h>
#include <_Log_.h>

#include <memory>

namespace SpecsCpp {

    class SpecApplication : public ISpecApplication {
        std::unique_ptr<ISpecEnvironment>                 _environment;
        std::unique_ptr<ISpecCommandLineOptionCollection> _options;

    public:
        SpecApplication()
            : _environment(std::make_unique<SpecEnvironment>()),
              _options(std::make_unique<SpecCommandLineOptionCollection>()) {}

        int main(int argc, char** argv) override {
            _Log_("ran main() entrypoint");
            return 0;
        }
        int                               main() override { return main(0, nullptr); }
        ISpecCommandLineOptionCollection* options() const override { return _options.get(); }
        ISpecEnvironment* environment() const override { return _environment.get(); }
    };
}
