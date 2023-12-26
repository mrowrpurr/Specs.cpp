add_requires("spdlog", "unordered_dense")

target("Tests")
    set_kind("binary")
    add_files("*.cpp", "**/*.cpp")
    add_includedirs(".")
    add_deps("Specs", "Specs.Snowhouse", "Specs.TestHelpers")
    add_packages("spdlog", "unordered_dense")
