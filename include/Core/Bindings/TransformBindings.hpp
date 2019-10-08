#pragma once

namespace kaguya
{
    class State;
}

/**
 * \brief Bindings to Transform related classes and functions
 */
namespace obe::Bindings::TransformBindings
{
    void LoadMovable(kaguya::State* lua);
    void LoadPolygon(kaguya::State* lua);
    void LoadProtectedUnitVector(kaguya::State* lua);
    void LoadRect(kaguya::State* lua);
    void LoadReferential(kaguya::State* lua);
    void LoadUnitBasedObject(kaguya::State* lua);
    void LoadUnitVector(kaguya::State* lua);
    void LoadUnits(kaguya::State* lua);
} // namespace obe::Bindings::TransformBindings