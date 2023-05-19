add_requires("vcpkg::snowhouse", "fmt")

target("Specs - Example")
    set_kind("binary")
    add_deps("Specs")
    add_files("CLI.Stuff.cpp")
    add_packages("vcpkg::snowhouse", "fmt")
    add_defines("STRING_FORMAT_USE_FMT")
