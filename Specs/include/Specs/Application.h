#pragma once

#include <memory>
#include <vector>

#include "Specs/ISpecExceptionHandler.h"
#include "Specs/ISpecReporter.h"
#include "Specs/ISpecRunner.h"
#include "Specs/SpecRegistry.h"

namespace Specs {

    //! Represents an application capable of running test suites and generating results.
    class Application {
        std::shared_ptr<SpecRegistry>                       _registry;
        std::vector<std::shared_ptr<ISpecReporter>>         _reporters;
        std::vector<std::shared_ptr<ISpecExceptionHandler>> _exceptionHandlers;
        std::shared_ptr<ISpecRunner>                        _runner;

    public:
        //! Creates a new application.
        Application() : _registry(std::make_shared<SpecRegistry>()) {}

        //! Gets the registry for this application.
        std::shared_ptr<SpecRegistry> GetRegistry() { return _registry; }

        //! Gets the runner for this application.
        std::shared_ptr<ISpecRunner> GetRunner() { return _runner; }

        //! Sets the runner for this application.
        void SetRunner(std::shared_ptr<ISpecRunner> runner) { _runner = runner; }

        //! Sets the runner of the specified type for this application.
        template <typename T>
        void SetRunner() {
            SetRunner(std::make_shared<T>());
        }

        //! Adds a reporter to the application.
        void AddReporter(std::shared_ptr<ISpecReporter> reporter) { _reporters.push_back(reporter); }

        //! Adds a reporter of the specified type to the application.
        template <typename T>
        void AddReporter() {
            AddReporter(std::make_shared<T>());
        }

        //! Gets the reporters for this application.
        std::vector<std::shared_ptr<ISpecReporter>>& GetReporters() { return _reporters; }

        //! Adds an exception handler to the application.
        void AddExceptionHandler(std::shared_ptr<ISpecExceptionHandler> exceptionHandler) {
            _exceptionHandlers.push_back(exceptionHandler);
        }

        //! Gets the exception handlers for this application.
        std::vector<std::shared_ptr<ISpecExceptionHandler>>& GetExceptionHandlers() { return _exceptionHandlers; }

        //! Runs the application.
        int Run() {
            // if (_runner == nullptr) {
            //     throw std::runtime_error("No runner has been set.");
            // }
            // return _runner->Run(_registry, _reporters, _exceptionHandlers);
            return 0;
        }

        //! TODO: Run the application with command line arguments.
        int Run(int argc, char* argv[]) { return Run(); }
    };
}
