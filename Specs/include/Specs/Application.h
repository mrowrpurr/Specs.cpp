#pragma once

#include <memory>
#include <vector>

#include "Specs/ExceptionHandlers/DefaultExceptionHandler.h"
#include "Specs/ISpecExceptionHandler.h"
#include "Specs/ISpecReporter.h"
#include "Specs/ISpecRunner.h"
#include "Specs/Reporters/DebugSpecReporter.h"
#include "Specs/Runners/DefaultSpecRunner.h"
#include "Specs/SpecTestGroup.h"

namespace Specs {

    //! Represents an application capable of running test suites and generating results.
    class Application {
        std::shared_ptr<SpecTestGroup>                      _tests;
        std::vector<std::shared_ptr<ISpecReporter>>         _reporters;
        std::vector<std::shared_ptr<ISpecExceptionHandler>> _exceptionHandlers;
        std::shared_ptr<ISpecRunner>                        _runner;

    public:
        //! Gets the root test group for this application.
        std::shared_ptr<SpecTestGroup> GetTests() { return _tests; }

        //! Sets the runner for this application.
        void SetRunner(std::shared_ptr<ISpecRunner> runner) { _runner = runner; }

        //! Gets the runner for this application.
        std::shared_ptr<ISpecRunner> GetRunner() { return _runner; }

        //! Adds a reporter to the application.
        void AddReporter(std::shared_ptr<ISpecReporter> reporter) { _reporters.push_back(reporter); }

        //! Gets the reporters for this application.
        std::vector<std::shared_ptr<ISpecReporter>>& GetReporters() { return _reporters; }

        //! Adds an exception handler to the application.
        void AddExceptionHandler(std::shared_ptr<ISpecExceptionHandler> exceptionHandler) {
            _exceptionHandlers.push_back(exceptionHandler);
        }

        //! Gets the exception handlers for this application.
        std::vector<std::shared_ptr<ISpecExceptionHandler>>& GetExceptionHandlers() { return _exceptionHandlers; }

        //! Runs the application.
        void Run();
    };
}
