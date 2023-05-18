add_requires("vcpkg::snowhouse")

target("Specs - Hello World")
    set_kind("binary")
    add_deps("Specs")
    add_files("Hello World.cpp")
    add_packages("vcpkg::snowhouse", "fmt")
