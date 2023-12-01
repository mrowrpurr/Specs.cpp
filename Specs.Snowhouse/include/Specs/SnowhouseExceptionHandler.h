#pragma once

#include <Specs/API.h>
#include <Specs/SpecExceptionMessage.h>
#include <snowhouse/snowhouse.h>
#include <string_format.h>

#include <filesystem>
#include <fstream>
#include <optional>
#include <string>

namespace SpecsCpp::ExceptionHandlers {

    class SnowhouseExceptionHandler : public IExceptionHandler {
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
        bool handle_exception(
            std::exception_ptr* exception, IExceptionMessageCallbackFn* failureMessageCallback
        ) override {
            try {
                std::rethrow_exception(*exception);
            } catch (const snowhouse::AssertionException& e) {
                if (failureMessageCallback) {
                    SpecExceptionMessage failureMessage{string_format(
                        "{}\n[{}:{}] {}", e.what(), e.file(), e.line(),
                        ReadLineFromFile(e.file(), e.line())
                    )};
                    failureMessageCallback->invoke(&failureMessage);
                }
                return true;
            } catch (...) {
                return false;
            }
        }
    };
}