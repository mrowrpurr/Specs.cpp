#pragma once

#include <Specs/API.h>
#include <Specs/SpecRunResult.h>
#include <Specs/SpecSuiteRunResult.h>
#include <_Log_.h>
#include <collections.h>

#include <future>
#include <memory>
#include <regex>
#include <string>

namespace SpecsCpp {

    // TODO: separate a bunch of common code into a SpecRunner class
    // which the parallel runner will also inherit from :)
    //
    // Also: perhaps go ahead and build a full list of all specs to be
    // run before running any of them, so we can print out a summary BEFORE running
    // and also this lets us do randomization :)

    class SpecSerialRunner : public ISpecRunner {
        class SpecSuiteRunInstance {
            SpecSuiteRunResult       _resultTotalCounts;
            ISpecReporterCollection* _reporters;
            ISpecKeyValueCollection* _options = nullptr;

            int _timeoutMs = 0;

            int                                            _setupGroupsRun          = 0;
            std::unique_ptr<std::promise<ISpecRunResult*>> _currentRunResultPromise = nullptr;
            ISpec*                                         _currentSpec             = nullptr;
            bool                                           _currentSpecFailed       = false;
            std::unique_ptr<ISpecRunResult>                _currentResult           = nullptr;
            std::string                                    _currentSpecFailureMessage;

            inline const char* filter_text() const {
                if (!_options) return nullptr;
                return _options->get(DESCRIPTION_FILTER_OPTION_KEY);
            }
            inline const char* group_filter_text() const {
                if (!_options) return nullptr;
                return _options->get(GROUP_DESCRIPTION_FILTER_OPTION_KEY);
            }
            inline const char* spec_filter_text() const {
                if (!_options) return nullptr;
                return _options->get(SPEC_DESCRIPTION_FILTER_OPTION_KEY);
            }
            inline const char* regex_filter_text() const {
                if (!_options) return nullptr;
                return _options->get(DESCRIPTION_REGEX_FILTER_OPTION_KEY);
            }
            inline const char* group_regex_filter_text() const {
                if (!_options) return nullptr;
                return _options->get(GROUP_DESCRIPTION_REGEX_FILTER_OPTION_KEY);
            }
            inline const char* spec_regex_filter_text() const {
                if (!_options) return nullptr;
                return _options->get(SPEC_DESCRIPTION_REGEX_FILTER_OPTION_KEY);
            }
            inline bool list_only() const {
                if (!_options) return false;
                return _options->has(LIST_TEST_NAMES_OPTION_KEY);
            }

            inline bool description_matches(const char* description, const char* filter) {
                if (!filter || !description) return false;
                bool result = strstr(description, filter) != nullptr;
                return strstr(description, filter) != nullptr;
            }

            inline bool regex_description_matches(const char* description, const char* filter) {
                if (!filter || !description) return false;
                return std::regex_search(description, std::regex(filter));
            }

            inline bool should_run_group(ISpecGroup* group) {
                // Always run root group (which has empty string as description)
                if (strlen(group->description()) == 0) return true;

                if (group->skip()) return false;
                if (group->meta_data()->has("skip")) return false;
                if (description_matches(group->full_description(), filter_text())) return true;
                if (description_matches(group->description(), group_filter_text())) return true;
                if (regex_description_matches(group->full_description(), regex_filter_text()))
                    return true;
                if (regex_description_matches(group->description(), group_regex_filter_text()))
                    return true;
                return (
                    filter_text() == nullptr && group_filter_text() == nullptr &&
                    regex_filter_text() == nullptr && group_regex_filter_text() == nullptr
                );
            }

            inline bool should_run_spec(ISpec* spec) {
                if (spec->skip()) return false;
                if (spec->meta_data()->has("skip")) return false;
                if (description_matches(spec->full_description(), filter_text())) return true;
                if (description_matches(spec->description(), spec_filter_text())) return true;
                if (regex_description_matches(spec->full_description(), regex_filter_text()))
                    return true;
                if (regex_description_matches(spec->description(), spec_regex_filter_text()))
                    return true;
                return (
                    filter_text() == nullptr && spec_filter_text() == nullptr &&
                    regex_filter_text() == nullptr && spec_regex_filter_text() == nullptr
                );
            }

            void code_block_callback_fn(ISpecRunResult* result) {
                if (result->status() == RunResultStatus::Failed ||
                    result->status() == RunResultStatus::Timeout) {
                    _currentSpecFailed         = true;
                    _currentSpecFailureMessage = result->message();
                }
                _currentResult = std::unique_ptr<ISpecRunResult>(result->copy());
                _currentRunResultPromise->set_value(_currentResult.get());
            }

