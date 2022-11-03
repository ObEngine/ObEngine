#pragma once

#include <concepts>

#include <sol/sol.hpp>

#include <Exception.hpp>

namespace obe::script
{
    namespace exceptions
    {
        class UnknownCaster : public Exception<UnknownCaster>
        {
        public:
            using Exception::Exception;
            UnknownCaster(std::string_view castable_type, DebugInfo info)
                : Exception(info)
            {
                this->error("Could not find caster for type '{}'", castable_type);
            }
        };
    }

    template <class T>
    concept VirtuallyTyped = requires(T x)
    {
        { x.type() } -> std::same_as<std::string_view>;
        { std::has_virtual_destructor_v<T> };
    };

    template <class T, class CastableBase>
    concept VirtuallyTypedChildClass = 
        std::derived_from<T, CastableBase> && 
        std::same_as<std::remove_cvref_t<decltype(T::Type)>, std::string_view> &&
        !std::is_abstract_v<T> &&
        requires(T x) {
            { x.type() } -> std::same_as<std::string_view>;
        };

    template <VirtuallyTyped CastableBase>
    class AutoCastManager
    {
    public:
        using Caster = std::function<sol::lua_value(CastableBase*)>;

    protected:
        static inline std::unordered_map<std::string_view, Caster> CastersMap;

    public:
        virtual ~AutoCastManager() = default;

        template <VirtuallyTypedChildClass<CastableBase> CastableSubClass>
        static void Register();

        [[nodiscard]] static sol::lua_value Cast(CastableBase* ptr);
    };

    template <VirtuallyTyped CastableBase>
    template <VirtuallyTypedChildClass<CastableBase> CastableSubClass>
    void AutoCastManager<CastableBase>::Register()
    {
        CastersMap[CastableSubClass::Type] = [](CastableBase* ptr) -> sol::lua_value
        { return static_cast<CastableSubClass*>(ptr); };
    }

    template <VirtuallyTyped CastableBase>
    sol::lua_value AutoCastManager<CastableBase>::Cast(CastableBase* ptr)
    {
        if (!CastersMap.contains(ptr->type()))
        {
            throw exceptions::UnknownCaster(ptr->type(), EXC_INFO);
        }
        return CastersMap.at(ptr->type())(ptr);
    }
}

