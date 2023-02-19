#pragma once

#include <string>

namespace Spec::Types {
    class SpecTestResultFailure {
        std::string  _message;
        std::string  _fileName;
        unsigned int _lineNumber = 0;

    public:
        SpecTestResultFailure() = default;
        SpecTestResultFailure(std::string message, std::string fileName = "", unsigned int lineNumber = 0)
            : _message(message), _fileName(fileName), _lineNumber(lineNumber) {}

        std::string  GetMessage() { return _message; }
        void         SetMessage(std::string message) { _message = message; }
        std::string  GetFileName() { return _fileName; }
        void         SetFileName(std::string fileName) { _fileName = fileName; }
        unsigned int GetLineNumber() { return _lineNumber; }
        void         SetLineNumber(unsigned int lineNumber) { _lineNumber = lineNumber; }

        bool HasMessage() { return !_message.empty(); }
        bool HasFileName() { return !_fileName.empty(); }
        bool HasLineNumber() { return _lineNumber != 0; }
        bool HasFileLocation() { return HasFileName() && HasLineNumber(); }
    };
}
