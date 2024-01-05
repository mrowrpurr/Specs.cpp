add_rules("mode.debug", "mode.release")

add_repositories("MrowrLib https://github.com/MrowrLib/Packages")

add_languages("c++20")

includes("xmake/*.lua")
includes("*/xmake.lua")
