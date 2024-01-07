test_target("cxx11")
clang_test_target("cxx11")

test_target("cxx14")
clang_test_target("cxx14")

test_target("cxx17")
clang_test_target("cxx17")

test_target("cxx17")
clang_test_target("cxx17")

test_target("cxx20")
clang_test_target("cxx20")

target("Run All Tests")
    set_kind("phony")
    on_run(function ()
        os.exec("xmake build -w -a")
        local targets = { "Tests cxx11", "Tests cxx14", "Tests cxx17", "Tests cxx20" }
        if is_plat("linux") or os.isfile("/proc/sys/fs/binfmt_misc/WSLInterop") then
            table.insert(targets, "Tests cxx11 clang")
            table.insert(targets, "Tests cxx14 clang")
            table.insert(targets, "Tests cxx17 clang")
            table.insert(targets, "Tests cxx20 clang")
        end
        for _, target in ipairs(targets) do
            print("Running target: " .. target)
            os.exec(string.format("xmake run \"%s\"", target))
        end
    end)