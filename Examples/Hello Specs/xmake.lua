add_requires("underscore_log", "spdlog", "unordered_dense")

target("Hello Specs")
    set_kind("binary")
    add_files("Templates/*.cpp", "*.cpp")
    add_deps("Specs", "Specs.Snowhouse", "Specs.LibAssert")
    add_packages("underscore_log", "spdlog", "unordered_dense", "libassert_latest")
    add_includedirs(".")
