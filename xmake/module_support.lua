set_policy("build.c++.modules", true)

if is_host("windows") then
    add_cxxflags("cl::/MD")
    add_cxxflags("cl::/EHsc")
    add_cxxflags("cl::/interface")
    add_cxxflags("cl::/std:c++latest")
elseif is_host("macosx") then
    -- TODO
elseif is_host("linux") then
    set_toolset("cc", "gcc-12")
    set_toolset("cxx", "g++-12")
end
