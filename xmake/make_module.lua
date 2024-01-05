function make_module(target_name, kind, file_folder, public)
    if not kind then
        kind = "static"
    end
    if not file_folder then
        file_folder = "include"
    end
    if not public then
        public = true
    end

    target_end()

    target("Generate " .. target_name .. " module")
        set_kind("phony")
        before_build(function (target)
            local files_folder = path.join(target_name, file_folder)
            if not os.isdir(files_folder) then
                print("Expected directory: " .. files_folder)
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
                    if filename:endswith(".h") or filename:endswith(".cpp") then
                        local new_file = dest .. "/" .. filename:gsub("%.h$", ".ixx"):gsub("%.cpp$", ".ixx")
                        local content = io.readfile(file)

                        content = content:gsub("//@ import ", "import ")
                        content = content:gsub("//@ module;", "module;")
                        content = content:gsub("//@ export module", "export module")
                        
                        content = content:gsub("#include *\"([a-zA-Z0-9/%-.]+)%.h\" *// @headerunit@", "import <%1>;")
                        content = content:gsub("#include *<([a-zA-Z0-9/%-.]+)%.h> *// @headerunit@", "import <%1>;")
                        content = content:gsub("#include *<([a-zA-Z0-9/%-.]+)%> *// @headerunit@", "import <%1>;")

                        content = content:gsub("#include *\"([a-zA-Z0-9/%-.]+)%.h\" *// @nomodule@", "")
                        content = content:gsub("#include *<([a-zA-Z0-9/%-.]+)%.h> *// @nomodule@", "")
                        content = content:gsub("#include *<([a-zA-Z0-9/%-.]+)%> *// @nomodule@", "")

                        content = content:gsub("#include *\"([a-zA-Z0-9/%-.]+)%.h\" *// @module@", "import %1;")
                        content = content:gsub("#include *<([a-zA-Z0-9/%-.]+)%.h> *// @module@", "import %1;")
                        content = content:gsub("#include *<([a-zA-Z0-9/%-.]+)%> *// @module@", "import %1;")

                        content = content:gsub("//@ export\nnamespace", "export namespace")

                        io.writefile(new_file, content)
                    end
                end
                for _, dir in ipairs(os.dirs(source .. "/*")) do
                    local subdir = path.filename(dir)
                    copy_files(dir, dest .. "/" .. subdir)
                end
            end

            copy_files(files_folder, path.join(module_dir, relative_path))
        end)
    target_end()

    target(target_name .. ".Module")
        set_kind(kind)
        add_defines("USE_MODULES")
        if os.isdir(path.join(os.projectdir(), "modules", target_name)) then
            add_files(path.join(os.projectdir(), "modules", target_name, "**.ixx"), { install = public })
        end
end

function make_binary_module(target_name)
    make_module(target_name, "binary", ".", false)
end
