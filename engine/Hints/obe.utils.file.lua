---@meta

obe.utils.file = {};
--- Get a list of directories.
---
---@param path string #Path where you want to check the directories
---@return string[]
function obe.utils.file.get_directory_list(path) end

--- Get a list of files.
---
---@param path string #Path where you want to check the files
---@return string[]
function obe.utils.file.get_file_list(path) end

--- Check if the file at the given path exists.
---
---@param path string #Path of the file you want to check the existence
---@return boolean
function obe.utils.file.file_exists(path) end

--- Check if the directory at the given path exists.
---
---@param path string #Path of the directory you want to check the existence
---@return boolean
function obe.utils.file.directory_exists(path) end

--- Creates a directory at the given path.
---
---@param path string #Path of the directory you want to create
---@return boolean
function obe.utils.file.create_directory(path) end

--- Create an empty file at the given path.
---
---@param path string #Path of the empty file you want to create
function obe.utils.file.create_file(path) end

--- Copy a file.
---
---@param source string #Path of the file you want to copy
---@param target string #Path of the new copy
function obe.utils.file.copy(source, target) end

--- Deletes a file.
---
---@param path string #Path of the file you want to delete
---@return boolean
function obe.utils.file.delete_file(path) end

--- Deletes an empty directory.
---
---@param path string #Path of of the directory you want to delete
---@return boolean
function obe.utils.file.delete_directory(path) end

--- Get the Current Working Directory (CWD)
---
---@return string
function obe.utils.file.get_current_directory() end

--- Returns the path separator of the current OS.
---
---@return string
function obe.utils.file.separator() end

--- Returns the path to the directory of the current executable.
---
---@return string
function obe.utils.file.get_executable_directory() end

--- Returns the path of the current executable.
---
---@return string
function obe.utils.file.get_executable_path() end

--- Normalizes the path given in argument (replaces every separator with a forward slash)
---
---@param path string #Path to normalize
---@return string
function obe.utils.file.normalize_path(path) end

---@param path string #
---@return string
function obe.utils.file.canonical_path(path) end

---@param parts string[] #
---@return string
function obe.utils.file.join(parts) end

return obe.utils.file;