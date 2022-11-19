local function realpath(path)
    return obe.system.Path(path):find():hypothetical_path();
end

-- ULF stands for Unpatched Lua Functions
__ULF = {
    io = {
        open = io.open,
        popen = io.popen,
    }
};

local io_open = io.open;
function io.open(filename, mode)
    return io_open(realpath(filename), mode);
end

if io.popen then
    local io_popen = io.popen;
    function io.popen(prog, mode)
        return io_popen(realpath(prog), mode);
    end
end