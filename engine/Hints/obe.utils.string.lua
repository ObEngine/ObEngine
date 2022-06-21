---@meta

obe.utils.string = {};
--- Splits a std::string using a delimited.
---
---@param str string #String you want to split
---@param delimiters? string #Delimiter used to split the string
---@return string[]
function obe.utils.string.split(str, delimiters) end

--- Count of the occurences of occur in string str.
---
---@param str string #String you want to count the occurences in
---@param occur string #String you want to search
---@return number
function obe.utils.string.occurences_in_string(str, occur) end

--- Get if the string only contains letters.
---
---@param str string #String you want to check
---@return boolean
function obe.utils.string.is_string_alpha(str) end

--- Get if the string only contains letters and numbers.
---
---@param str string #String you want to check
---@return boolean
function obe.utils.string.is_string_alpha_numeric(str) end

--- Get if the string is a number.
---
---@param str string #String you want to check
---@return boolean
function obe.utils.string.is_string_numeric(str) end

--- Get if the string is an integer.
---
---@param str string #String you want to check
---@return boolean
function obe.utils.string.is_string_int(str) end

--- Get if the string is a float.
---
---@param str string #String you want to check
---@return boolean
function obe.utils.string.is_string_float(str) end

--- Replace all the occurences of search to replace in the string subject.
---
---@param subject string #The string you want to modify
---@param search string #The string to replace
---@param replace string #The content that will replace search occurences
---@return string
function obe.utils.string.replace(subject, search, replace) end

--- Check if the string is surrounded by the given string.
---
---@param string string #String you want to check
---@param bet string #String you want to check if it surrounds the first string
---@return boolean
function obe.utils.string.is_surrounded_by(string, bet) end

--- Generates a random string witch characters from the given set.
---
---@param set string #Set of characters to use for the generation
---@param len number #Length of the string you want to generate
---@return string
function obe.utils.string.get_random_key(set, len) end

--- Check if a string contains another one.
---
---@param string string #The string to check
---@param search string #The content to search in the first string
---@return boolean
function obe.utils.string.contains(string, search) end

--- Checks if "string" starts with "search".
---
---@param string string #String where to search the prefix
---@param search string #Prefix to check
---@return boolean
function obe.utils.string.starts_with(string, search) end

--- Checks if "string" ends with "search".
---
---@param string string #String where to search the suffix
---@param search string #Suffix to check
---@return boolean
function obe.utils.string.ends_with(string, search) end

---@param source string #
---@param target string #
---@return number
function obe.utils.string.distance(source, target) end

---@param source string #
---@param words string[] #
---@param limit? number #
---@return string[]
function obe.utils.string.sort_by_distance(source, words, limit) end

---@param source string #
---@return string
function obe.utils.string.quote(source) end

---@param source string #
---@return string
function obe.utils.string.titleize(source) end


---@type string
obe.utils.string.Alphabet = {};

---@type string
obe.utils.string.Numbers = {};
return obe.utils.string;