            FunctionPointer<void(ISpecRunResult*)> _codeBlockCallbackFn{
                this, &SpecSuiteRunInstance::code_block_callback_fn
            };

            void foreach_setup_in_group(ISpecSetup* setup) {
                if (_currentSpecFailed) {
                    auto result = SpecRunResult::not_run(setup, _currentSpec);
                    _reporters->report_setup(result.get());
                    return;
                }

                _currentRunResultPromise = std::make_unique<std::promise<ISpecRunResult*>>();

                auto* codeBlock = setup->code_block();
                codeBlock->set_timeout_ms(_timeoutMs);

                codeBlock->run(setup, _currentSpec, &_codeBlockCallbackFn);

                auto future = _currentRunResultPromise->get_future();
                if (_timeoutMs > 0) {
                    if (future.wait_for(std::chrono::milliseconds(_timeoutMs)) ==
                        std::future_status::timeout) {
                        auto result = SpecRunResult::timeout(setup, _currentSpec);
                        _reporters->report_setup(result.get());
                        _currentSpecFailed = true;
                        return;
                    }
                }

                if (auto* result = future.get()) _reporters->report_setup(result);
                else _Log_("Setup callback future.get() returned nullptr");
            }

            FunctionPointer<void(ISpecSetup*)> _forEachSetupInGroupFn{
                this, &SpecSuiteRunInstance::foreach_setup_in_group
            };

            void foreach_teardown_in_group(ISpecTeardown* teardown) {
                _currentRunResultPromise = std::make_unique<std::promise<ISpecRunResult*>>();

                auto* codeBlock = teardown->code_block();
                codeBlock->set_timeout_ms(_timeoutMs);

                codeBlock->run(teardown, _currentSpec, &_codeBlockCallbackFn);

                auto future = _currentRunResultPromise->get_future();
                if (_timeoutMs > 0) {
                    if (future.wait_for(std::chrono::milliseconds(_timeoutMs)) ==
                        std::future_status::timeout) {
                        auto result = SpecRunResult::timeout(teardown, _currentSpec);
                        _reporters->report_teardown(result.get());
                        _currentSpecFailed = true;
                        return;
                    }
                }

                if (auto* result = future.get()) _reporters->report_teardown(result);
                else _Log_("Teardown callback future.get() returned nullptr");
            }

            FunctionPointer<void(ISpecTeardown*)> _forEachTeardownInGroupFn{
                this, &SpecSuiteRunInstance::foreach_teardown_in_group
            };

            void foreach_spec_in_group(ISpec* spec) {
                if (!should_run_spec(spec)) return;

                if (list_only()) {
                    auto result = SpecRunResult::not_run(spec, spec);
                    _reporters->report_spec_result(result.get());
                    return;
                }

                _currentSpec       = spec;
                _currentSpecFailed = false;
                _currentResult     = nullptr;

                _reporters->report_spec_begin(_currentSpec);

                std::vector<ISpecGroup*> groupStack;
                auto*                    currentGroup = spec->group();
                while (currentGroup) {
                    groupStack.push_back(currentGroup);
                    currentGroup = currentGroup->group();
                }

                // Run foreach blocks, starting with root parent
                for (auto it = groupStack.rbegin(); it != groupStack.rend(); ++it) {
                    auto* group = *it;
                    group->foreach_setup(&_forEachSetupInGroupFn);
                    if (!_currentSpecFailed) _setupGroupsRun++;
                }

                if (_currentSpecFailed) {
                    auto specCodeResult = SpecRunResult::not_run(spec, spec);
                    _reporters->report_spec(specCodeResult.get());

                    if (_currentResult && _currentResult->status() == RunResultStatus::Timeout) {
                        auto specFinalResult = SpecRunResult::timeout(spec, spec);
                        _reporters->report_spec_result(specFinalResult.get());
                    } else {
                        auto specFinalResult =
                            SpecRunResult::failed(spec, spec, _currentSpecFailureMessage);
                        _reporters->report_spec_result(specFinalResult.get());
                    }

                    _resultTotalCounts.increment_failed();

                    // We still tear things down - but only run the teardown for each group that run
                    // setups
                    int  teardownsToRun = _setupGroupsRun;
                    auto groupCount     = groupStack.size();
                    auto groupsToSkip   = groupCount - teardownsToRun;

                    // Run teardowns, but skip the first X ones, where X is the number of groups
                    // that ran setups
                    for (int i = 0; i < groupCount; i++) {
                        if (i < groupsToSkip - 1) continue;
                        auto* group = groupStack[i];
                        group->foreach_teardown(&_forEachTeardownInGroupFn);
                    }

                    spec->variables()->clear();
                    return;
                }

                _currentRunResultPromise = std::make_unique<std::promise<ISpecRunResult*>>();

                auto* codeBlock = spec->code_block();
                codeBlock->set_timeout_ms(_timeoutMs);

                codeBlock->run(spec, spec, &_codeBlockCallbackFn);

                auto future = _currentRunResultPromise->get_future();

                if (_timeoutMs > 0) {
                    if (future.wait_for(std::chrono::milliseconds(_timeoutMs)) ==
                        std::future_status::timeout) {
                        auto result = SpecRunResult::timeout(spec, spec);
                        _reporters->report_spec(result.get());
                        auto specFinalResult = SpecRunResult::failed(spec, spec);
                        _reporters->report_spec_result(specFinalResult.get());
                        _resultTotalCounts.increment_failed();
                        spec->variables()->clear();
                        return;
                    }
                }

                if (auto* result = future.get()) _reporters->report_spec(result);
                else _Log_("Spec callback future.get() returned nullptr");

                // Run teardown blocks, starting with current and walking up to root parent
                for (auto* group : groupStack) group->foreach_teardown(&_forEachTeardownInGroupFn);

                if (_currentSpecFailed) {
                    _resultTotalCounts.increment_failed();
                    auto specFinalResult =
                        SpecRunResult::failed(spec, spec, _currentSpecFailureMessage);
                    _reporters->report_spec_result(specFinalResult.get());
                } else {
                    _resultTotalCounts.increment_passed();
                    auto specFinalResult = SpecRunResult::passed(spec, spec);
                    _reporters->report_spec_result(specFinalResult.get());
                }
                spec->variables()->clear();
            }

