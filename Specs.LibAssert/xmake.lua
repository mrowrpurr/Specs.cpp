add_requires("libassert_latest", { configs = { lowercase = true } })
add_requires("string_format")

target("Specs.LibAssert")
    set_kind("headeronly")
    add_deps("Specs.DSLs", "Specs.Implementations")
    add_packages("libassert_latest", "string_format", { public = true })
    add_includedirs("include", { public = true })
    add_defines("ASSERT_FAIL=libassert_specs_handler", { public = true })
