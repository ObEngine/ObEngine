#pragma once

#include <entt/entt.hpp>

namespace obe::Component
{
    class Identifiable
    {
    public:
        entt::hashed_string id;

        Identifiable(entt::hashed_string id)
            : id(id)
        {
        }
    };
}

namespace obe::Scene
{
    class NewScene
    {
    private:
        entt::registry& m_registry;
    public:
        NewScene(entt::registry& registry);
    };
}