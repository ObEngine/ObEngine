local mirror = require("Lib/Internal/ArgMirror");

print("Executing Debug wrapper")
function obe.Debug.critical(...)
    obe.Debug.__critical_internal(string.format(...));
end

function obe.Debug.error(...)
    obe.Debug.__error_internal(string.format(...));
end

function obe.Debug.warn(...)
    obe.Debug.__warn_internal(string.format(...));
end

function obe.Debug.info(...)
    obe.Debug.__info_internal(string.format(...));
end

function obe.Debug.debug(...)
    obe.Debug.__debug_internal(string.format(...));
end

function obe.Debug.trace(...)
    obe.Debug.__trace_internal(string.format(...));
end