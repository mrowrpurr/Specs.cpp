#pragma once

#include <memory>

#include "Specs/Application.h"
#include "Specs/CommandLineOptions.h"

namespace Specs {

    //! Represents a command-line interface for the application.
    class CLI {
        std::shared_ptr<Application>        _app;
        std::shared_ptr<CommandLineOptions> _options;

        //! Sets the runner to use.
        void SetRunner(const std::string& runnerName) {
            if (_options->HasRunnerOption(runnerName))
                _options->ApplyRunnerOption(runnerName, _app);
            else
                throw std::runtime_error("Unknown runner: " + runnerName);
        }

        //! Sets the reporter to use.
        void SetReporter(const std::string& reporterName) {
            if (_options->HasReporterOption(reporterName))
                _options->ApplyReporterOption(reporterName, _app);
            else
                throw std::runtime_error("Unknown reporter: " + reporterName);
        }

        //! Adds a filter for test descriptions.
        void AddFilter(const std::string& filter) { _app->GetRunnerOptions().AddFilter(filter); }

        //! Parses a single argument.
        void ParseArg(std::vector<std::string>& args) {
            auto arg = args[0];
            args.erase(args.begin());
            Print("Parsing argument: " + arg);
            try {
                if (arg == "--runner" || arg == "-u") {
                    if (args.empty()) throw std::runtime_error("Missing runner name.");
                    auto runnerName = args[0];
                    args.erase(args.begin());
                    SetRunner(runnerName);
                } else if (arg == "--reporter" || arg == "-e") {
                    if (args.empty()) throw std::runtime_error("Missing reporter name.");
                    auto reporterName = args[0];
                    args.erase(args.begin());
                    SetReporter(reporterName);
                } else if (arg == "--filter" || arg == "-f") {
                    if (args.empty()) throw std::runtime_error("Missing filter.");
                    auto filter = args[0];
                    args.erase(args.begin());
                    AddFilter(filter);
                } else {
                    throw std::runtime_error("Unknown argument: " + arg);
                }
            } catch (std::exception& e) {
                throw std::runtime_error("Error parsing argument: " + arg + " (" + e.what() + ")");
            } catch (...) {
                throw std::runtime_error("Error parsing argument: " + arg);
            }
        }

    public:
        //! Creates a new CLI with an application.
        CLI()
            : _app(std::make_shared<Application>()),
              _options(std::make_shared<CommandLineOptions>(CommandLineOptions::GetSingleton())) {}

        //! Creates a new CLI from an existing application.
        CLI(std::shared_ptr<Application> app)
            : _app(app), _options(std::make_shared<CommandLineOptions>(CommandLineOptions::GetSingleton())) {}

        //! Creates a new CLI from an existing application and configuration options.
        CLI(std::shared_ptr<Application> app, std::shared_ptr<CommandLineOptions> options)
            : _app(app), _options(options) {}

        //! Parses the command-line arguments.
        bool Parse(std::vector<std::string> args) {
            try {
                while (!args.empty()) ParseArg(args);
                return true;
            } catch (std::exception& e) {
                std::cerr << e.what() << std::endl;
                return false;
            } catch (...) {
                std::cerr << "Unknown error parsing arguments." << std::endl;
                return false;
            }
        }

        //! Parses the command-line arguments.
        bool Parse(int argc, char** argv) {
            std::vector<std::string> args;
            for (int i = 0; i < argc; i++) args.push_back(argv[i]);
            args.erase(args.begin());
            return Parse(args);
        }

        //! Runs the application.
        int Run(int argc, char** argv) {
            try {
                if (!Parse(argc, argv)) return 1;
                return _app->Run();
            } catch (std::exception& e) {
                std::cerr << e.what() << std::endl;
                return 1;
            } catch (...) {
                std::cerr << "Unknown error running application." << std::endl;
                return 1;
            }
        }
    };
}