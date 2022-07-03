---@meta

obe.animation.easing = {};

---@alias obe.animation.easing.EasingTypeMeta obe.types.SmartEnum[obe.animation.easing.EasingType]

---@alias obe.animation.easing.EasingFunction fun(p0:number):number
---@param t number #
---@return number
function obe.animation.easing.linear(t) end

---@param t number #
---@return number
function obe.animation.easing.in_sine(t) end

---@param t number #
---@return number
function obe.animation.easing.out_sine(t) end

---@param t number #
---@return number
function obe.animation.easing.in_out_sine(t) end

---@param t number #
---@return number
function obe.animation.easing.in_quad(t) end

---@param t number #
---@return number
function obe.animation.easing.out_quad(t) end

---@param t number #
---@return number
function obe.animation.easing.in_out_quad(t) end

---@param t number #
---@return number
function obe.animation.easing.in_cubic(t) end

---@param t number #
---@return number
function obe.animation.easing.out_cubic(t) end

---@param t number #
---@return number
function obe.animation.easing.in_out_cubic(t) end

---@param t number #
---@return number
function obe.animation.easing.in_quart(t) end

---@param t number #
---@return number
function obe.animation.easing.out_quart(t) end

---@param t number #
---@return number
function obe.animation.easing.in_out_quart(t) end

---@param t number #
---@return number
function obe.animation.easing.in_quint(t) end

---@param t number #
---@return number
function obe.animation.easing.out_quint(t) end

---@param t number #
---@return number
function obe.animation.easing.in_out_quint(t) end

---@param t number #
---@return number
function obe.animation.easing.in_expo(t) end

---@param t number #
---@return number
function obe.animation.easing.out_expo(t) end

---@param t number #
---@return number
function obe.animation.easing.in_out_expo(t) end

---@param t number #
---@return number
function obe.animation.easing.in_circ(t) end

---@param t number #
---@return number
function obe.animation.easing.out_circ(t) end

---@param t number #
---@return number
function obe.animation.easing.in_out_circ(t) end

---@param t number #
---@return number
function obe.animation.easing.in_back(t) end

---@param t number #
---@return number
function obe.animation.easing.out_back(t) end

---@param t number #
---@return number
function obe.animation.easing.in_out_back(t) end

---@param t number #
---@return number
function obe.animation.easing.in_elastic(t) end

---@param t number #
---@return number
function obe.animation.easing.out_elastic(t) end

---@param t number #
---@return number
function obe.animation.easing.in_out_elastic(t) end

---@param t number #
---@return number
function obe.animation.easing.in_bounce(t) end

---@param t number #
---@return number
function obe.animation.easing.out_bounce(t) end

---@param t number #
---@return number
function obe.animation.easing.in_out_bounce(t) end


--- 
---
---@class obe.animation.easing.EasingType
obe.animation.easing.EasingType = {
    ---@type obe.animation.easing.EasingType
    Linear = 0,
    ---@type obe.animation.easing.EasingType
    InSine = 1,
    ---@type obe.animation.easing.EasingType
    OutSine = 2,
    ---@type obe.animation.easing.EasingType
    InOutSine = 3,
    ---@type obe.animation.easing.EasingType
    InQuad = 4,
    ---@type obe.animation.easing.EasingType
    OutQuad = 5,
    ---@type obe.animation.easing.EasingType
    InOutQuad = 6,
    ---@type obe.animation.easing.EasingType
    InCubic = 7,
    ---@type obe.animation.easing.EasingType
    OutCubic = 8,
    ---@type obe.animation.easing.EasingType
    InOutCubic = 9,
    ---@type obe.animation.easing.EasingType
    InQuart = 10,
    ---@type obe.animation.easing.EasingType
    OutQuart = 11,
    ---@type obe.animation.easing.EasingType
    InOutQuart = 12,
    ---@type obe.animation.easing.EasingType
    InQuint = 13,
    ---@type obe.animation.easing.EasingType
    OutQuint = 14,
    ---@type obe.animation.easing.EasingType
    InOutQuint = 15,
    ---@type obe.animation.easing.EasingType
    InExpo = 16,
    ---@type obe.animation.easing.EasingType
    OutExpo = 17,
    ---@type obe.animation.easing.EasingType
    InOutExpo = 18,
    ---@type obe.animation.easing.EasingType
    InCirc = 19,
    ---@type obe.animation.easing.EasingType
    OutCirc = 20,
    ---@type obe.animation.easing.EasingType
    InOutCirc = 21,
    ---@type obe.animation.easing.EasingType
    InBack = 22,
    ---@type obe.animation.easing.EasingType
    OutBack = 23,
    ---@type obe.animation.easing.EasingType
    InOutBack = 24,
    ---@type obe.animation.easing.EasingType
    InElastic = 25,
    ---@type obe.animation.easing.EasingType
    OutElastic = 26,
    ---@type obe.animation.easing.EasingType
    InOutElastic = 27,
    ---@type obe.animation.easing.EasingType
    InBounce = 28,
    ---@type obe.animation.easing.EasingType
    OutBounce = 29,
    ---@type obe.animation.easing.EasingType
    InOutBounce = 30,
};
return obe.animation.easing;