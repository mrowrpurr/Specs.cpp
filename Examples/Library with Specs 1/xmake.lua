add_requires("spdlog")

target("Library with Specs 1")
    set_kind("shared")
    add_files("*.cpp")
    add_deps(
        "Specs.DLL",
        "Specs.DSLs",
        "Specs.Snowhouse" 
    )
    add_packages("spdlog")
