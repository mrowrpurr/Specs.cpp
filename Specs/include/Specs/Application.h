#pragma once

#include "DSL/Components/Functions/Print.h"
// constexpr auto Print = [](auto&&... args) { Specs::DSL::Components::Functions::Print(args...); };

#include <memory>
#include <vector>

#include "ISpecExceptionHandler.h"
#include "ISpecReporter.h"
#include "ISpecRunner.h"
#include "ReporterOptions.h"
#include "RunnerOptions.h"
#include "SpecRegistry.h"

namespace Specs {

    //! Represents an application capable of running test suites.
    class Application : public std::enable_shared_from_this<Application> {
        std::shared_ptr<SpecRegistry>                       _registry;
        std::vector<std::shared_ptr<ISpecReporter>>         _reporters;
        std::vector<std::shared_ptr<ISpecExceptionHandler>> _exceptionHandlers;
        std::shared_ptr<ISpecRunner>                        _runner;
        RunnerOptions                                       _runnerOptions;
        ReporterOptions                                     _reporterOptions;

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
            // _exceptionHandlers.push_back(exceptionHandler);
            // Add the exceptionHandler to the front of the vector so that it is the first to be called.
            _exceptionHandlers.insert(_exceptionHandlers.begin(), exceptionHandler);
        }

        //! Adds an exception handler of the specified type to the application.
        template <typename T>
        void AddExceptionHandler() {
            AddExceptionHandler(std::make_shared<T>());
        }

        //! Gets the exception handlers for this application.
        std::vector<std::shared_ptr<ISpecExceptionHandler>>& GetExceptionHandlers() { return _exceptionHandlers; }

        //! Gets the runner options for this application.
        RunnerOptions& GetRunnerOptions() { return _runnerOptions; }

        //! Gets the reporter options for this application.
        ReporterOptions& GetReporterOptions() { return _reporterOptions; }

        //! Runs the application.
        int Run() {
            if (!_runner) throw std::runtime_error("No runner set.");
            auto promise = _runner->RunSpecs(
                _registry->GetRootTestGroup(), _reporters, _exceptionHandlers, _runnerOptions, _reporterOptions
            );
            promise.get_future().wait();
            return 69;  // TODO return 1/0 based on results
        }
    };
}
