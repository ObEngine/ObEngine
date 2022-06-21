---@meta

obe.system.package = {};
--- Get the Location of the Package identified by package_name.
---
---@param package_name string #Name of the Package you want to get the path.
---@return string
function obe.system.package.get_package_location(package_name) end

--- Get if the Package exists or not.
---
---@param package_name string #Name of the Package you want to check the existence.
---@return boolean
function obe.system.package.package_exists(package_name) end

---@return string[]
function obe.system.package.list_packages() end

--- Installs a Package.
---
---@param package_name string #Is the name of the .opaque file located in Package/ folder (without the .opaque extension)
---@return boolean
function obe.system.package.install(package_name) end

--- Load a new Package in the mounted paths.
---
---@param package_name string #Name of the Package to load.
---@param prefix string #Prefix that can be used to reference Package root path
---@param priority? number #Priority of the path that will be mounted.
---@return boolean
function obe.system.package.load(package_name, prefix, priority) end

return obe.system.package;