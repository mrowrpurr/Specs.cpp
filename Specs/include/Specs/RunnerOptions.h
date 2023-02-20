#pragma once

#include <string>
#include <vector>

namespace Specs {

    //! Represents the configuration options for runners.
    class RunnerOptions {
        std::vector<std::string> _filters;
        bool                     _randomizeTestOrder       = false;
        bool                     _parallelizeTestExecution = false;

    public:
        //! Creates a new runner options.
        RunnerOptions() = default;

        //! Gets the filters.
        const std::vector<std::string>& GetFilters() const { return _filters; }

        //! Adds a filter.
        void AddFilter(const std::string& filter) {
            _filters.push_back(filter);
            Print("Added filter: {}", filter);
        }

        //! Gets whether to randomize the test order.
        bool GetRandomizeTestOrder() const { return _randomizeTestOrder; }

        //! Sets whether to randomize the test order.
        void SetRandomizeTestOrder(bool randomizeTestOrder) { _randomizeTestOrder = randomizeTestOrder; }

        //! Gets whether to parallelize the test execution.
        bool GetParallelizeTestExecution() const { return _parallelizeTestExecution; }

        //! Sets whether to parallelize the test execution.
        void SetParallelizeTestExecution(bool parallelizeTestExecution) {
            _parallelizeTestExecution = parallelizeTestExecution;
        }
    };
}
