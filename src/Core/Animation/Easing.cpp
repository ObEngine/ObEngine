#include <cmath>

#include <Animation/Easing.hpp>
#include <Animation/Exceptions.hpp>
#include <Utils/MathUtils.hpp>

namespace obe::animation::easing
{
    using utils::math::pi;

    double linear(double t)
    {
        return t;
    }

    double in_sine(double t)
    {
        return sin(1.5707963 * t);
    }

    double out_sine(double t)
    {
        return 1 + sin(1.5707963 * (--t));
    }

    double in_out_sine(double t)
    {
        return 0.5 * (1 + sin(3.1415926 * (t - 0.5)));
    }

    double in_quad(double t)
    {
        return t * t;
    }

    double out_quad(double t)
    {
        return t * (2 - t);
    }

    double in_out_quad(double t)
    {
        return t < 0.5 ? 2 * t * t : t * (4 - 2 * t) - 1;
    }

    double in_cubic(double t)
    {
        return t * t * t;
    }

    double out_cubic(double t)
    {
        --t;
        return 1 + t * t * t;
    }

    double in_out_cubic(double t)
    {
        return t < 0.5 ? 4 * t * t * t : 1 - pow(-2 * t + 2, 3) / 2;
    }

    double in_quart(double t)
    {
        t *= t;
        return t * t;
    }

    double out_quart(double t)
    {
        --t;
        t = t * t;
        return 1 - t * t;
    }

    double in_out_quart(double t)
    {
        if (t < 0.5)
        {
            t *= t;
            return 8 * t * t;
        }
        else
        {
            --t;
            t = t * t;
            return 1 - 8 * t * t;
        }
    }

    double in_quint(double t)
    {
        double t2 = t * t;
        return t * t2 * t2;
    }

    double out_quint(double t)
    {
        --t;
        double t2 = t * t;
        return 1 + t * t2 * t2;
    }

    double in_out_quint(double t)
    {
        double t2;
        if (t < 0.5)
        {
            t2 = t * t;
            return 16 * t * t2 * t2;
        }
        else
        {
            --t;
            t2 = t * t;
            return 1 + 16 * t * t2 * t2;
        }
    }

    double in_expo(double t)
    {
        return (pow(2, 8 * t) - 1) / 255;
    }

    double out_expo(double t)
    {
        return 1 - pow(2, -8 * t);
    }

    double in_out_expo(double t)
    {
        if (t < 0.5)
        {
            return (pow(2, 16 * t) - 1) / 510;
        }
        else
        {
            return 1 - 0.5 * pow(2, -16 * (t - 0.5));
        }
    }

    double in_circ(double t)
    {
        return 1 - sqrt(1 - t);
    }

    double out_circ(double t)
    {
        return sqrt(t);
    }

    double in_out_circ(double t)
    {
        if (t < 0.5)
        {
            return (1 - sqrt(1 - 2 * t)) * 0.5;
        }
        else
        {
            return (1 + sqrt(2 * t - 1)) * 0.5;
        }
    }

    double in_back(double t)
    {
        return t * t * (2.70158 * t - 1.70158);
    }

    double out_back(double t)
    {
        --t;
        return 1 + t * t * (2.70158 * t + 1.70158);
    }

    double in_out_back(double t)
    {
        if (t < 0.5)
        {
            return t * t * (7 * t - 2.5) * 2;
        }
        else
        {
            --t;
            return 1 + t * t * 2 * (7 * t + 2.5);
        }
    }

    double in_elastic(double t)
    {
        double t2 = t * t;
        return t2 * t2 * sin(t * pi * 4.5);
    }

    double out_elastic(double t)
    {
        double t2 = (t - 1) * (t - 1);
        return 1 - t2 * t2 * cos(t * pi * 4.5);
    }

    double in_out_elastic(double t)
    {
        double t2;
        if (t < 0.45)
        {
            t2 = t * t;
            return 8 * t2 * t2 * sin(t * pi * 9);
        }
        else if (t < 0.55)
        {
            return 0.5 + 0.75 * sin(t * pi * 4);
        }
        else
        {
            t2 = (t - 1) * (t - 1);
            return 1 - 8 * t2 * t2 * sin(t * pi * 9);
        }
    }

    double in_bounce(double t)
    {
        return pow(2, 6 * (t - 1)) * abs(sin(t * pi * 3.5));
    }

