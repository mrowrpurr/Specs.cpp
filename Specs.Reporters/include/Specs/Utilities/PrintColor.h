#pragma once

#include <string_format.h>

#include <cstdint>
#include <iostream>
#include <string>
#include <string_view>

namespace SpecsCpp::Colors {

    // TODO this shouldn't use the ANSI escape codes on Windows
    enum class Color {
        None        = 0,
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

    inline void PrintColor(
        std::string_view text, Color foreground = Color::None, Color background = Color::None,
        Unix::Style style = Unix::Style::Normal
    ) {
        using namespace Unix;

        std::string output = "\033[";

        if (style != Style::Normal) output += std::to_string(static_cast<std::uint8_t>(style));

        if (foreground != Color::None) {
            if (style != Style::Normal) output += ";";
            output += std::to_string(static_cast<std::uint8_t>(foreground));
        }

        if (background != Color::None) {
            if (style != Style::Normal || foreground != Color::None) output += ";";
            output += std::to_string(static_cast<std::uint8_t>(background));
        }

        output += string_format("m{}\033[0m", text);

        std::cout << output;
    }

}