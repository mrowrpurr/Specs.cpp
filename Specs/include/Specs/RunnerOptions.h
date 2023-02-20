#pragma once

#include <string>
#include <vector>

namespace Specs {

    //! Represents the configuration options for runners.
    class RunnerOptions {
        std::vector<std::string> _filters;

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
    };
}
