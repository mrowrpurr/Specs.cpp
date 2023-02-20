#pragma once

#include "Specs/Application.h"
#include "Specs/Reporters/DebugReporter.h"
#include "Specs/Reporters/DocumentationReporter.h"
#include "Specs/Reporters/OneLineReporter.h"
#include "Specs/Runners/ParallelRunner.h"
#include "Specs/Runners/QueueRunner.h"
#include "Specs/Runners/TreeRunner.h"

namespace Specs {

    //! Represents the configuration options for the application.
    class CommandLineOptions {
        std::unordered_map<std::string, std::function<void(std::shared_ptr<Application>)>> _availableRunnerOptions;
        std::unordered_map<std::string, std::function<void(std::shared_ptr<Application>)>> _availableReporterOptions;

    public:
        //! Gets the singleton instance of the configuration options.
        /**
         * This is where you should register available Runner and Reporter options.
         */
        static CommandLineOptions& GetSingleton() {
            static CommandLineOptions globalInstance = GetDefaultCommandLineOptions();
            return globalInstance;
        }

        //! Gets a CommandLineOptions configured with the default options provided by `Specs.cpp`.
        static CommandLineOptions GetDefaultCommandLineOptions() {
            CommandLineOptions options;

            options.AddRunnerOption("tree", [](std::shared_ptr<Application> app) {
                app->SetRunner<Runners::TreeRunner>();
            });
            options.AddRunnerOption("queue", [](std::shared_ptr<Application> app) {
                app->SetRunner<Runners::QueueRunner>();
            });
            options.AddRunnerOption("parallel", [](std::shared_ptr<Application> app) {
                app->SetRunner<Runners::ParallelRunner>();
            });

            options.AddReporterOption("debug", [](std::shared_ptr<Application> app) {
                app->AddReporter<Reporters::DebugReporter>();
            });
            options.AddReporterOption("oneline", [](std::shared_ptr<Application> app) {
                app->AddReporter<Reporters::OneLineReporter>();
            });
            options.AddReporterOption("documentation", [](std::shared_ptr<Application> app) {
                app->AddReporter<Reporters::DocumentationReporter>();
            });

            return options;
        }

        //! Add a Runner option to the configuration options.
        /**
         * Should add an ISpecRunner of a specified type to the application.
         */
        void AddRunnerOption(std::string name, std::function<void(std::shared_ptr<Application>)> option) {
            _availableRunnerOptions[name] = option;
        }

        //! Add a Reporter option to the configuration options.
        /**
         * Should add an ISpecReporter of a specified type to the application.
         */
        void AddReporterOption(std::string name, std::function<void(std::shared_ptr<Application>)> option) {
            _availableReporterOptions[name] = option;
        }

        //! Returns true if the specified Runner option exists.
        bool HasRunnerOption(std::string name) { return _availableRunnerOptions.contains(name); }

        //! Returns true if the specified Reporter option exists.
        bool HasReporterOption(std::string name) { return _availableReporterOptions.contains(name); }

        //! Applies the specified Runner option to the Application.
        void ApplyRunnerOption(std::string name, std::shared_ptr<Application> app) {
            if (HasRunnerOption(name)) _availableRunnerOptions[name](app);
        }

        //! Applies the specified Reporter option to the Application.
        void ApplyReporterOption(std::string name, std::shared_ptr<Application> app) {
            if (HasReporterOption(name)) _availableReporterOptions[name](app);
        }
    };
}