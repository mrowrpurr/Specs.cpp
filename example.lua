add_rules("mode.debug", "mode.release")

add_repositories("MrowrLib https://github.com/MrowrLib/Packages")

add_languages("c++20")

includes("xmake/*.lua")

target("TestLibrary")
    set_kind("headeronly")
    add_includedirs("include", { public = true })
    make_module_target("TestModule")

target("TestUsingModule")
    set_kind("binary")
    add_deps("TestModule")
    add_files("use_module.cpp")

target("TestUsingLibrary")
    set_kind("binary")
    add_deps("TestLibrary")
    add_files("use_library.cpp")
