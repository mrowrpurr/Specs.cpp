function is_wsl()
    return os.isfile("/proc/sys/fs/binfmt_misc/WSLInterop")
end

function is_linux()
    return is_plat("linux") or is_wsl()
end

function test_target(cpp_version, compiler)
    target_name = "Tests " .. cpp_version
    if compiler then 
        target_name = target_name .. " " .. compiler
    end
    target(target_name)
        set_languages(cpp_version)
        if compiler then 
            add_toolchains(compiler)
        end 
        set_kind("binary")
        add_includedirs("Helpers")
        add_files("run_tests.cpp")
        -- add_files(cpp_version .. "/*.cpp")
end

function clang_test_target(cpp_version)
    if is_linux() then
        test_target(cpp_version, "clang")
    end
end
