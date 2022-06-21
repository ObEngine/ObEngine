---@meta

obe.system.Exceptions = {};
---@class obe.system.Exceptions.InvalidDeferredMountablePath : obe.Exception[obe.system.Exceptions.InvalidDeferredMountablePath]
obe.system.Exceptions._InvalidDeferredMountablePath = {};

--- obe.system.Exceptions.InvalidDeferredMountablePath constructor
---
---@param prefix string #
---@param info obe.DebugInfo #
---@return obe.system.Exceptions.InvalidDeferredMountablePath
function obe.system.Exceptions.InvalidDeferredMountablePath(prefix, info) end



---@class obe.system.Exceptions.InvalidMountFile : obe.Exception[obe.system.Exceptions.InvalidMountFile]
obe.system.Exceptions._InvalidMountFile = {};

--- obe.system.Exceptions.InvalidMountFile constructor
---
---@param mount_file_path string #
---@param info obe.DebugInfo #
---@return obe.system.Exceptions.InvalidMountFile
function obe.system.Exceptions.InvalidMountFile(mount_file_path, info) end



---@class obe.system.Exceptions.InvalidMouseButtonEnumValue : obe.Exception[obe.system.Exceptions.InvalidMouseButtonEnumValue]
obe.system.Exceptions._InvalidMouseButtonEnumValue = {};

--- obe.system.Exceptions.InvalidMouseButtonEnumValue constructor
---
---@param enum_value number #
---@param info obe.DebugInfo #
---@return obe.system.Exceptions.InvalidMouseButtonEnumValue
function obe.system.Exceptions.InvalidMouseButtonEnumValue(enum_value, info) end



---@class obe.system.Exceptions.InvalidProjectFile : obe.Exception[obe.system.Exceptions.InvalidProjectFile]
obe.system.Exceptions._InvalidProjectFile = {};

--- obe.system.Exceptions.InvalidProjectFile constructor
---
---@param project_file_path string #
---@param info obe.DebugInfo #
---@return obe.system.Exceptions.InvalidProjectFile
function obe.system.Exceptions.InvalidProjectFile(project_file_path, info) end



---@class obe.system.Exceptions.MissingDefaultMountPoint : obe.Exception[obe.system.Exceptions.MissingDefaultMountPoint]
obe.system.Exceptions._MissingDefaultMountPoint = {};

--- obe.system.Exceptions.MissingDefaultMountPoint constructor
---
---@param info obe.DebugInfo #
---@return obe.system.Exceptions.MissingDefaultMountPoint
function obe.system.Exceptions.MissingDefaultMountPoint(info) end



---@class obe.system.Exceptions.MountFileMissing : obe.Exception[obe.system.Exceptions.MountFileMissing]
obe.system.Exceptions._MountFileMissing = {};

--- obe.system.Exceptions.MountFileMissing constructor
---
---@param current_path string #
---@param info obe.DebugInfo #
---@return obe.system.Exceptions.MountFileMissing
function obe.system.Exceptions.MountFileMissing(current_path, info) end



---@class obe.system.Exceptions.MountablePathIndexOverflow : obe.Exception[obe.system.Exceptions.MountablePathIndexOverflow]
obe.system.Exceptions._MountablePathIndexOverflow = {};

--- obe.system.Exceptions.MountablePathIndexOverflow constructor
---
---@param index number #
---@param maximum number #
---@param mounts string[] #
---@param info obe.DebugInfo #
---@return obe.system.Exceptions.MountablePathIndexOverflow
function obe.system.Exceptions.MountablePathIndexOverflow(index, maximum, mounts, info) end



---@class obe.system.Exceptions.PackageAlreadyInstalled : obe.Exception[obe.system.Exceptions.PackageAlreadyInstalled]
obe.system.Exceptions._PackageAlreadyInstalled = {};

--- obe.system.Exceptions.PackageAlreadyInstalled constructor
---
---@param package string #
---@param info obe.DebugInfo #
---@return obe.system.Exceptions.PackageAlreadyInstalled
function obe.system.Exceptions.PackageAlreadyInstalled(package, info) end



---@class obe.system.Exceptions.PackageFileNotFound : obe.Exception[obe.system.Exceptions.PackageFileNotFound]
obe.system.Exceptions._PackageFileNotFound = {};

--- obe.system.Exceptions.PackageFileNotFound constructor
---
---@param path string #
---@param info obe.DebugInfo #
---@return obe.system.Exceptions.PackageFileNotFound
function obe.system.Exceptions.PackageFileNotFound(path, info) end



---@class obe.system.Exceptions.PathError : obe.Exception[obe.system.Exceptions.PathError]
obe.system.Exceptions._PathError = {};

--- obe.system.Exceptions.PathError constructor
---
---@param prefix string #
---@param path string #
---@param info obe.DebugInfo #
---@return obe.system.Exceptions.PathError
function obe.system.Exceptions.PathError(prefix, path, info) end



---@class obe.system.Exceptions.ResourceNotFound : obe.Exception[obe.system.Exceptions.ResourceNotFound]
obe.system.Exceptions._ResourceNotFound = {};

--- obe.system.Exceptions.ResourceNotFound constructor
---
---@param path string #
---@param path_type string #
---@param mounts string[] #
---@param info obe.DebugInfo #
---@return obe.system.Exceptions.ResourceNotFound
function obe.system.Exceptions.ResourceNotFound(path, path_type, mounts, info) end



---@class obe.system.Exceptions.UnknownPackage : obe.Exception[obe.system.Exceptions.UnknownPackage]
obe.system.Exceptions._UnknownPackage = {};

--- obe.system.Exceptions.UnknownPackage constructor
---
---@param package string #
---@param all_packages string[] #
---@param info obe.DebugInfo #
---@return obe.system.Exceptions.UnknownPackage
function obe.system.Exceptions.UnknownPackage(package, all_packages, info) end



---@class obe.system.Exceptions.UnknownPathPrefix : obe.Exception[obe.system.Exceptions.UnknownPathPrefix]
obe.system.Exceptions._UnknownPathPrefix = {};

--- obe.system.Exceptions.UnknownPathPrefix constructor
---
---@param prefix string #
---@param all_prefixes string[] #
---@param info obe.DebugInfo #
---@return obe.system.Exceptions.UnknownPathPrefix
function obe.system.Exceptions.UnknownPathPrefix(prefix, all_prefixes, info) end



---@class obe.system.Exceptions.UnknownProject : obe.Exception[obe.system.Exceptions.UnknownProject]
obe.system.Exceptions._UnknownProject = {};

--- obe.system.Exceptions.UnknownProject constructor
---
---@param project string #
---@param all_projects string[] #
---@param info obe.DebugInfo #
---@return obe.system.Exceptions.UnknownProject
function obe.system.Exceptions.UnknownProject(project, all_projects, info) end



return obe.system.Exceptions;