---@meta

obe.audio.exceptions = {};
---@class obe.audio.exceptions.AudioFileNotFound : obe.Exception[obe.audio.exceptions.AudioFileNotFound]
obe.audio.exceptions._AudioFileNotFound = {};

--- obe.audio.exceptions.AudioFileNotFound constructor
---
---@param path string #
---@param mounted_paths string[] #
---@param info obe.DebugInfo #
---@return obe.audio.exceptions.AudioFileNotFound
function obe.audio.exceptions.AudioFileNotFound(path, mounted_paths, info) end



return obe.audio.exceptions;