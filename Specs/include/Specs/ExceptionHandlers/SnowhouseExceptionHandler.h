#pragma once

#include <snowhouse/snowhouse.h>
#include <string_format.h>

#include <exception>
#include <filesystem>
#include <fstream>
#include <optional>
#include <sstream>

#include "../ISpecExceptionHandler.h"
#include "../SpecTestCaseResult.h"

namespace Specs::ExceptionHandlers {

    //! Exception handler for assertions provided by the `Snowhouse` library.
    class SnowhouseExceptionHandler : public ISpecExceptionHandler {
        std::optional<std::filesystem::path> WalkUpToFindFilePath(const std::string& path) {
            // Given the provided path,
            // return it if it exists.
            //
            // Else, walk up parent folders and return the first one that exists.
            if (std::filesystem::exists(path)) return path;

            std::filesystem::path currentPath = std::filesystem::current_path();
            if (std::filesystem::exists(currentPath / path)) return currentPath / path;

            while (currentPath.has_parent_path()) {
                currentPath = currentPath.parent_path();
                if (std::filesystem::exists(currentPath / path)) return currentPath / path;
            }

            return std::nullopt;
        }

        std::string ReadLineFromFile(const std::string& filename, unsigned int linenumber) {
            auto path = WalkUpToFindFilePath(filename);
            if (!path.has_value()) return "";

            std::ifstream file(path.value());
            if (!file.is_open()) return "";

            std::string  line;
            unsigned int currentLineNumber = 0;
            while (std::getline(file, line)) {
                currentLineNumber++;
                if (currentLineNumber == linenumber) {
                    // trim whitespace from front of line and then return it
                    line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](int ch) {
                                   return !std::isspace(ch);
                               }));
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
                    string_format("\n{}{}\n[{}:{}]", e.what(), ReadLineFromFile(e.file(), e.line()), e.file(), e.line())
                );
                return true;
            } catch (...) {
                return false;
            }
        }
    };
}
