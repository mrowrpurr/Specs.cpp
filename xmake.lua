add_rules("mode.debug", "mode.release")

set_languages("c++20")

add_repositories("MrowrLib https://github.com/MrowrLib/Packages")
add_requires("string_format", "_Log_", "spdlog", "fmt", "vcpkg::snowhouse")

includes("*/xmake.lua")
includes("Examples/*/xmake.lua")
