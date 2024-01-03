add_requires("collections", "underscore_log", "string_format", "managed_pointer")

target("Specs.Implementations")
    set_kind("headeronly")
    add_includedirs("include", { public = true })
    add_deps("Specs.API")
    add_packages("collections", "underscore_log", "string_format", "managed_pointer", { public = true })
