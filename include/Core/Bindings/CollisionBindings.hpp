#pragma once

namespace kaguya
{
    class State;
}

/**
 * \brief Bindings to Collision related classes and functions
 */
namespace obe::Bindings::CollisionBindings
{
    void LoadTrajectory(kaguya::State* lua);
    void LoadTrajectoryNode(kaguya::State* lua);
    void LoadPolygonalCollider(kaguya::State* lua);
} // namespace obe::Bindings::CollisionBindings
