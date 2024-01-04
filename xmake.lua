add_rules("mode.debug", "mode.release")

set_languages("c++23")

add_toolchains("clang")

-- add_cxxflags("cl::/MD")
-- add_cxxflags("cl::/EHsc")
-- add_cxxflags("cl::/interface")

-- set_toolset("cc", "gcc-12")
-- set_toolset("cxx", "g++-12")

-- add_cxxflags("-fmodules-ts")

set_toolset("cc", "clang-17")
set_toolset("cxx", "clang++-17")

-- add_cxxflags("-fmodule-file=pcms/foo.pcm")
add_cxxflags("-fprebuilt-module-path=pcms")

-- add_cxxflags("-fmodules")
-- add_cxxflags("-fbuiltin-module-map")

-- add_compile_options("-fmodules -fbuiltin-module-map")
-- add_link_options("-fmodules -fbuiltin-module-map")

add_repositories("MrowrLib https://github.com/MrowrLib/Packages")
 
-- includes("Specs/*/xmake.lua") 
includes("*/xmake.lua") 
