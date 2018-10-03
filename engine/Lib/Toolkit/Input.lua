return {
    input = function()
        local inp = coroutine.yield();
        return inp;
    end
};