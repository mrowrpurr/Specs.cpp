target("Specs.CLI")
    set_kind("headeronly")
    add_deps("Specs.API")
    add_includedirs("include", { public = true })
