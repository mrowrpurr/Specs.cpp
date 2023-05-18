add_requires("vcpkg::snowhouse")

target("CLI.Stuff")
    set_kind("binary")
    add_deps("Specs")
    add_files("CLI.Stuff.cpp")
    add_packages("vcpkg::snowhouse", "fmt")
