#pragma once

namespace sol
{
    class state_view;
};
namespace obe::collision::Bindings
{
    void LoadClassCollisionData(sol::state_view state);
    void LoadClassPolygonalCollider(sol::state_view state);
    void LoadClassTrajectory(sol::state_view state);
    void LoadClassTrajectoryNode(sol::state_view state);
    void LoadEnumColliderTagType(sol::state_view state);
};