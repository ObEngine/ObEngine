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

    template <class... ComponentTypes> class Entity
    {
    private:
        template <class ComponentType> void buildSingle(ComponentType component);
        template <class ComponentType, class... ComponentPack>
        void build(ComponentType component, ComponentPack... components);
        template <class ComponentType> void buildSingle();
        template <class... ComponentPack> void build();

    protected:
        entt::registry& m_registry;
        entt::entity m_entity;

    public:
        Entity(entt::registry& registry, const std::string& id);
        Entity(entt::registry& registry, const std::string& id,
            ComponentTypes... components);
        virtual ~Entity();

        [[nodiscard]] entt::entity entity() const;

        [[nodiscard]] virtual vili::node dump() const = 0;
        virtual void load(const vili::node& data) = 0;
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
        : m_registry(registry)
    {
        m_entity = registry.create();
        buildSingle<Types::Identifiable>(Types::Identifiable(id));
        build<ComponentTypes...>();
    }

    template <class... ComponentTypes>
    Entity<ComponentTypes...>::Entity(
        entt::registry& registry, const std::string& id, ComponentTypes... components)
        : Entity(registry, id)
    {
        build<ComponentTypes...>(components...);
    }

    template <class... ComponentTypes> Entity<ComponentTypes...>::~Entity()
    {
        m_registry.destroy(m_entity);
    }

    template <class... ComponentTypes>
    entt::entity Entity<ComponentTypes...>::entity() const
    {
        return m_entity;
    }
}
