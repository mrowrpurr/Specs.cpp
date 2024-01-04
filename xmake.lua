add_rules("mode.debug", "mode.release")

set_languages("c++23")

add_cxxflags("cl::/MD")
add_cxxflags("cl::/EHsc")
add_cxxflags("cl::/interface")

add_repositories("MrowrLib https://github.com/MrowrLib/Packages")
 
-- includes("Specs/*/xmake.lua") 
includes("*/xmake.lua") 
