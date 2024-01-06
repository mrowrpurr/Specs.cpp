function test_target(cpp_version)
    target("Tests " .. cpp_version)
        set_languages(cpp_version)
        set_kind("binary")
        add_includedirs("Helpers")
        add_files("run_tests.cpp")
        -- add_files(cpp_version .. "/*.cpp")
end

test_target("cxx11")

-- target("Tests C++14")
--     set_languages("c++14")
--     set_kind("binary")
--     add_files("run_tests.cpp")
--     -- add_files("Cpp11/*.cpp")

-- target("Tests C++14")
--     set_languages("c++14")
--     set_kind("binary")
--     add_files("run_tests.cpp")
--     -- add_files("Cpp11/*.cpp")

-- target("Tests C++17")
--     set_languages("c++17")
--     set_kind("binary")
--     add_files("run_tests.cpp")
--     -- add_files("Cpp11/*.cpp")

-- target("Tests C++20")
--     set_languages("c++20")
--     set_kind("binary")
--     add_files("run_tests.cpp")
--     -- add_files("Cpp11/*.cpp")

-- -- target("Tests C++20 Modules")
-- -- target("Tests C++2b")
