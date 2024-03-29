add_rules("mode.debug", "mode.releasedbg", "mode.release")

set_languages("c++20")

add_repositories("MrowrLib https://github.com/MrowrLib/Packages")

add_requires("specs", "specs_snowhouse", "specs_libassert")
add_requires("vcpkg::snowhouse", "spdlog", "unordered_dense")
add_requires("libassert_latest", { configs = { lowercase = true } })

target("DemoSpecs")
    set_kind("binary")
    add_files("*.cpp")
    add_packages("specs", "specs_snowhouse", "specs_libassert")
    add_packages("vcpkg::snowhouse", "libassert_latest", "spdlog", "unordered_dense")
