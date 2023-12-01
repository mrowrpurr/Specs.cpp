add_requires("underscore_log", "spdlog", "unordered_dense")

target("EXE run loaded DLLs")
    set_kind("binary")
    add_files("*.cpp")
    add_deps(
        "Specs.DllLoader",
        "Specs.Implementations",
        "Specs.Runners",
        "Specs.Reporters"
    )
    add_packages("underscore_log", "spdlog", "unordered_dense")
