target("Specs.Globals")
    set_kind("headeronly")
    add_includedirs("include", { public = true })
    add_deps("Specs.Implementations")
