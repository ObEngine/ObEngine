#pragma once

/**
 * \brief Various functions related to functions manipulation
 * @Bind
 */
namespace obe::Utils::Func
{
    template <class Func>
    auto patchFunctionReturnReferenceToPointer(Func&& function);
    template <class C, class Func>
    auto patchMethodReturnReferenceToPointer(Func&& method);

    template <class Func>
    auto patchFunctionReturnReferenceToPointer(Func&& function)
    {
        return [function](auto... args) { return &function(args...); };
    }

    template <class C, class Func>
    auto patchMethodReturnReferenceToPointer(Func&& method)
    {
        return [function](C object, auto... args) {
            return &(object.*function)(args...);
        };
    }
} // namespace obe::Utils::Func
