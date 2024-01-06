function is_wsl()
    return os.isfile("/proc/sys/fs/binfmt_misc/WSLInterop") then
end
