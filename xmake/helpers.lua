function is_wsl()
    return os.isfile("/proc/sys/fs/binfmt_misc/WSLInterop")
end

function is_linux()
    return is_plat("linux") or is_wsl()
end

function supports_clang()
    return is_wsl() or not is_plat("windows")
end

function set_compiler(compiler)
    if is_plat("windows") and not is_wsl() then
        print("WINDOWS returning...")
        return -- MSVC, nothing to configure
    end
    if not compiler then
        compiler = "gcc" -- Default to gcc
    end
    if compiler == "clang" then
        local clang_version = os.getenv("CLANG_VERSION")
        set_toolchains("clang")
        if clang_version then
            set_toolset("cc", "clang-" .. clang_version)
            set_toolset("cxx", "clang++-" .. clang_version)
            set_toolset("ld", "clang++-" .. clang_version)
        end
    elseif compiler == "gcc" then
        local gcc_version = os.getenv("GCC_VERSION")
        set_toolchains("gcc")
        if gcc_version then
            set_toolset("cc", "gcc-" .. gcc_version)
            set_toolset("cxx", "g++-" .. gcc_version)
            set_toolset("ld", "g++-" .. gcc_version)
        end
    else
        error("Unknown compiler: " .. compiler)
    end
end

function test_target(cpp_version, compiler)
    target_name = "Tests " .. cpp_version
    if compiler then 
        target_name = target_name .. " " .. compiler
    end
    target(target_name)
        set_languages(cpp_version)
        set_compiler(compiler)
        set_kind("binary")
        add_includedirs("Helpers")
        add_files("run_tests.cpp")
        -- add_files(cpp_version .. "/*.cpp")
end
