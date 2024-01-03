#pragma once

namespace SpecsCpp {
    struct ISpecCommandLineOptionCollection;
    struct ISpecEnvironment;
}

namespace SpecsCpp::Interfaces {

    //! Represents the entry point for a Specs application (to run tests)
    /**
     * Interface for the main entry point of a specs application.
     *
     * The main entry point is responsible for parsing the command line arguments
     * and running the tests.
     */
    struct ISpecApplication {
        virtual ~ISpecApplication() = default;

        virtual int main(int argc, char** argv) = 0;
        virtual int main()                      = 0;

        virtual ISpecCommandLineOptionCollection* cli_options() const             = 0;
        virtual void set_cli_option_collection(ISpecCommandLineOptionCollection*) = 0;

        virtual ISpecEnvironment* environment() const                = 0;
        virtual void              set_environment(ISpecEnvironment*) = 0;
    };
}
