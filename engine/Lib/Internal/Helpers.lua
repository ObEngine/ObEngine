inspect = require("obe://Lib/Extlibs/Inspect");
dbg = require("obe://Lib/Extlibs/debugger");
try = require("obe://Lib/Internal/Try");
with_require_from_obe(
    function()
        pl.List = require("obe://Lib/Extlibs/pl/List");
        pl.String = require("obe://Lib/Extlibs/pl/stringx");
    end
);

pl.String:import();
