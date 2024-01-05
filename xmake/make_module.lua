function make_module(target_name)
    target_end()

    target("Generate " .. target_name .. " module")
        set_kind("phony")
        before_build(function (target)
            local include_dir = path.join(target_name, "include")
            if not os.isdir(include_dir) then
                print("Expected include directory: " .. include_dir)
                return
            end

            local module_dir = path.join("modules", target_name)
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
                    content = content:gsub("//@ import ", "import ")
                    content = content:gsub("#include%s*\"(.-)%.h\"%s*// @headerunit@", "import <%1>;")
                    content = content:gsub("#include%s*<(.-)%.h>%s*// @headerunit@", "import <%1>;")
                    content = content:gsub("#include%s*<(.-)>%s*// @headerunit@", "import <%1>;")
                    content = content:gsub("#include%s*(.-)%s*// @nomodule@", "")
                    content = content:gsub("#include%s*<(.-)>%s*// @module@", "import %1;")
                    content = content:gsub("#include%s*\"(.-)%.h\"%s*// @module@", "import %1;")
                    content = content:gsub("//@ export\nnamespace", "export namespace")
                    io.writefile(new_file, content)
                end
                for _, dir in ipairs(os.dirs(source .. "/*")) do
                    local subdir = path.filename(dir)
                    copy_files(dir, dest .. "/" .. subdir)
                end
            end

            copy_files(include_dir, path.join(module_dir, relative_path))
        end)
    target_end()

    target(target_name .. ".Module")
        set_kind("static")
        add_defines("USE_MODULES")
        if os.isdir(path.join(os.projectdir(), "modules", target_name)) then
            add_files(path.join(os.projectdir(), "modules", target_name, "**.ixx"), { install = true })
        end
end
