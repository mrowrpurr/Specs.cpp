add_requires(
    "specs"
)

target("Tests")
    set_kind("binary")
    add_files("*.cpp")
    add_packages("specs")
    add_deps("Specs.Entrypoint")
