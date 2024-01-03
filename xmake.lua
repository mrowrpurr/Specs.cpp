add_rules("mode.debug", "mode.release")

set_languages("c++20")
 
add_repositories("MrowrLib https://github.com/MrowrLib/Packages")
 
includes("Specs/*/xmake.lua") 
includes("*/xmake.lua") 
