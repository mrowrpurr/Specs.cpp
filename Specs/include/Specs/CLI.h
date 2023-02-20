#pragma once

#include <memory>

#include "Specs/Application.h"
#include "Specs/ConfigOptions.h"

namespace Specs {

    //! Represents a command-line interface for the application.
    class CLI {
        std::shared_ptr<Application> _app;

    public:
        //! Creates a new CLI with an application.
        CLI() : _app(std::make_shared<Application>()) {}

        //! Creates a new CLI from an existing application.
        CLI(std::shared_ptr<Application> app) : _app(app) {}

        //! Parses the command-line arguments.
        void Parse(int argc, char** argv) {
            //
            Print("How do you spell bubkis?");
        }
    };
}
