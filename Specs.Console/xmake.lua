add_requires("unordered_dense", "spdlog")

target("Specs.Console")
    set_kind("binary")
    set_basename("Specs")
    add_files("*.cpp")
    add_deps(
        "Specs.Main",
        "Specs.Reporters",
        "Specs.Runners",
        "Specs.DllLoader"
    )
    add_packages("unordered_dense", "spdlog")
