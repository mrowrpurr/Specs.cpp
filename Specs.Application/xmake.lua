target("Specs.Application")
    set_kind("headeronly")
    add_includedirs("include", { public = true })
    add_deps("Specs.Interfaces")
    
make_module("Specs.Application")
    add_deps("Specs.Interfaces.Module")