            FunctionPointer<void(ISpec*)> _forEachSpecInGroupFn{
                this, &SpecSuiteRunInstance::foreach_spec_in_group
            };

            void foreach_group_in_group(ISpecGroup* group) {
                // TODO group these into an inline function:
                _currentSpec       = nullptr;
                _currentSpecFailed = false;
                _currentSpecFailureMessage.clear();
                _currentResult = nullptr;

                // Run the group's one time setups
                group->foreach_one_time_setup(&_forEachSetupInGroupFn);

                group->foreach_spec(&_forEachSpecInGroupFn);
                group->foreach_group(&_forEachGroupInGroupFn);

                // Run the group's one time teardowns
                group->foreach_one_time_teardown(&_forEachTeardownInGroupFn);

                group->variables()->clear();
            }

            FunctionPointer<void(ISpecGroup*)> _forEachGroupInGroupFn{
                this, &SpecSuiteRunInstance::foreach_group_in_group
            };

            void run_group(ISpecGroup* group) {
                if (should_run_group(group)) {
                    // TODO group these into an inline function:
                    _currentSpec       = nullptr;
                    _currentSpecFailed = false;
                    _currentSpecFailureMessage.clear();
                    _currentResult = nullptr;

                    // Run the group's one time setups
                    group->foreach_one_time_setup(&_forEachSetupInGroupFn);

                    // Run the specs
                    group->foreach_spec(&_forEachSpecInGroupFn);

                    // Run any child groups
                    group->foreach_group(&_forEachGroupInGroupFn);

                    // Run the group's one time teardowns
                    group->foreach_one_time_teardown(&_forEachTeardownInGroupFn);
                }
            }

        public:
            SpecSuiteRunInstance(
                ISpecReporterCollection* reporters, ISpecKeyValueCollection* options,
                int timeoutMs = 5000
            )
                : _reporters(reporters), _options(options), _timeoutMs(timeoutMs) {}

            void run(ISpecGroup* group, ISpecSuiteRunResultCallbackFn* callback) {
                // TODO : put all of the specs into a Queue and we can call report_suite_begin()
                // with count

                run_group(group);
                _reporters->report_suite_result(&_resultTotalCounts);
                if (callback) callback->invoke(&_resultTotalCounts);
            }
        };

    public:
        void run(
            ISpecGroup* group, ISpecReporterCollection* reporters, ISpecKeyValueCollection* options,
            ISpecSuiteRunResultCallbackFn* callback
        ) override {
            if (options && options->has(DEFAULT_TIMEOUT_MS_OPTION_KEY)) {
                int timeoutMs = std::stoi(options->get(DEFAULT_TIMEOUT_MS_OPTION_KEY));
                _Log_("Configured timeout milliseconds: {}", timeoutMs);
                SpecSuiteRunInstance(reporters, options, timeoutMs).run(group, callback);
            } else {
                SpecSuiteRunInstance(reporters, options).run(group, callback);
            }
        }
    };
}
