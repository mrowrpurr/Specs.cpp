#pragma once

#include <Specs/API.h>
#include <_Log_.h>

namespace SpecsCpp {

    class SpecApplication : public Interfaces::ISpecApplication {
        ISpecEnvironment*                 _environment;
        ISpecCommandLineOptionCollection* _cli_options;

    public:
        int main(int argc, char** argv) override {
            if (!_environment) {
                _Log_("SpecApplication::main() called without an environment set");
                return 1;
            }

            return 0;
        }

        int main() override { return main(0, nullptr); }

        ISpecCommandLineOptionCollection* cli_options() const override { return _cli_options; }
        void set_cli_option_collection(ISpecCommandLineOptionCollection* options) override {
            _cli_options = options;
        }

        ISpecEnvironment* environment() const override { return _environment; }
        void set_environment(ISpecEnvironment* environment) override { _environment = environment; }
    };
}
