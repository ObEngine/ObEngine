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
    obe.Debug.critical(log.format(...));
end

function log.error(...)
    obe.Debug.error(log.format(...));
end

function log.warn(...)
    obe.Debug.warn(log.format(...));
end

function log.info(...)
    obe.Debug.info(log.format(...));
end

function log.debug(...)
    obe.Debug.debug(log.format(...));
end

function log.trace(...)
    obe.Debug.trace(log.format(...));
end

-- print = log.debug;