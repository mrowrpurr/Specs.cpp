add_rules("mode.debug", "mode.release")

set_languages("c++20")

if is_plat("windows") then
    add_toolchains("msvc")
else
    add_toolchains("clang")
end

add_repositories("MrowrLib https://github.com/MrowrLib/Packages")
add_requires("string_format", "fmt")

-- includes("**/xmake.lua")
