add_rules("mode.debug", "mode.releasedbg", "mode.release")

set_languages("c++20")

add_repositories("MrowrLib https://github.com/MrowrLib/Packages")

includes("*/xmake.lua")
includes("Examples/**/xmake.lua")
