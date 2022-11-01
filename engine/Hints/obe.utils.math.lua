---@meta

obe.utils.math = {};
--- Get a random integer between the given bound.
---
---@param min N #Min bound
---@param max N #Max bound \thints
---@return N
function obe.utils.math.randint(min, max) end

--- Get a random double.
---
---@return number
function obe.utils.math.randfloat() end

--- Get the lowest value between the two given values.
---
---@param min1 N #First value to check
---@param min2 N #Second value to check
---@return N
function obe.utils.math.get_min(min1, min2) end

--- Get the highest value between the two given values.
---
---@param max1 N #First value to check
---@param max2 N #Second value to check
---@return N
function obe.utils.math.get_max(max1, max2) end

--- Check if the given value is between the lower bound and the upper bound.
---
---@param target N #Value to check
---@param lower_bound N1 #Lower bound
---@param upper_bound N2 #Upper bound
---@return boolean
function obe.utils.math.is_between(target, lower_bound, upper_bound) end

--- Check if a double is an integer (3.0 for example is equal to 3)
---
---@param value number #Value to check
---@return boolean
function obe.utils.math.is_double_int(value) end

--- Get the sign of the given number.
---
---@param val T #Value to check the sign
---@return number
function obe.utils.math.sign(val) end

--- Converts a degrees angle to radians.
---
---@param value number #Angle in degrees
---@return number
function obe.utils.math.convert_to_radian(value) end

--- Converts a radians angle to degrees.
---
---@param value number #Angle in radians
---@return number
function obe.utils.math.convert_to_degrees(value) end

--- Normalizes a value between start and end.
---
---@param value number #Value to normalize
---@param low number #Lower bound
---@param high number #Higher bound
---@return number
function obe.utils.math.normalize(value, low, high) end


---@type number
obe.utils.math.pi = {};
return obe.utils.math;