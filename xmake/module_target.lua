function make_module_target(module_name)
    on_load(function (target)
        local module_dir = path.join("modules", module_name)
        if os.isdir(module_dir) then
            os.rmdir(module_dir)
        end
        local function copy_files(source, dest)
            os.mkdir(dest)
            for _, file in ipairs(os.files(source .. "/*")) do
                local filename = path.filename(file)
                local new_file = dest .. "/" .. filename:gsub("%.h$", ".ixx")
                os.cp(file, new_file)
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
        add_files(path.join("modules", module_name, "**.ixx"), { install = true })
end