    double out_bounce(double t)
    {
        return 1 - pow(2, -6 * t) * abs(cos(t * pi * 3.5));
    }

    double in_out_bounce(double t)
    {
        if (t < 0.5)
        {
            return 8 * pow(2, 8 * (t - 1)) * abs(sin(t * pi * 7));
        }
        else
        {
            return 1 - 8 * pow(2, -8 * t) * abs(sin(t * pi * 7));
        }
    }

    static std::unordered_map<EasingType, EasingFunction> EASING_ENUM_TO_FUNCTIONS = {
        { EasingType::Linear, linear },
        { EasingType::InSine, in_sine },
        { EasingType::OutSine, out_sine },
        { EasingType::InOutSine, in_out_sine },
        { EasingType::InQuad, in_quad },
        { EasingType::OutQuad, out_quad },
        { EasingType::InOutQuad, in_out_quad },
        { EasingType::InCubic, in_cubic },
        { EasingType::OutCubic, out_cubic },
        { EasingType::InOutCubic, in_out_cubic },
        { EasingType::InQuart, in_quart },
        { EasingType::OutQuart, out_quart },
        { EasingType::InOutQuart, in_out_quart },
        { EasingType::InQuint, in_quint },
        { EasingType::OutQuint, out_quint },
        { EasingType::InOutQuint, in_out_quint },
        { EasingType::InExpo, in_expo },
        { EasingType::OutExpo, out_expo },
        { EasingType::InOutExpo, in_out_expo },
        { EasingType::InCirc, in_circ },
        { EasingType::OutCirc, out_circ },
        { EasingType::InOutCirc, in_out_circ },
        { EasingType::InBack, in_back },
        { EasingType::OutBack, out_back },
        { EasingType::InOutBack, in_out_back },
        { EasingType::InElastic, in_elastic },
        { EasingType::OutElastic, out_elastic },
        { EasingType::InOutElastic, in_out_elastic },
        { EasingType::InBounce, in_bounce },
        { EasingType::OutBounce, out_bounce },
        { EasingType::InOutBounce, in_out_bounce },
    };

    EasingFunction get(EasingType easing)
    {
        if (const auto function = EASING_ENUM_TO_FUNCTIONS.find(easing);
            function != EASING_ENUM_TO_FUNCTIONS.end())
        {
            return function->second;
        }
        const int enum_value = static_cast<std::underlying_type_t<EasingType>>(easing);
        throw exceptions::UnknownEasingFromEnum(enum_value);
    }

    static std::unordered_map<std::string, EasingFunction> EASING_STRING_TO_FUNCTIONS = {
        { "linear", linear },
        { "in_sine", in_sine },
        { "out_sine", out_sine },
        { "in_out_sine", in_out_sine },
        { "in_quad", in_quad },
        { "out_quad", out_quad },
        { "in_out_quad", in_out_quad },
        { "in_cubic", in_cubic },
        { "out_cubic", out_cubic },
        { "in_out_cubic", in_out_cubic },
        { "in_quart", in_quart },
        { "out_quart", out_quart },
        { "in_out_quart", in_out_quart },
        { "in_quint", in_quint },
        { "out_quint", out_quint },
        { "in_out_quint", in_out_quint },
        { "in_expo", in_expo },
        { "out_expo", out_expo },
        { "in_out_expo", in_out_expo },
        { "in_circ", in_circ },
        { "out_circ", out_circ },
        { "in_out_circ", in_out_circ },
        { "in_back", in_back },
        { "out_back", out_back },
        { "in_out_back", in_out_back },
        { "in_elastic", in_elastic },
        { "out_elastic", out_elastic },
        { "in_out_elastic", in_out_elastic },
        { "in_bounce", in_bounce },
        { "out_bounce", out_bounce },
        { "in_out_bounce", in_out_bounce },
    };

    EasingFunction get(const std::string& easing)
    {
        if (const auto function = EASING_STRING_TO_FUNCTIONS.find(easing);
            function != EASING_STRING_TO_FUNCTIONS.end())
        {
            return function->second;
        }
        std::vector<std::string> easings_names;
        easings_names.reserve(EASING_STRING_TO_FUNCTIONS.size());
        for (const auto& [easing_name, _] : EASING_STRING_TO_FUNCTIONS)
        {
            easings_names.push_back(easing_name);
        }
        throw exceptions::UnknownEasingFromString(easing, easings_names);
    }
}
