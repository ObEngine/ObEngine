#pragma once

namespace kaguya
{
    class State;
}

/**
 * \brief Bindings to Types related classes and functions
 */
namespace obe::Bindings::TypesBindings
{
    void LoadIdentifiable(kaguya::State* lua);
    void LoadSelectable(kaguya::State* lua);
    void LoadSerializable(kaguya::State* lua);
    void LoadTogglable(kaguya::State* lua);
} // namespace obe::Bindings::TypesBindings