add_rules("mode.debug", "mode.release")

set_languages("c++20")

add_repositories("MrowrLib https://github.com/MrowrLib/Packages")
add_requires("string_format", "mrowr_log", "spdlog", "fmt")

includes("**/xmake.lua")
