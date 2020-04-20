#pragma once

namespace sol
{
    class state_view;
};
namespace obe::Graphics::Exceptions::Bindings
{
    void LoadClassCanvasElementAlreadyExists(sol::state_view state);
    void LoadClassInvalidColorName(sol::state_view state);
    void LoadClassReadOnlyTexture(sol::state_view state);
};