#include <Entities/Entity.hpp>

namespace obe::Entities
{
    EntityBase::EntityBase(entt::registry& registry, const std::string& id)
        : m_registry(registry)
    {
        m_entity = registry.create();
        m_registry.emplace<Types::Identifiable>(m_entity, id);
    }

    EntityBase::~EntityBase()
    {
        m_registry.destroy(m_entity);
    }

    entt::entity EntityBase::entity() const
    {
        return m_entity;
    }
}
