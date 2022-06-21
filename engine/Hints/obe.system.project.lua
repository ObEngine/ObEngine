---@meta

obe.system.project = {};
---@class obe.system.project.Project
obe.system.project._Project = {};

--- obe.system.project.Project constructor
---
---@return obe.system.project.Project
function obe.system.project.Project() end


--- Gets the validation schema of the Serializable object as a vili node.
---
---@return vili.node
function obe.system.project._Project:schema() end

--- Dumps the content of the Project to a vili node.
---
---@return vili.node
function obe.system.project._Project:dump() end

--- Loads a Project from a vili node.
---
---@param data vili.node #vili node containing the data of the Project
function obe.system.project._Project:load(data) end

---@param path string #
function obe.system.project._Project:load_from_file(path) end

function obe.system.project._Project:mount() end

function obe.system.project._Project:unmount() end

---@return string
function obe.system.project._Project:get_id() end

---@return boolean
function obe.system.project._Project:is_standalone() end


---@class obe.system.project.ProjectURLs
---@field homepage string #
---@field issues string #
---@field readme string #
---@field documentation string #
---@field license string #
obe.system.project._ProjectURLs = {};


--- Gets the validation schema of the Serializable object as a vili node.
---
---@return vili.node
function obe.system.project._ProjectURLs:schema() end

--- Dumps the content of the Project URLs to a vili node.
---
---@return vili.node
function obe.system.project._ProjectURLs:dump() end

--- Loads a Project URLs from a vili node.
---
---@param data vili.node #vili node containing the data of the Project URLs
function obe.system.project._ProjectURLs:load(data) end


--- Get the Location of the Project identified by project_name.
---
---@param project_name string #Name of the Project you want to get the path.
---@return string
function obe.system.project.get_project_location(project_name) end

--- Get if the Project exists or not.
---
---@param project_name string #Name of the Project you want to check the existence.
---@return boolean
function obe.system.project.project_exists(project_name) end

--- Load a new Project in the mounted paths.
---
---@param project_name string #Name of the Project to load.
---@param prefix string #Prefix that can be used to reference Project root path
---@param priority? number #Priority of the path that will be mounted.
---@return boolean
function obe.system.project.load(project_name, prefix, priority) end

---@return string[]
function obe.system.project.list_projects() end

return obe.system.project;