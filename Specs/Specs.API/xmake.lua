add_requires("function_pointer", "void_pointer", "underscore_log")

target("Specs.API")
    set_kind("headeronly")
    add_includedirs("include", { public = true })
    add_packages("function_pointer", "void_pointer", "underscore_log", { public = true })
