---@meta

obe.animation.easing = {};

---@alias obe.animation.easing.EasingTypeMeta obe.Types.SmartEnum[obe.animation.easing.EasingType]

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
    Linear = 0,
    InSine = 1,
    OutSine = 2,
    InOutSine = 3,
    InQuad = 4,
    OutQuad = 5,
    InOutQuad = 6,
    InCubic = 7,
    OutCubic = 8,
    InOutCubic = 9,
    InQuart = 10,
    OutQuart = 11,
    InOutQuart = 12,
    InQuint = 13,
    OutQuint = 14,
    InOutQuint = 15,
    InExpo = 16,
    OutExpo = 17,
    InOutExpo = 18,
    InCirc = 19,
    OutCirc = 20,
    InOutCirc = 21,
    InBack = 22,
    OutBack = 23,
    InOutBack = 24,
    InElastic = 25,
    OutElastic = 26,
    InOutElastic = 27,
    InBounce = 28,
    OutBounce = 29,
    InOutBounce = 30,
};
return obe.animation.easing;