#pragma once

#include <Specs/ExceptionHandlers/CStringExceptionHandler.h>
#include <Specs/ExceptionHandlers/StdExceptionExceptionHandler.h>
#include <Specs/GlobalSpecCodeBlocks.h>
#include <Specs/GlobalSpecEnvironment.h>
#include <Specs/GlobalSpecGroup.h>
#include <Specs/LibraryLoader.h>
#include <Specs/SpecDataValue.h>
#include <Specs/SpecDataValueCollection.h>
#include <Specs/SpecDebugReporter.h>
#include <Specs/SpecEnvironment.h>
#include <Specs/SpecReporterCollection.h>
#include <Specs/SpecSerialRunner.h>
#include <_Log_.h>

#include <cxxopts.hpp>
#include <filesystem>

namespace SpecsCpp {

    class Entrypoint {
        int _returnCode = 0;
        int _totalTests = 0;

        SpecEnvironment         _specs;
        SpecSerialRunner        _runner;
        SpecDebugReporter       _reporter;
        SpecReporterCollection  _reporters;
        SpecDataValueCollection _runnerOptions;
        LibraryLoader           _LibraryLoader{&_specs};

        ExceptionHandlers::CStringExceptionHandler      _cStringExceptionHandler;
        ExceptionHandlers::StdExceptionExceptionHandler _stdExceptionExceptionHandler;

        void on_suite_complete(ISpecSuiteRunResult* result) {
            _returnCode = result->failed() > 0 ? 1 : 0;
            _totalTests =
                result->passed() + result->failed() + result->not_run() + result->timed_out();
        }

        FunctionPointer<void(ISpecSuiteRunResult*)> _onSuiteComplete =
            function_pointer(this, &Entrypoint::on_suite_complete);

    public:
        int main(int argc, char** argv) {
            cxxopts::Options options("Specs.cpp", "Specs.cpp command line options");
            options.allow_unrecognised_options();

            // TODO: option to specify / customize the reporters used
            // TODO: option to specify / customize the runner used
            options.add_options()
                ("n,name", "Filter name of test/group to run", cxxopts::value<std::string>())
                ("s,spec", "Filter name of test to run",  cxxopts::value<std::string>())
                ("g,group", "Filter name of group to run", cxxopts::value<std::string>())
                ("r,pattern", "Regex pattern filter of test/group to run", cxxopts::value<std::string>())
                ("spec-pattern", "Regex pattern filter of test to run", cxxopts::value<std::string>())
                ("group-pattern", "Regex pattern filter of group to run", cxxopts::value<std::string>())
                ("l,list", "List all tests and groups", cxxopts::value<bool>()->default_value("false"))
                ("dll,so", "Load tests from shared library (--dll,--so)", cxxopts::value<std::vector<std::string>>())
                ("t,timeout", "Timeout in milliseconds for each test", cxxopts::value<int>())
                ("h,help", "Print usage");

            auto result = options.parse(argc, argv);
            if (result.count("help")) {
                _Log_(options.help());
                return 0;
            }

            if (result.count("name"))
                _runnerOptions.add(SpecDataValue::create_string(
                    ISpecRunner::DESCRIPTION_FILTER_OPTION_KEY,
                    result["name"].as<std::string>().c_str()
                ));
            if (result.count("spec"))
                _runnerOptions.add(SpecDataValue::create_string(
                    ISpecRunner::SPEC_DESCRIPTION_FILTER_OPTION_KEY,
                    result["spec"].as<std::string>().c_str()
                ));
            if (result.count("group"))
                _runnerOptions.add(SpecDataValue::create_string(
                    ISpecRunner::GROUP_DESCRIPTION_FILTER_OPTION_KEY,
                    result["group"].as<std::string>().c_str()
                ));
            if (result.count("pattern"))
                _runnerOptions.add(SpecDataValue::create_string(
                    ISpecRunner::DESCRIPTION_REGEX_FILTER_OPTION_KEY,
                    result["pattern"].as<std::string>().c_str()
                ));
            if (result.count("spec-pattern"))
                _runnerOptions.add(SpecDataValue::create_string(
                    ISpecRunner::SPEC_DESCRIPTION_REGEX_FILTER_OPTION_KEY,
                    result["spec-pattern"].as<std::string>().c_str()
                ));
            if (result.count("group-pattern"))
                _runnerOptions.add(SpecDataValue::create_string(
                    ISpecRunner::GROUP_DESCRIPTION_REGEX_FILTER_OPTION_KEY,
                    result["group-pattern"].as<std::string>().c_str()
                ));
            if (result.count("list"))
                _runnerOptions.add(SpecDataValue::create_bool(
                    ISpecRunner::LIST_TEST_NAMES_OPTION_KEY, result["list"].as<bool>()
                ));
            if (result.count("timeout"))
                _runnerOptions.add(SpecDataValue::create_int(
                    ISpecRunner::DEFAULT_TIMEOUT_MS_OPTION_KEY, result["timeout"].as<int>()
                ));

            if (result.unmatched().size() > 0) {
                _Log_("Unrecognized options:");
                for (auto& option : result.unmatched()) _Log_(option);
                return 1;
            }

            global_spec_environment().set(&_specs);
            _specs.root_group()->merge(GlobalSpecGroup::instance().root());
            _specs.local_exception_handlers()->register_exception_handler(&_cStringExceptionHandler
            );
            _specs.local_exception_handlers()->register_exception_handler(
                &_stdExceptionExceptionHandler
            );
            GlobalSpecCodeBlocks::instance().run_code_blocks();

            if (result.count("dll")) {
                for (auto& dll : result["dll"].as<std::vector<std::string>>()) {
                    if (!std::filesystem::exists(dll)) {
                        _Log_("Specs.cpp: Error: Spec dll/so file not found: " + dll);
                        return 1;
                    }
                    if (auto* dllRootSpecGroup = _LibraryLoader.load(dll)) {
                        _specs.root_group()->merge(dllRootSpecGroup);
                    } else {
                        _Log_("Specs.cpp: Error: Failed to load group from dll/so file: " + dll);
                        return 1;
                    }
                }
            }

            _reporters.add("debug", &_reporter);
            _runner.run(_specs.root_group(), &_reporters, &_runnerOptions, &_onSuiteComplete);

            if (_totalTests == 0) {
                _Log_("No tests found.\n");
                _Log_(options.help());
                return 1;
            }

            return _returnCode;
        }
    };
}
