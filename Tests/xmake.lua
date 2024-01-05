add_requires(
    "specs"
)

-- TODO
-- target("Tests - Using Headers")

target("Tests - Using Modules")
    set_kind("binary")
    add_files("*.cpp")
    add_packages("specs")
    add_includedirs(".")

    -- Separate targets for using modules -vs- headers

    -- headers...
    add_deps("Specs.Application.Module")
