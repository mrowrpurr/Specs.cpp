target("ModuleHelper")
    set_kind("headeronly")


function make_module_target(module_name)
    before_build(function (target)
        local module_dir = path.join("modules", module_name)
        if os.isdir(module_dir) then
            os.rmdir(module_dir)
        end
        local function copy_files(source, dest)
            os.mkdir(dest)
            for _, file in ipairs(os.files(source .. "/*")) do
                local filename = path.filename(file)
                local new_file = dest .. "/" .. filename:gsub("%.h$", ".ixx")
                local content = io.readfile(file)
                content = content:gsub("//@ module;", "module;")
                content = content:gsub("//@ export module", "export module")
                content = content:gsub("//@ export @//", "export")
                content = content:gsub("//@ export:", "export:")
                content = content:gsub("//@ import ", "import ")
                content = content:gsub("#include%s*\"(.-)%.h\"%s*// @headerunit@", "import <%1>;")
                content = content:gsub("#include%s*<(.-)%.h>%s*// @headerunit@", "import <%1>;")
                content = content:gsub("#include%s*<(.-)>%s*// @headerunit@", "import <%1>;")
                content = content:gsub("#include%s*(.-)%s*// @nomodule@", "")
                content = content:gsub("#include%s*<(.-)>%s*// @module@", "import %1;")
                content = content:gsub("#include%s*\"(.-)%.h\"%s*// @module@", "import %1;")
                content = content:gsub("export\nnamespace", "export namespace")
                io.writefile(new_file, content)
            end
            for _, dir in ipairs(os.dirs(source .. "/*")) do
                local subdir = path.filename(dir)
                copy_files(dir, dest .. "/" .. subdir)
            end
        end
        for _, dir in ipairs(target:get("includedirs")) do
            local relative_path = path.relative(dir, os.projectdir())
            copy_files(dir, path.join(module_dir, relative_path))
        end
    end)
    target_end()
    target(module_name)
        set_kind("static")
        add_defines("USE_MODULES")
        add_files(path.join("modules", module_name, "**.ixx"), { install = true })
end
