add_requires("global_macro_functions")

target("Specs.DSLs")
    set_kind("headeronly")
    add_deps(
        "Specs.API",
        "Specs.Implementations"
    )
    add_packages("global_macro_functions", { public = true })
    add_includedirs("include", { public = true })
