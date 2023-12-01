target("Specs")
    set_kind("headeronly")
    add_deps(
        "Specs.Main",
        "Specs.DSLs",
        "Specs.Implementations",
        "Specs.Reporters",
        "Specs.Runners",
        "Specs.DllLoader"
    )
    add_includedirs("include", { public = true })
