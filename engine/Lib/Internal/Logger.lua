log = {};

function log.format(...)
    local s = "";
    local first = true;
    for _, v in pairs({...}) do
        if first then
            s = tostring(v);
            first = false;
        else
            s = s .. " " .. tostring(v);
        end
    end
    return s;
end

function log.critical(...)
    obe.debug.critical(log.format(...));
end

function log.error(...)
    obe.debug.error(log.format(...));
end

function log.warn(...)
    obe.debug.warn(log.format(...));
end

function log.info(...)
    obe.debug.info(log.format(...));
end

function log.debug(...)
    obe.debug.debug(log.format(...));
end

function log.trace(...)
    obe.debug.trace(log.format(...));
end

-- print = log.debug;