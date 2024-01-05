add_requires(
    "specs"
)

target("Tests")
    set_kind("binary")
    add_files("*.cpp")
    add_packages("specs")
    add_includedirs(".")
    add_deps("Specs.Application")

make_binary_module("Tests")
    add_packages("specs")
    add_deps("Specs.Application.Module")
