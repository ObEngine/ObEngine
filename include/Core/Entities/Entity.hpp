#pragma once

#include <typeinfo>

#include <entt/entt.hpp>
#include <vili/node.hpp>

#include <Debug/Logger.hpp>
#include <Types/Identifiable.hpp>

namespace obe::Entities
{
    template <std::size_t N> struct num
    {
        static const constexpr auto value = N;
    };

    template <class F, std::size_t... Is> void for_(F func, std::index_sequence<Is...>)
    {
        (func(num<Is> {}), ...);
    }

    class EntityBase
    {
    protected:
        entt::registry& m_registry;
        entt::entity m_entity;

    public:
        EntityBase(entt::registry& registry, const std::string& id);
        virtual ~EntityBase();

        [[nodiscard]] entt::entity entity() const;
        [[nodiscard]] virtual vili::node dump() const = 0;
        virtual void load(const vili::node& data) = 0;
    };

    template <class... ComponentTypes> class Entity : public EntityBase
    {
    private:
        template <class ComponentType> void buildSingle(ComponentType component);
        template <class ComponentType, class... ComponentPack>
        void build(ComponentType component, ComponentPack... components);
        template <class ComponentType> void buildSingle();
        template <class... ComponentPack> void build();

    public:
        Entity(entt::registry& registry, const std::string& id);
        Entity(entt::registry& registry, const std::string& id,
            ComponentTypes... components);
        ~Entity() override = default;

        [[nodiscard]] vili::node dump() const override = 0;
        void load(const vili::node& data) override = 0;
    };

    template <class... Types>
    template <class ComponentType>
    void Entity<Types...>::buildSingle(ComponentType component)
    {
        Debug::Log->info(
            "Adding component {} with constructor", typeid(ComponentType).name());
        m_registry.emplace<ComponentType>(m_entity, component);
    }

    template <class... Types>
    template <class ComponentType, class... ComponentPack>
    void Entity<Types...>::build(ComponentType component, ComponentPack... components)
    {
        buildSingle<ComponentType>(component);
        build<ComponentPack...>(components...);
    }

    template <class... ComponentTypes>
    template <class ComponentType>
    void Entity<ComponentTypes...>::buildSingle()
    {
        Debug::Log->info("Adding component {}", typeid(ComponentType).name());
        m_registry.emplace<ComponentType>(m_entity);
    }

    template <class... ComponentTypes>
    template <class... ComponentPack>
    void Entity<ComponentTypes...>::build()
    {
        ((buildSingle<ComponentPack>()), ...);
    }

    template <class... ComponentTypes>
    Entity<ComponentTypes...>::Entity(entt::registry& registry, const std::string& id)
        : EntityBase(registry, id)
    {
        build<ComponentTypes...>();
    }

    template <class... ComponentTypes>
    Entity<ComponentTypes...>::Entity(
        entt::registry& registry, const std::string& id, ComponentTypes... components)
        : EntityBase(registry, id)
    {
        build<ComponentTypes...>(components...);
    }
}
