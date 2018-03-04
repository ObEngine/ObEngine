#pragma once

#include <kaguya/kaguya.hpp>

/**
* \brief Bindings to Transform related classes and functions
*/
namespace obe::Bindings::TransformBindings
{
    void LoadMovable(kaguya::State* lua);
    void LoadSceneNode(kaguya::State* lua);
    void LoadProtectedUnitVector(kaguya::State* lua);
    void LoadRect(kaguya::State* lua);
    void LoadReferencial(kaguya::State* lua);
    void LoadUnitBasedObject(kaguya::State* lua);
    void LoadUnitVector(kaguya::State* lua);
    void LoadUnits(kaguya::State* lua);
}