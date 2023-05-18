#pragma once

#include <cstdint>
#include <iostream>
#include <string>

namespace Specs::Reporters::Utilities {

    namespace Colors {
        enum class Color {
            None,
            Black,
            Red,
            Green,
            Yellow,
            Blue,
            Purple,
            Cyan,
            LightGray,
            DarkGray,
            LightRed,
            LightGreen,
            LightYellow,
            LightBlue,
            LightPurple,
            LightCyan,
            White
        };

        namespace Unix {
            enum class Style : uint8_t {
                Normal     = 0,
                Bold       = 1,
                Dim        = 2,
                Italic     = 3,
                Underline  = 4,
                SlowBlink  = 5,
                RapidBlink = 6,
                Inverted   = 7,
                Conceal    = 8,
                CrossedOut = 9
            };

            enum class ForegroundColor : uint8_t {
                Black       = 30,
                Red         = 31,
                Green       = 32,
                Yellow      = 33,
                Blue        = 34,
                Purple      = 35,
                Cyan        = 36,
                LightGray   = 37,
                DarkGray    = 90,
                LightRed    = 91,
                LightGreen  = 92,
                LightYellow = 93,
                LightBlue   = 94,
                LightPurple = 95,
                LightCyan   = 96,
                White       = 97
            };

            enum class BackgroundColor : uint8_t {
                Black       = 40,
                Red         = 41,
                Green       = 42,
                Yellow      = 43,
                Blue        = 44,
                Purple      = 45,
                Cyan        = 46,
                LightGray   = 47,
                DarkGray    = 100,
                LightRed    = 101,
                LightGreen  = 102,
                LightYellow = 103,
                LightBlue   = 104,
                LightPurple = 105,
                LightCyan   = 106,
                White       = 107
            };
        }
    }

    void PrintColor(
        const std::string& text, Colors::Color foreground = Colors::Color::None,
        Colors::Color background = Colors::Color::None, Colors::Unix::Style style = Colors::Unix::Style::Normal
    ) {
        using namespace Colors::Unix;

        std::string output = "\033[";

        if (style != Style::Normal) {
            output += std::to_string(static_cast<uint8_t>(style));
        }

        if (foreground != Colors::Color::None) {
            if (style != Style::Normal) {
                output += ";";
            }

            output += std::to_string(static_cast<uint8_t>(foreground) + 30);
        }

        if (background != Colors::Color::None) {
            if (style != Style::Normal || foreground != Colors::Color::None) {
                output += ";";
            }

            output += std::to_string(static_cast<uint8_t>(background) + 40);
        }

        output += "m" + text + "\033[0m";

        std::cout << output;
    }
}

// HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
//             SetConsoleTextAttribute(console, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
//             std::cout << "PASS: " << testDescription << std::endl;
//             SetConsoleTextAttribute(console, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
