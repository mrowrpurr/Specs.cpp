#pragma once

#include <snowhouse/snowhouse.h>
#include <string_format.h>

#include <exception>
#include <filesystem>
#include <fstream>
#include <sstream>

#include "../ISpecExceptionHandler.h"
#include "../SpecTestCaseResult.h"

namespace Specs::ExceptionHandlers {

    //! Exception handler for assertions provided by the `Snowhouse` library.
    class SnowhouseExceptionHandler : public ISpecExceptionHandler {
        std::string ReadLineFromFile(const std::string& filename, unsigned int linenumber) {
            if (!std::filesystem::exists(filename)) return "";

            std::ifstream file(filename);
            if (!file.is_open()) return "";

            std::string  line;
            unsigned int currentLineNumber = 0;
            while (std::getline(file, line)) {
                currentLineNumber++;
                if (currentLineNumber == linenumber) {
                    return line;
                }
            }

            return "";
        }

    public:
        bool HandleException(std::exception_ptr exception, SpecTestCaseResult& testResult) override {
            try {
                std::rethrow_exception(exception);
            } catch (const snowhouse::AssertionException& e) {
                testResult.SetFailureMessage(
                    string_format("[{}:{}] {}\n{}", e.file(), e.line(), e.what(), ReadLineFromFile(e.file(), e.line()))
                );
                return true;
            } catch (...) {
                return false;
            }
        }
    };
}
