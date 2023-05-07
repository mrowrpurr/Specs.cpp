add_rules("mode.debug", "mode.release")

set_languages("c++20")
add_toolchains("msvc")

includes("**/xmake.lua")
