add_requires("function_pointer", "void_pointer", "underscore_log", "virtual_collections")

target("Specs.API")
    set_kind("headeronly")
    add_includedirs("include", { public = true })
    add_packages("function_pointer", "void_pointer", "underscore_log", "virtual_collections", { public = true })
