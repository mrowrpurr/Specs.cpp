target("Specs.DLL")
    set_kind("headeronly")
    add_deps("Specs.Implementations")
    add_includedirs("include", { public = true })
