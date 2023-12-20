add_requires("vcpkg::snowhouse", "string_format")

target("Specs.Snowhouse")
    set_kind("headeronly")
    add_deps("Specs.DSLs", "Specs.Implementations")
    add_packages("vcpkg::snowhouse", "string_format", { public = true })
    add_includedirs("include", { public = true })
