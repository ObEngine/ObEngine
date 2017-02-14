function package(argtable)
    local packageName = argtable.output;
    print("Creating package : " .. packageName .. ".msp from package : " .. argtable.pkgname);
end

return package;