add_requires("cxxopts", "underscore_log")

target("Specs.Main")
    set_kind("headeronly")
    add_deps("Specs.Implementations", "Specs.DSLs")
    add_packages("cxxopts", "underscore_log", { public = true })
    add_includedirs("include", { public = true })
