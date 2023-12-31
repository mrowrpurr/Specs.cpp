#pragma once

#include <Specs/API.h>
#include <_Log_.h>

#include <string>
#include <vector>

namespace SpecsCpp::TestHelpers {

    class TestSpecOutput : public ISpecOutput {
        bool                     _log_output;
        std::vector<std::string> _outputs;

    public:
        TestSpecOutput(bool log_output = false) : _log_output(log_output) {}

        void log_output(bool value) { _log_output = value; }

        std::vector<std::string> outputs() const { return _outputs; }
        std::vector<std::string> read_outputs() {
            auto outputs = _outputs;
            _outputs.clear();
            return outputs;
        }

        std::string output() const {
            std::string output;
            for (auto& line : _outputs) {
                output += line;
                output += "\n";
            }
            return output;
        }
        std::string read_output() {
            auto output = this->output();
            _outputs.clear();
            return output;
        }

        void clear() { _outputs.clear(); }

        /* Interface */

        void write(const char* output) override {
            if (_log_output) _Log_(output);
            _outputs.push_back(output);
        }
    };
}
