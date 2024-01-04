target("Specs.Module")
    set_kind("static")
    add_files("*.ixx", { install = true })
    add_deps("Specs.Entrypoint")
