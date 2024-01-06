add_rules("mode.debug", "mode.release")

includes("xmake/*.lua")

if is_wsl() then
    -- xmake-vscode doesn't automatically generate compile_commands.json
    add_rules("plugin.compile_commands.autoupdate", { outputdir = "compile_commands" })

    -- If you ever need to do it from the command line:
    -- xmake project -k compile_commands --lsp=clangd
end

-- includes("Specs/xmake.lua")

includes("Tests/xmake.lua")
