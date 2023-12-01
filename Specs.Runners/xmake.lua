add_requires("collections")

target("Specs.Runners")
    set_kind("headeronly")
    add_deps("Specs.API")
    add_packages("collections", { public = true })
    add_includedirs("include", { public = true })
