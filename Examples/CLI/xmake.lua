add_requires("vcpkg::snowhouse")

target("Specs - Example")
    set_kind("binary")
    add_deps("Specs")
    add_files("CLI.Stuff.cpp")
    add_packages("vcpkg::snowhouse", "fmt")
