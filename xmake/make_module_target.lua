function make_module_target(module_name)
    on_config(function (target)
        local module_dir = path.join("modules", module_name)
        if os.isdir(module_dir) then
            os.rmdir(module_dir)
        end
        local function copy_files(source, dest)
            os.mkdir(dest)
            for _, file in ipairs(os.files(source .. "/*")) do
                local filename = path.filename(file)
                local new_file = dest .. "/" .. filename:gsub("%.h$", ".ixx")

                -- Read the content of the .h file
                local content = io.readfile(file)
                -- Perform the replacements
                content = content:gsub("//@ module;", "module;")
                content = content:gsub("//@ export module", "export module")
                content = content:gsub("//@ export @//", "export")
                content = content:gsub("//@ export:", "export:")
                -- Handle the special case of removing the newline after "//@ export @//"
                content = content:gsub("export\nnamespace", "export namespace")

                -- Write the modified content to the .ixx file
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
