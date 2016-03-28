Func<Float> sin(Float x) {
    return Core::sin(x);
}
Func<Float> cos(Float x) {
    return Core::cos(x);
}
Func<Float> tan(Float x) {
    return Core::tan(x);
}
Func<Float> asin(Float x) {
    return Core::asin(x);
}
Func<Float> acos(Float x) {
    return Core::acos(x);
}
Func<Float> atan(Float x) {
    return Core::atan(x);
}
Func<Float> sinh(Float x) {
    return Core::sinh(x);
}
Func<Float> cosh(Float x) {
    return Core::cosh(x);
}
Func<Float> tanh(Float x) {
    return Core::tanh(x);
}
Func<Float> exp(Float x) {
    return Core::exp(x);
}
Func<Float> abs(Float x) {
    return Core::abs(x);
}
Func<Float> ln(Float x) {
    return Core::ln(x);
}
Func<Float> log(Float x) {
    return Core::log(x);
}
Func<Float> sqrt(Float x) {
    return Core::sqrt(x);
}
Func<Float> cbrt(Float x) {
    return Core::cbrt(x);
}
Func<Float> ceil(Float x) {
    return Core::ceil(x);
}
Func<Float> floor(Float x) {
    return Core::floor(x);
}
Func<Float> round(Float x) {
    return Core::round(x);
}
Func<Int> bound(Float s, Float e, Float n) {
    If (n >= s and n <= e)
    {
        return 1;
    }
    Else
    {
        return 0;
    }
}
Func<Int> heav(Float x) {
    If (x >= 0)
    {
        return 1;
    }
    Else
    {
        return 0;
    }
}
